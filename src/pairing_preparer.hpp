#pragma once

#include <vector>

#include "player.hpp"
#include "point.hpp"
#include "utility.hpp"

using namespace std;

struct PairingPreparer : public Player {
    PairingPreparer() : finished(false) {}
    virtual Point play(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        assert(opponentStones.size() == playerStones.size() + 1);
        return opponentStones[0] == Point(3, 3, 3) ? diagonalsStrategy(playerStones, opponentStones) : centerStrategy(playerStones, opponentStones);
    }

    bool isFinished() const {
        return finished;
    }

   private:
    bool finished;
    vector<int> remainingLayers;
    Point diagonalsStrategy(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        if (opponentStones.size() == 1) {
            remainingLayers = {1, 2, 4, 5, 6};  // without 0 (taken) and 3 (only center)
            return Point(0, 0, 0);
        }
        // ply 2,3 - easy main diagonal
        if (opponentStones.size() < 4) {
            int lastLayer = opponentStones[opponentStones.size() - 1].x;
            lastLayer = isInVector(remainingLayers, lastLayer) ? lastLayer : remainingLayers[0];
            remainingLayers.erase(remove(remainingLayers.begin(), remainingLayers.end(), lastLayer));
            vector<Point> possibleSpots = getPossibleSpots(lastLayer, opponentStones);
            Point next_stone = leastColinearPoint(playerStones, possibleSpots);
            return next_stone;
        }
        //ply 4 - not so easy main diagonal - guaranteed 1 colinear circle, but could be more
        vector<Point> possibleSpots = getPossibleSpots(remainingLayers, opponentStones);
        Point next_stone = leastColinearPoint(playerStones, possibleSpots);
        finished = true;
        return next_stone;
    }

    Point centerStrategy(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        if (opponentStones.size() == 1) {
            remainingLayers = {0, 1, 2, 4, 5, 6};
            return Point(3, 3, 3);
        }
        // ply 2, any diagonal is ok
        if (opponentStones.size() == 2) {
            int lastLayer = opponentStones[opponentStones.size() - 1].x;
            lastLayer = isInVector(remainingLayers, lastLayer) ? lastLayer : remainingLayers[0];
            remainingLayers.erase(remove(remainingLayers.begin(), remainingLayers.end(), lastLayer));
            vector<Point> possibleSpots = getPossibleSpots(lastLayer, opponentStones);
            Point next_stone = leastColinearPoint(playerStones, possibleSpots);
            return next_stone;
        }
        // ply 3
        vector<Point> possibleSpots = getPossibleSpots(remainingLayers, opponentStones);
        Point next_stone = leastColinearPoint(playerStones, possibleSpots);
        finished = true;
        return next_stone;
    }

    static vector<Point> getPossibleSpots(int layer, const vector<Point>& obstructions) {
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

    static vector<Point> getPossibleSpots(const vector<int>& layers, const vector<Point>& obstructions) {
        vector<Point> result;
        for (int layer : layers) {
            vector<Point> layerSpots = getPossibleSpots(layer, obstructions);
            result.insert(result.end(), layerSpots.begin(), layerSpots.end());
        }
        return result;
    }

    static bool areOnSameLine(const Point& p1, const Point& p2) {
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

    static Point leastColinearPoint(const vector<Point>& placed_stones, const vector<Point>& candidates) {
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
};