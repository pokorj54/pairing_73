#include "point_utility.hpp"

#include <cassert>
#include <unordered_set>
#include <vector>

using namespace std;
template <typename T>
unordered_set<T> toSet(const vector<T>& v) {
    return unordered_set<Point>(v.begin(), v.end());
}

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

    assert(getPossiblePoints(0, {Point(0, 0, 0), Point(0, 6, 0), Point(0, 0, 6), Point(0, 6, 6)}) == vector<Point>());
    assert(getPossiblePoints(0, {Point(0, 0, 0), Point(0, 6, 0), Point(0, 0, 6)}) == vector<Point>({Point(0, 6, 6)}));
    assert(toSet(getPossiblePoints(1, {Point(1, 1, 1), Point(1, 5, 5)})) == unordered_set<Point>({Point(1, 1, 5), Point(1, 5, 1)}));
    assert(toSet(getPossiblePoints(2, {Point(2, 4, 4)})) == unordered_set<Point>({Point(2, 2, 2), Point(2, 4, 2), Point(2, 2, 4)}));
    assert(toSet(getPossiblePoints(2, {Point(2, 4, 4)})) == unordered_set<Point>({Point(2, 2, 2), Point(2, 4, 2), Point(2, 2, 4)}));
    assert(toSet(getPossiblePoints(3, {Point(1, 2, 3), Point(3, 2, 2)})) == unordered_set<Point>({Point(3, 3, 3)}));
    assert(toSet(getPossiblePoints(4, {
                                          Point(4, 0, 1),
                                          Point(4, 4, 1),
                                          Point(4, 2, 2),
                                      })) == unordered_set<Point>({
                                                 Point(4, 4, 4),
                                                 Point(4, 2, 4),
                                                 Point(4, 4, 2),
                                             }));
    assert(toSet(getPossiblePoints(5, {
                                          Point(1, 5, 1),
                                          Point(5, 4, 1),
                                          Point(5, 5, 3),
                                      })) == unordered_set<Point>({
                                                 Point(5, 5, 5),
                                                 Point(5, 1, 5),
                                                 Point(5, 1, 1),
                                                 Point(5, 5, 1),
                                             }));

    assert(getPossiblePoints(vector<int>(), {Point(1, 5, 2), Point(4, 4, 6)}) == vector<Point>());

    assert(getPossiblePoints({0}, {Point(0, 0, 0), Point(0, 6, 0), Point(0, 0, 6), Point(0, 6, 6)}) == vector<Point>());
    assert(getPossiblePoints({0}, {Point(0, 0, 0), Point(0, 6, 0), Point(0, 0, 6)}) == vector<Point>({Point(0, 6, 6)}));
    assert(toSet(getPossiblePoints({1}, {Point(1, 1, 1), Point(1, 5, 5)})) == unordered_set<Point>({Point(1, 1, 5), Point(1, 5, 1)}));
    assert(toSet(getPossiblePoints({2}, {Point(2, 4, 4)})) == unordered_set<Point>({Point(2, 2, 2), Point(2, 4, 2), Point(2, 2, 4)}));
    assert(toSet(getPossiblePoints({2}, {Point(2, 4, 4)})) == unordered_set<Point>({Point(2, 2, 2), Point(2, 4, 2), Point(2, 2, 4)}));
    assert(toSet(getPossiblePoints({3}, {Point(1, 2, 3), Point(3, 2, 2)})) == unordered_set<Point>({Point(3, 3, 3)}));

    assert(toSet(getPossiblePoints({3, 4}, {Point(4, 1, 4), Point(4, 2, 2)})) == unordered_set<Point>({
                                                                                     Point(3, 3, 3),
                                                                                     Point(4, 4, 4),
                                                                                     Point(4, 2, 4),
                                                                                     Point(4, 4, 2),
                                                                                 }));

    assert(toSet(getPossiblePoints({0, 2, 4}, {Point(1, 1, 5),
                                               Point(1, 1, 1),
                                               Point(4, 2, 2),
                                               Point(6, 6, 6),
                                               Point(2, 2, 2),
                                               Point(6, 6, 0)})) == unordered_set<Point>({
                                                                        Point(0, 0, 0),
                                                                        Point(0, 6, 0),
                                                                        Point(0, 0, 6),
                                                                        Point(0, 6, 6),
                                                                        Point(2, 2, 4),
                                                                        Point(2, 4, 2),
                                                                        Point(2, 4, 4),
                                                                        Point(4, 4, 4),
                                                                        Point(4, 2, 4),
                                                                        Point(4, 4, 2),
                                                                    }));

    assert(getLeastColinearPoint({Point(3, 3, 3)}, {Point(1, 1, 1)}) == Point(1, 1, 1));
    assert(getLeastColinearPoint({Point(3, 3, 3), Point(6, 6, 6)}, {Point(0, 0, 6), Point(0, 6, 0), Point(1, 5, 1)}) == Point(1, 5, 1));
    assert(getLeastColinearPoint({Point(3, 3, 3), Point(6, 6, 6)}, {Point(0, 0, 6), Point(0, 6, 0), Point(1, 5, 1)}) == Point(1, 5, 1));
    assert(getLeastColinearPoint({Point(0, 0, 0),
                                  Point(1, 5, 1),
                                  Point(2, 4, 4)},
                                 {Point(2, 2, 2), Point(5, 1, 5), Point(1, 1, 1)}) == Point(5, 1, 5));

    return 0;
}