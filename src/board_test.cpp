#include "board.hpp"

#include <cassert>

using namespace std;

int main(void) {
    Board board;
    assert(board.pliesMade() == 0);
    board.addPly(Point(1, 1, 1));
    assert(board.pliesMade() == 1);
    board.addPly(Point(2, 2, 2));
    assert(board.pliesMade() == 2);
    board.addPly(Point(1, 2, 3));
    assert(board.pliesMade() == 3);
    board.addPly(Point(3, 0, 5));
    assert(board.pliesMade() == 4);
    assert(board.getCrosses()[0] == Point(1, 1, 1));
    assert(board.getCrosses()[1] == Point(1, 2, 3));
    assert(board.getCircles()[0] == Point(2, 2, 2));
    assert(board.getCircles()[1] == Point(3, 0, 5));

    assert(board.toString('_') == "111_222_123_305");
    return 0;
}
