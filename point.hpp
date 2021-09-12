#pragma once

#include <cassert>
#include <functional>
#include <iostream>

using namespace std;

/*
* Class for representing point in 7^3
*/
struct Point {
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) {
        assert(x >= 0 && x < 7);
        assert(y >= 0 && y < 7);
        assert(z >= 0 && z < 7);
    }

    bool operator==(const Point& o) const {
        return x == o.x && y == o.y && z == o.z;
    }

    static Point first() {
        return Point(0, 0, 0);
    }

    bool hasNext() const {
        return !(x == 6 && y == 6 && z == 6);
    }

    Point next() const {
        if (x == 6 && y == 6 && z == 6) {
            throw;
        }
        if (y == 6 && z == 6) {
            return Point(x + 1, 0, 0);
        } else if (z == 6) {
            return Point(x, y + 1, 0);
        } else {
            return Point(x, y, z + 1);
        }
    }

    static Point loadPoint(istream& is) {
        int x, y, z;
        cin >> x >> y >> z;
        assert(is.good());
        return Point(x, y, z);
    }

    friend ostream& operator<<(ostream& os, const Point& point);
};

ostream& operator<<(ostream& os, const Point& p) {
    return os << p.x << p.y << p.z;
}

namespace std {
template <>
struct hash<Point> {
    std::size_t operator()(const Point& point) const noexcept {
        return point.x + point.y * 7 + point.z * 7 * 7;
    }
};
}  // namespace std