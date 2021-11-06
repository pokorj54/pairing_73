
#include <omp.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "board.hpp"
#include "console_player.hpp"
#include "file_outputer.hpp"
#include "given_moves_player.hpp"
#include "hopcroft_karp.hpp"
#include "line.hpp"
#include "match.hpp"
#include "pairing_preparer.hpp"
#include "point.hpp"
#include "random_player.hpp"
#include "utility.hpp"

using namespace std;

const string output_folder = "positions/";
const string errors_folder = "error_out/";

const int cross = -1;
const int circle = -2;

const vector<Line> ALL_CANONICAL_LINES = Line::generateAllCanonicalLines();

vector<vector<Point>> toSolve;

void iterateThroughAllBoardsByCase(const function<void(vector<Point>)>& f, bool firstCenter) {
    vector<Point> moves = vector<Point>(3, Point::first());
    while (true) {
        while (true) {
            while (true) {
                vector<Point> arguments;
                if (firstCenter) {
                    arguments.push_back(Point(3, 3, 3));
                }
                arguments.insert(arguments.end(), moves.begin(), moves.end());
                f(arguments);
                if (!moves[2].hasNext()) {
                    moves[2] = Point::first();
                    break;
                }
                moves[2] = moves[2].next();
            }
            if (!moves[1].hasNext()) {
                moves[1] = Point::first();
                break;
            }
            moves[1] = moves[1].next();
        }
        if (!moves[0].hasNext()) {
            break;
        }
        moves[0] = moves[0].next();
        if (moves[0] == Point(3, 3, 3)) {
            moves[0] = moves[0].next();
        }
    }
}

void iterateThroughAllBoards(const function<void(vector<Point>)>& f) {
    iterateThroughAllBoardsByCase(f, false);
    iterateThroughAllBoardsByCase(f, true);
}

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

ostream* thread_err_output = nullptr;
#pragma omp threadprivate(thread_err_output)

void initialize_thread_err_output() {
    thread_err_output = new std::ofstream(errors_folder + "e" + std::to_string(omp_get_thread_num()) + ".txt", std::ios::out);
}

void print_invalid_sequence(const vector<Point>& points) {
    *thread_err_output << "Invalid sequence ";
    print(points, *thread_err_output);
    *thread_err_output << endl;
}

void tryCase(const vector<Point>& points) {
    Board board;
    try {
        GivenMovesPlayer gmp(points);
        PairingPreparer pp;
        board = Match::play(gmp, pp, [&pp](const Board& board) { 
            (void)board;
            return pp.isFinished(); });
    } catch (const CannotPlayMoveException& e) {
        print_invalid_sequence(points);
        return;
    }

    HopcroftKarp<Point, Line> HC = initializeHopcroftKarp(board);
    size_t matching_size = HC.maxBipartiteMatching();

    // todo handle invlaid BPM more nicely
    if (HC.rightPartiteSize() != matching_size) {
        *thread_err_output << "Insuficient matching" << endl
                           << board.toString() << endl;
        throw;
    }

    unordered_map<Line, Point> linesPartite = HC.getRightPartiteMatching();
    array<array<array<int, 7>, 7>, 7> solutionGrid = {0};
    solutio_to_grid(board, aggregateLinePoints(linesPartite), solutionGrid);

    FileOutputer fileOutputer(output_folder);
    fileOutputer.outputSolution(solutionGrid, board);
}

void putToVector(const vector<Point>& points) {
    toSolve.push_back(points);
}

void createDirectories(const string& str) {
    string argument = string("mkdir -p ") + str;
    system(argument.c_str());
}

int main(int argc, char** args) {
    createDirectories(output_folder);
    createDirectories(errors_folder);
    //todo set by number of system cores
    if (argc == 2) {
        omp_set_num_threads(atoi(args[1]));
    } else {
        cerr << "Insufficient number of arguments, expected number of threads" << endl;
        return 1;
    }
#pragma omp parallel
    initialize_thread_err_output();

#pragma omp parallel
#pragma omp single
    cout << "threads: " << omp_get_num_threads() << endl;

    cout << "Creating all cases" << endl;
    iterateThroughAllBoards(putToVector);
    cout << "Cases created: " << toSolve.size() << endl;

#pragma omp parallel for schedule(static, 16)
    for (size_t i = 0; i < toSolve.size(); ++i) {
        tryCase(toSolve[i]);
    }

    return 0;
}