#include "sql_outputer.hpp"

#include <array>
#include <cassert>

using namespace std;

int main(void) {
    SQLOutputer sql_outputer("/tmp/SQL_outputter_test");

    sql_outputer.initialize_DB();
    Board board;
    board.addPly(Point(0, 0, 0));
    board.addPly(Point(3, 3, 3));
    board.addPly(Point(0, 0, 1));
    board.addPly(Point(6, 6, 6));
    board.addPly(Point(0, 0, 2));
    board.addPly(Point(1, 1, 1));

    array<array<array<int, 7>, 7>, 7> arr = {0};

    arr[0][0][0] = -1;
    arr[3][3][3] = -2;
    arr[0][0][1] = -1;
    arr[6][6][6] = -2;
    arr[0][0][2] = -1;
    arr[1][1][1] = -2;

    sql_outputer.outputSolution(arr, board);

    return 0;
}