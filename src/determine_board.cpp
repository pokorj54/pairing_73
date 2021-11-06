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
    Board board = Match::play(cp, pp, [&pp](const Board& board) { 
            (void)board;
            return pp.isFinished(); });
    cerr << board.toString('_') << endl;
}