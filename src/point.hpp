#pragma once

#include <functional>
#include <iostream>

/**
 * @brief Class for representing point in 7^3. Coordinates are from 0 to 6 (included).
 * 
 */
struct Point {
    int x, y, z;
    Point(int x, int y, int z);

    bool operator==(const Point& o) const;

    static Point first();

    bool hasNext() const;

    Point next() const;

    static Point loadPoint(std::istream& is);

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << p.x << p.y << p.z;
    }
};

namespace std {
template <>
struct hash<Point> {
    std::size_t operator()(const Point& point) const noexcept {
        return point.x + point.y * 7 + point.z * 7 * 7;
    }
};
}  // namespace std