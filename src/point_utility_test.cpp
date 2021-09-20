#include "point_utility.hpp"

#include <cassert>

using namespace std;

int main(void) {
    assert(flip(0) == 6);
    assert(flip(1) == 5);
    assert(flip(2) == 4);
    assert(flip(3) == 3);
    assert(flip(4) == 2);
    assert(flip(5) == 1);
    assert(flip(6) == 0);

    assert(areOnSameLine(Point(0, 0, 0), Point(1, 1, 1)));
    assert(areOnSameLine(Point(0, 0, 0), Point(0, 0, 0)));
    assert(areOnSameLine(Point(3, 2, 6), Point(3, 2, 4)));
    assert(areOnSameLine(Point(3, 3, 3), Point(1, 5, 1)));
    assert(areOnSameLine(Point(2, 4, 2), Point(4, 2, 4)));
    assert(areOnSameLine(Point(2, 4, 2), Point(4, 2, 2)));
    assert(areOnSameLine(Point(1, 1, 5), Point(5, 5, 1)));
    assert(areOnSameLine(Point(2, 3, 3), Point(2, 4, 4)));
    assert(areOnSameLine(Point(6, 2, 2), Point(1, 2, 2)));
    assert(areOnSameLine(Point(4, 0, 6), Point(4, 1, 5)));
    assert(!areOnSameLine(Point(0, 0, 0), Point(6, 6, 4)));
    assert(!areOnSameLine(Point(2, 5, 2), Point(5, 2, 5)));
    assert(!areOnSameLine(Point(2, 1, 0), Point(5, 4, 0)));
    assert(!areOnSameLine(Point(3, 4, 5), Point(2, 1, 0)));
}