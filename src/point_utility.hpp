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

std::vector<Point> getPossiblePoints(int layer, const std::vector<Point>& obstructions);

std::vector<Point> getPossiblePoints(const std::vector<int>& layers, const std::vector<Point>& obstructions);

/**
 * @brief Calculates whether two points lies on the same line
 * 
 * @param p1 a Point of 7^3
 * @param p2 a Point of 7^3
 * @return if exist such a line that both points are on it
 */
bool areOnSameLine(const Point& p1, const Point& p2);

Point getLeastColinearPoint(const std::vector<Point>& placed_stones, const std::vector<Point>& candidates);