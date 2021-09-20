#pragma once

#include <vector>

#include "point.hpp"

/**
 * @brief Flips coordinate on a hypercube with side 7
 * 
 * @param a coordinate of a point
 * @return int flipped coordinate around the center
 */
int flip(int a);

/**
 * @brief In give layer find points o space diagonals that are not in obstuctions
 * 
 * @param layer specifies layer that is searched
 * @param obstructions forbidden points
 * @return std::vector<Point> All the points that are on space diagonals in given layer that are not in obstructions.
 */
std::vector<Point> getPossiblePoints(int layer, const std::vector<Point>& obstructions);

/**
 * @brief In given layers find points on space diagonals that are not in obstructions
 * 
 * @param layers in which possible point are searched
 * @param obstructions forbidden points
 * @return std::vector<Point> All the points that are on space diagonals in given alyers and are not in obstructions
 */
std::vector<Point> getPossiblePoints(const std::vector<int>& layers, const std::vector<Point>& obstructions);

/**
 * @brief Calculates whether two points lies on the same line
 * 
 * @param p1 a Point of 7^3
 * @param p2 a Point of 7^3
 * @return if exist such a line that both points are on it
 */
bool areOnSameLine(const Point& p1, const Point& p2);

/**
 * @brief Get the Least Colinear Point from cadidates to placed stones
 * 
 * @param placed_stones Points that are placed 
 * @param candidates Points that can be placed, the least collinear to placed_stones will be chosen and added to them
 * @return Point that is on fewest lines occupied by placed_stones
 */
Point getLeastColinearPoint(const std::vector<Point>& placed_stones, const std::vector<Point>& candidates);