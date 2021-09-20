#include "point_utility.hpp"

#include <cassert>

#include "utility.hpp"

using namespace std;

int flip(int a) {
    return 7 - a - 1;
}

vector<Point> getPossiblePoints(int layer, const vector<Point>& obstructions) {
    vector<Point> spots = {
        Point(layer, layer, layer),
        Point(layer, layer, flip(layer)),
        Point(layer, flip(layer), layer),
        Point(layer, flip(layer), flip(layer))};
    if (layer == 3) {
        spots = {Point(3, 3, 3)};
    }
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
    if (p1 == p2) {
        return true;
    }
    vector<int> differences;  // differences in moving coordinates must be same
    vector<int> valuesp1, valuesp2;
    function<void(int, int)> lambda = [&differences, &valuesp1, &valuesp2](int a, int b) {
        if (a != b) {
            differences.push_back(abs(a - b));
            a = a > 3 ? flip(a) : a;
            b = b > 3 ? flip(b) : b;
            valuesp1.push_back(a);
            valuesp2.push_back(b);
        }
    };
    lambda(p1.x, p2.x);
    lambda(p1.y, p2.y);
    lambda(p1.z, p2.z);
    for (size_t i = 0; i < differences.size(); ++i) {
        if (differences[i] != differences[0] || valuesp1[i] != valuesp1[0] || valuesp2[i] != valuesp2[0]) {
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