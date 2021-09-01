
#include "board_position.hpp"
#include "hopcroft_karp.hpp"
#include "line.hpp"
#include "point.hpp"

#include <iostream>
#include <algorithm>

const int cross = -1;
const int circle = -2;

const vector<Line> ALL_CANONICAL_LINES = Line::generateAllCanonicalLines();


vector<Line> getNoncoveredLines(const vector<Point> & blockingPoints){
    vector<Line> lines;
    for(const Line & line: ALL_CANONICAL_LINES){
        bool covered = false;
        for(const Point & point : blockingPoints){
            if(line.containsPoint(point)){
                covered = true;
                break;
            }
        }
        if(!covered){
            lines.push_back(line);
        }
    }
    return lines;
}
template <typename T>
bool isInVector(const vector<T>& v, T t) {
    return std::find(v.begin(), v.end(), t) != v.end();
}

HopcroftKarp<Point, Line> initializeHopcroftKarp(const BoardPosition & board){
    vector<Line> linesToCover =  getNoncoveredLines(board.circles);
    
    HopcroftKarp<Point, Line> hopcroftKarp = HopcroftKarp<Point, Line>(7*7*7 - board.pliesMade(),  linesToCover.size()*2);
    for(const Line & line : linesToCover){
        Line flippedLine = line.getFlippedLine();
        for(const Point & point : line.getPointsOnLine()){
            if(isInVector(board.croses, point)){ // circles are gone because, the lines containing them were filtered out
                continue;
            }
            hopcroftKarp.addEdge(point, line);
            hopcroftKarp.addEdge(point, flippedLine);
        }
    }
    return hopcroftKarp;
}


void printSolution(const array<array<array<int, 7>,7>,7> & solution, ostream & os){
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 7; ++j){
            for(int k = 0; k < 7; ++k){
                os << solution[i][j][k] << '\t';
            }
            os << endl;
        }
        os << endl;
    }
}

void outputSolution(const BoardPosition & startingPosition, const unordered_map<Line, pair<Point, Point>> & linesPoints, array<array<array<int, 7>,7>,7> & outputgrid){
    for(const Point & p : startingPosition.circles){
        outputgrid[p.x][p.y][p.z] = circle;
    }
    for(const Point & p : startingPosition.croses){
        outputgrid[p.x][p.y][p.z] = cross;
    }
    int i = 1;

    for(pair<Line, pair<Point, Point>> p : linesPoints){
        Point a = p.second.first;
        Point b = p.second.second;
        outputgrid[a.x][a.y][a.z] = i + 1;
        outputgrid[b.x][b.y][b.z] = i + 1;
        ++i;
    }
    
}

unordered_map<Line, pair<Point, Point>> aggregateLinePoints(const unordered_map<Line, Point> & linePoints){
    unordered_map<Line, pair<Point, Point>> result;
    for(pair<Line, Point> p : linePoints){
        Line line = p.first;
        if(!line.isCanonical()){
            continue;
        }
        Line complementLine = line.getFlippedLine();
        result.insert({line, {p.second, linePoints.at(complementLine)}});
    }
    return result;
}

int main(void){
    BoardPosition board; // generate
    board.croses.push_back(Point(3,3,3));
    board.circles.push_back(Point(0,0,0));
    board.croses.push_back(Point(1,1,5));
    board.circles.push_back(Point(1,5,1));
    board.croses.push_back(Point(2,2,4));
    board.circles.push_back(Point(2,4,4));
    board.croses.push_back(Point(0,0,6));
    board.circles.push_back(Point(4,4,2));

    HopcroftKarp<Point, Line> HC = initializeHopcroftKarp(board);
    HC.maxBipartiteMatching();
    unordered_map<Line, Point> linesPartite = HC.getRightPartiteMatching();
    assert(linesPartite.size() == HC.rightPartiteSize());
    // todo handle invlaid BPM more nicely 
    array<array<array<int, 7>,7>,7> solutionGrid = {0};
    outputSolution(board, aggregateLinePoints(linesPartite), solutionGrid);
    printSolution(solutionGrid, cout);
    return 0;
}