#pragma once

#include <functional>
#include <vector>

#include "point.hpp"

using namespace std;

/**
 * @brief Represents a winning line in 7^3
 * 
 */
struct Line {
    /**
     * @brief Constant representing increasing coordinate of a line
     * 
     */
    static const int increasing = -1;

    /**
     * @brief Constant representing decreasing coordinate of a line
     * 
     */
    static const int decreasing = 7;

    int x, y, z;
    Line(int x, int y, int z);

    /**
     * @brief Gets all points that lies on this line
     * 
     * @return vector<Point> all those points
     */
    vector<Point> getPointsOnLine() const;

    /**
     * @brief Calculates whether point lies on this line
     * 
     * @param point Point in question
     * @return true if the point lies on this line
     * @return false if the point does not lie on this line
     */
    bool containsPoint(const Point& point) const;

    /**
     * @brief generates all winning lines on 7^3, all of them in cannonical form 
     * 
     * @return vector<Line> alll the winning lines
     */
    static vector<Line> generateAllCanonicalLines();

    /**
     * @brief Equality on lines representations, every line representation is it's own class (cannonical and the second form is different object)
     * 
     * @param other second line to compare with
     * @return true if this and the other line are identical lines in identical representations
     * @return false else
     */
    bool operator==(const Line& other) const;

    /**
     * @brief Determines if current representation is cannonical. For each line exists 2 representations, it is guaranteed than exactly one of them is canonical
     * 
     * @return true if it is canonical representation of the representing line
     * @return false if it is not canonical representation of the representing line
     */
    bool isCanonical() const;

    /**
     * @brief Gets line representing the same line but directions are swapped
     * 
     * @return Returns line that covers the same points but is flipped ( increasing -> decreasing and vice versa) 
     */
    Line getFlippedLine() const;

    /**
    * @brief Determines whether coordinate of line is constant
    * 
    * @param a coordinate of a line
    * @return true the coordinate is constant (0, ..., 6)
    * @return false the coordinate is not constant (increasing or decreasing)
    */
    static bool isConstant(int a);

    /**
     * @brief Flips direction of a coordinate of a line (increasing to decreasing and vice versa)
     * 
     * @param a coordinate of a line
     * @return int flipped coordinate
     */
    static int flipDirection(int a);
};

namespace std {
template <>
struct hash<Line> {
    std::size_t operator()(const Line& line) const noexcept {
        return (line.x + 1) + (line.y + 1) * 9 + (line.z + 1) * 9 * 9;
    }
};
}  // namespace std