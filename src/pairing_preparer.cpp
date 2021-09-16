#include "pairing_preparer.hpp"

#include <cassert>
#include <vector>

#include "player.hpp"
#include "point.hpp"
#include "point_utility.hpp"
#include "utility.hpp"

using namespace std;

PairingPreparer::PairingPreparer() : finished(false) {}
Point PairingPreparer::play(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
    assert(opponentStones.size() == playerStones.size() + 1);
    return opponentStones[0] == Point(3, 3, 3) ? diagonalsStrategy(playerStones, opponentStones) : centerStrategy(playerStones, opponentStones);
}

bool PairingPreparer::isFinished() const {
    return finished;
}

Point PairingPreparer::diagonalsStrategy(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
    if (opponentStones.size() == 1) {
        remainingLayers = {1, 2, 4, 5, 6};  // without 0 (taken) and 3 (only center)
        return Point(0, 0, 0);
    }
    // ply 2,3 - easy main diagonal
    if (opponentStones.size() < 4) {
        int lastLayer = opponentStones[opponentStones.size() - 1].x;
        lastLayer = isInVector(remainingLayers, lastLayer) ? lastLayer : remainingLayers[0];
        remainingLayers.erase(remove(remainingLayers.begin(), remainingLayers.end(), lastLayer));
        vector<Point> possibleSpots = getPossiblePoints(lastLayer, opponentStones);
        Point next_stone = getLeastColinearPoint(playerStones, possibleSpots);
        return next_stone;
    }
    //ply 4 - not so easy main diagonal - guaranteed 1 colinear circle, but could be more
    vector<Point> possibleSpots = getPossiblePoints(remainingLayers, opponentStones);
    Point next_stone = getLeastColinearPoint(playerStones, possibleSpots);
    finished = true;
    return next_stone;
}

Point PairingPreparer::centerStrategy(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
    if (opponentStones.size() == 1) {
        remainingLayers = {0, 1, 2, 4, 5, 6};
        return Point(3, 3, 3);
    }
    // ply 2, any diagonal is ok
    if (opponentStones.size() == 2) {
        int lastLayer = opponentStones[opponentStones.size() - 1].x;
        lastLayer = isInVector(remainingLayers, lastLayer) ? lastLayer : remainingLayers[0];
        remainingLayers.erase(remove(remainingLayers.begin(), remainingLayers.end(), lastLayer));
        vector<Point> possibleSpots = getPossiblePoints(lastLayer, opponentStones);
        Point next_stone = getLeastColinearPoint(playerStones, possibleSpots);
        return next_stone;
    }
    // ply 3
    vector<Point> possibleSpots = getPossiblePoints(remainingLayers, opponentStones);
    Point next_stone = getLeastColinearPoint(playerStones, possibleSpots);
    finished = true;
    return next_stone;
}