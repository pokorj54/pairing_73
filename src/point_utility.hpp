#pragma once

#include <vector>

#include "point.hpp"

std::vector<Point> getPossiblePoints(int layer, const std::vector<Point>& obstructions);

std::vector<Point> getPossiblePoints(const std::vector<int>& layers, const std::vector<Point>& obstructions);

bool areOnSameLine(const Point& p1, const Point& p2);

Point getLeastColinearPoint(const std::vector<Point>& placed_stones, const std::vector<Point>& candidates);