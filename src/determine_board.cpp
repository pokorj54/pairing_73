#include <functional>
#include <iostream>

#include "board.hpp"
#include "console_player.hpp"
#include "match.hpp"
#include "pairing_preparer.hpp"

using namespace std;

int main(void) {
    ConsolePlayer cp(cout, cerr, cin);
    PairingPreparer pp;
    try {
        Board board = Match::play(cp, pp, [&pp](const Board& board) { 
                (void)board;
                return pp.isFinished(); });
        cout << board.toString('_') << endl;
    } catch (const std::exception& e) {
        cerr << "invalid sequence of moves" << endl;
        return 1;
    }
    return 0;
}