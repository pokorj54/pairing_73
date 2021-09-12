#include "point.hpp"

#include <cassert>

using namespace std;

int main(void) {
    assert(Point(1, 4, 3).hasNext() && Point(1, 4, 3).next() == Point(1, 4, 4));
    assert(Point(2, 1, 6).hasNext() && Point(2, 1, 6).next() == Point(2, 2, 0));
    assert(Point(2, 6, 1).hasNext() && Point(2, 6, 1).next() == Point(2, 6, 2));
    assert(Point(2, 6, 6).hasNext() && Point(2, 6, 6).next() == Point(3, 0, 0));
    assert(Point(6, 0, 1).hasNext() && Point(6, 0, 1).next() == Point(6, 0, 2));
    assert(!Point(6, 6, 6).hasNext());

    assert(Point(1, 2, 3) == Point(1, 2, 3));
    assert(!(Point(2, 2, 3) == Point(1, 2, 3)));
    return 0;
}