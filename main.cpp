
#include "board_position.hpp"
#include "hopcroft_karp.hpp"
#include "line.hpp"
#include "point.hpp"
#include "match.hpp"
#include "console_player.hpp"
#include "random_player.hpp"
#include "given_moves_player.hpp"
#include "pairing_preparer.hpp"
#include "utility.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

const int cross = -1;
const int circle = -2;

const vector<Line> ALL_CANONICAL_LINES = Line::generateAllCanonicalLines();


void iterateThroughAllBoardsByCase(const function<void(vector<Point>)> & f, bool firstCenter){
    vector<Point> moves = vector<Point>(3, Point::first());
    while(true){
        while(true){
            while(true){
                vector<Point> arguments;
                if(firstCenter){
                    arguments.push_back(Point(3,3,3));
                }
                arguments.insert(arguments.end(), moves.begin(), moves.end());
                f(arguments);
                if(!moves[2].hasNext()){
                    moves[2] = Point::first();
                    break;
                }
                moves[2] = moves[2].next();
            }
            if(!moves[1].hasNext()){
                moves[1] = Point::first();
                break;
            }
            moves[1] = moves[1].next();
        }   
        if(!moves[0].hasNext()){
            break;
        }
        moves[0] = moves[0].next();
        if(moves[0] == Point(3,3,3)){
            moves[0] = moves[0].next();
        }
    }
}

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

HopcroftKarp<Point, Line> initializeHopcroftKarp(const BoardPosition & board){
    vector<Line> linesToCover =  getNoncoveredLines(board.circles);
    
    HopcroftKarp<Point, Line> hopcroftKarp = HopcroftKarp<Point, Line>(7*7*7 - board.pliesMade(),  linesToCover.size()*2);
    for(const Line & line : linesToCover){
        Line flippedLine = line.getFlippedLine();
        for(const Point & point : line.getPointsOnLine()){
            if(isInVector(board.crosses, point)){ // circles are gone because, the lines containing them were filtered out
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
    for(const Point & p : startingPosition.crosses){
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

void tryCase(const vector<Point> & points){
    BoardPosition board;
    try{
        GivenMovesPlayer gmp(points);
        PairingPreparer pp;
        board = Match::play(gmp, pp, [&pp](const BoardPosition & board){ 
            (void)board;
            return pp.isFinished();}
        );
    }catch(const CannotPlayMoveException & e){
        cerr << "Invalid sequence ";
        print(points, cerr);
        cerr << endl;
        return;
    }
    
    HopcroftKarp<Point, Line> HC = initializeHopcroftKarp(board);
    size_t matching_size = HC.maxBipartiteMatching();

    // todo handle invlaid BPM more nicely 
    if(HC.rightPartiteSize() != matching_size){
        cerr << "Insuficient matching" << endl << board << endl;
        throw;
    }
    
    unordered_map<Line, Point> linesPartite = HC.getRightPartiteMatching();
    array<array<array<int, 7>,7>,7> solutionGrid = {0};
    outputSolution(board, aggregateLinePoints(linesPartite), solutionGrid);
    std::stringstream ss;
    ss << "positions/" << board << ".txt";
    std::string filename = ss.str();
    std::ofstream fileStream(filename, std::ios::out);
    printSolution(solutionGrid, fileStream);
    fileStream.close();
}

int main(void){
    iterateThroughAllBoardsByCase(tryCase, false);
    iterateThroughAllBoardsByCase(tryCase, true);
    return 0;
}