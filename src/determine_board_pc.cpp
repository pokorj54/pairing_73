#include <functional>
#include <iostream>

#include "board.hpp"
#include "given_moves_player.hpp"
#include "match.hpp"
#include "pairing_preparer.hpp"

using namespace std;

vector<Point> get_points(int n, char** moves) {
    vector<Point> result;
    for (int i = 0; i < n; ++i) {
        Point p = Point(moves[i][0] - '0', moves[i][1] - '0', moves[i][2] - '0');
        result.push_back(p);
    }
    return result;
}

int main(int argc, char** args) {
    if (argc != 4 && argc != 5) {
        cerr << "Expected 3 or 4 arguments of points, eg. 000 242 115 or 333 145 666 501" << endl;
        return 1;
    }
    vector<Point> moves = get_points(argc - 1, args + 1);
    GivenMovesPlayer gmp(moves);
    PairingPreparer pp;
    try {
        Board board = Match::play(gmp, pp, [&pp](const Board& board) { 
                (void)board;
                return pp.isFinished(); });
        cout << board.toString('_') << endl;
    } catch (const std::exception& e) {
        cerr << "invalid sequence of moves" << endl;
        return 1;
    }

    return 0;
}