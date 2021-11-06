#include "draw_strategy.hpp"

#include "board.hpp"
#include "given_moves_player.hpp"
#include "hopcroft_karp.hpp"
#include "line.hpp"
#include "match.hpp"
#include "pairing_preparer.hpp"
#include "point.hpp"
#include "sql_outputer.hpp"
#include "utility.hpp"
using namespace std;

const int cross = -1;
const int circle = -2;

const vector<Line> ALL_CANONICAL_LINES = Line::generateAllCanonicalLines();

vector<Line> getNoncoveredLines(const vector<Point>& blockingPoints) {
    vector<Line> lines;
    for (const Line& line : ALL_CANONICAL_LINES) {
        bool covered = false;
        for (const Point& point : blockingPoints) {
            if (line.containsPoint(point)) {
                covered = true;
                break;
            }
        }
        if (!covered) {
            lines.push_back(line);
        }
    }
    return lines;
}

HopcroftKarp<Point, Line> initializeHopcroftKarp(const Board& board) {
    vector<Line> linesToCover = getNoncoveredLines(board.getCircles());

    HopcroftKarp<Point, Line> hopcroftKarp = HopcroftKarp<Point, Line>(7 * 7 * 7 - board.pliesMade(), linesToCover.size() * 2);
    for (const Line& line : linesToCover) {
        Line flippedLine = line.getFlippedLine();
        for (const Point& point : line.getPointsOnLine()) {
            if (isInVector(board.getCrosses(), point)) {  // circles are gone because, the lines containing them were filtered out
                continue;
            }
            hopcroftKarp.addEdge(point, line);
            hopcroftKarp.addEdge(point, flippedLine);
        }
    }
    return hopcroftKarp;
}

void solutio_to_grid(const Board& startingPosition, const unordered_map<Line, pair<Point, Point>>& linesPoints, array<array<array<int, 7>, 7>, 7>& outputgrid) {
    for (const Point& p : startingPosition.getCircles()) {
        outputgrid[p.x][p.y][p.z] = circle;
    }
    for (const Point& p : startingPosition.getCrosses()) {
        outputgrid[p.x][p.y][p.z] = cross;
    }
    int i = 1;

    for (pair<Line, pair<Point, Point>> p : linesPoints) {
        Point a = p.second.first;
        Point b = p.second.second;
        outputgrid[a.x][a.y][a.z] = i + 1;
        outputgrid[b.x][b.y][b.z] = i + 1;
        ++i;
    }
}

unordered_map<Line, pair<Point, Point>> aggregateLinePoints(const unordered_map<Line, Point>& linePoints) {
    unordered_map<Line, pair<Point, Point>> result;
    for (pair<Line, Point> p : linePoints) {
        Line line = p.first;
        if (!line.isCanonical()) {
            continue;
        }
        Line complementLine = line.getFlippedLine();
        result.insert({line, {p.second, linePoints.at(complementLine)}});
    }
    return result;
}

array<array<array<int, 7>, 7>, 7> compute_draw_strategy(const Board& board) {
    HopcroftKarp<Point, Line> HC = initializeHopcroftKarp(board);
    size_t matching_size = HC.maxBipartiteMatching();

    // todo handle invlaid BPM more nicely
    if (HC.rightPartiteSize() != matching_size) {
        cerr << "Insuficient matching" << endl
             << board.toString() << endl;
        throw;
    }

    unordered_map<Line, Point> linesPartite = HC.getRightPartiteMatching();
    array<array<array<int, 7>, 7>, 7> solutionGrid = {0};
    solutio_to_grid(board, aggregateLinePoints(linesPartite), solutionGrid);
    return solutionGrid;
}
