#include "point.hpp"

#include <cassert>

using namespace std;

Point::Point(int x, int y, int z) : x(x), y(y), z(z) {
    assert(x >= 0 && x < 7);
    assert(y >= 0 && y < 7);
    assert(z >= 0 && z < 7);
}

bool Point::operator==(const Point& o) const {
    return x == o.x && y == o.y && z == o.z;
}

Point Point::first() {
    return Point(0, 0, 0);
}

bool Point::hasNext() const {
    return !(x == 6 && y == 6 && z == 6);
}

Point Point::next() const {
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

Point Point::loadPoint(istream& is) {
    char x, y, z;
    cin >> x >> y >> z;
    assert(is.good());
    return Point(x - '0', y - '0', z - '0');
}

string Point::toString() const {
    return to_string(x) + to_string(y) + to_string(z);
}
