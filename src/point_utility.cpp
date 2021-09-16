#include "point_utility.hpp"

#include <cassert>

#include "utility.hpp"

using namespace std;

vector<Point> getPossiblePoints(int layer, const vector<Point>& obstructions) {
    vector<Point> spots = {
        Point(layer, layer, layer),
        Point(layer, layer, 7 - layer - 1),
        Point(layer, 7 - layer - 1, layer),
        Point(layer, 7 - layer - 1, 7 - layer - 1)};
    vector<Point> result;
    for (const Point& spot : spots) {
        if (!isInVector(obstructions, spot)) {
            result.push_back(spot);
        }
    }
    return result;
}

vector<Point> getPossiblePoints(const vector<int>& layers, const vector<Point>& obstructions) {
    vector<Point> result;
    for (int layer : layers) {
        vector<Point> layerSpots = getPossiblePoints(layer, obstructions);
        result.insert(result.end(), layerSpots.begin(), layerSpots.end());
    }
    return result;
}

bool areOnSameLine(const Point& p1, const Point& p2) {
    vector<int> differences;
    if (p1.x != p2.x) {
        differences.push_back(abs(p1.x - p2.x));
    }
    if (p1.y != p2.y) {
        differences.push_back(abs(p1.y - p2.y));
    }
    if (p1.z != p2.z) {
        differences.push_back(abs(p1.z - p2.z));
    }
    for (int diff : differences) {
        if (diff != differences[0]) {
            return false;
        }
    }
    return true;
}

Point getLeastColinearPoint(const vector<Point>& placed_stones, const vector<Point>& candidates) {
    assert(candidates.size() > 0);
    const Point* best_Point = nullptr;
    int lowest_colinearity = INT32_MAX;
    for (const Point& candidate : candidates) {
        int candidate_count = 0;
        for (const Point& stone : placed_stones) {
            if (areOnSameLine(stone, candidate)) {
                ++candidate_count;
            }
        }
        if (candidate_count < lowest_colinearity) {
            lowest_colinearity = candidate_count;
            best_Point = &candidate;
        }
    }
    return *best_Point;
}