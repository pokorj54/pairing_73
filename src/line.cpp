#include "line.hpp"

#include <cassert>
#include <functional>
#include <vector>

#include "point.hpp"

using namespace std;

Line::Line(int x, int y, int z) : x(x), y(y), z(z) {
    assert(x >= -1 && x <= 7);
    assert(y >= -1 && y <= 7);
    assert(z >= -1 && z <= 7);
    assert(!isConstant(x) || !isConstant(y) || !isConstant(z));
}

vector<Point> Line::getPointsOnLine() const {
    vector<Point> result;
    int a = x;
    int b = y;
    int c = z;
    for (int i = 0; i < 7; ++i) {
        if (x == increasing) {
            ++a;
        } else if (x == decreasing) {
            --a;
        }
        if (y == increasing) {
            ++b;
        } else if (y == decreasing) {
            --b;
        }
        if (z == increasing) {
            ++c;
        } else if (z == decreasing) {
            --c;
        }
        result.push_back(Point(a, b, c));
    }
    return result;
}

bool Line::containsPoint(const Point& point) const {
    for (const Point& p : getPointsOnLine()) {
        if (p == point) {
            return true;
        }
    }
    return false;
}

vector<Line> Line::generateAllCanonicalLines() {
    vector<Line> result;
    for (int i = -1; i <= 7; ++i) {
        for (int j = -1; j <= 7; ++j) {
            for (int k = -1; k <= 7; ++k) {
                if (isConstant(i) && isConstant(j) && isConstant(k)) {
                    continue;
                }
                Line l = Line(i, j, k);
                if (l.isCanonical()) {
                    result.push_back(l);
                }
            }
        }
    }
    return result;
}

bool Line::operator==(const Line& o) const {
    return x == o.x && y == o.y && z == o.z;
}

bool Line::isCanonical() const {
    return (x == increasing) || (x != decreasing && y == increasing) || (x != decreasing && y != decreasing && z == increasing);
}

Line Line::getFlippedLine() const {
    return Line(flipDirection(x), flipDirection(y), flipDirection(z));
}

bool Line::isConstant(int a) {
    return a >= 0 && a < 7;
}

int Line::flipDirection(int a) {
    return a == Line::increasing ? Line::decreasing : (a == Line::decreasing ? Line::increasing : a);
}