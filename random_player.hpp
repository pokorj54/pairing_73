#pragma once

#include <random>
#include <vector>

#include "player.hpp"
#include "utility.hpp"

using namespace std;

struct RandomPlayer : public Player {
    RandomPlayer() : distribution(0, 6) {
    }

    virtual Point play(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        Point generated = getRandomPoint();
        while (isInVector(playerStones, generated) || isInVector(opponentStones, generated)) {
            generated = getRandomPoint();
        }
        return generated;
    }

   private:
    Point getRandomPoint() {
        return Point(distribution(gen), distribution(gen), distribution(gen));
    }
    uniform_int_distribution<int> distribution;
    random_device gen;
};
