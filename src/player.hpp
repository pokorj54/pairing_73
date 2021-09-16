#pragma once

#include "point.hpp"

struct Player {
    virtual Point play(const std::vector<Point>& playerStones, const std::vector<Point>& opponentStones) = 0;
};
