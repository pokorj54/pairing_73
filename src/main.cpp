
#include <omp.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "board.hpp"
#include "draw_strategy.hpp"
#include "given_moves_player.hpp"
#include "hopcroft_karp.hpp"
#include "line.hpp"
#include "match.hpp"
#include "pairing_preparer.hpp"
#include "point.hpp"
#include "sql_outputer.hpp"
#include "utility.hpp"

using namespace std;

const string output_folder = "positions/";
const string errors_folder = "error_out/";

vector<vector<Point>> toSolve;

SQLOutputer sqlOutputer(output_folder + "DB");

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

void doCase(const vector<Point>& points) {
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

    array<array<array<int, 7>, 7>, 7> solutionGrid = compute_draw_strategy(board);

#pragma omp critical
    sqlOutputer.outputSolution(solutionGrid, board);
}

void tryCase(const vector<Point>& points) {
    try {
        doCase(points);
    } catch (const std::exception& e) {
        cerr << e.what() << '\n';
        print(points, cerr);
        cerr << endl;
    }
}

void putToVector(const vector<Point>& points) {
    toSolve.push_back(points);
}

void createDirectories(const string& str) {
    string argument = string("mkdir -p ") + str;
    system(argument.c_str());
}

int main(int argc, char** args) {
    //todo set by number of system cores
    if (argc == 2) {
        omp_set_num_threads(atoi(args[1]));
    } else {
        cerr << "Insufficient number of arguments, expected number of threads" << endl;
        return 1;
    }
    createDirectories(output_folder);
    createDirectories(errors_folder);
    sqlOutputer.initialize_DB();

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