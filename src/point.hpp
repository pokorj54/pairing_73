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

    /**
     * @brief First point of order on points
     * 
     * @return Point 
     */
    static Point first();

    /**
     * @brief Determines if next element in ordering started by first() and continued by sequence of next() exist
     * 
     * @return true this point has next
     * @return false this point does not have next
     */
    bool hasNext() const;

    /**
     * @brief Advances to next element in ordering started by first()
     * 
     * @return Point the point after this point in the point ordering started by first() and continuesd by next()
     */
    Point next() const;

    /**
     * @brief loads point from input stream
     * 
     * @param is Input stream from the point is read
     * @return Point the read point
     */
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