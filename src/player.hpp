#pragma once

#include "point.hpp"

struct Player {
    virtual Point play(const vector<Point>& playerStones, const vector<Point>& opponentStones) = 0;
};
