#pragma once

#include <vector>

#include "player.hpp"
#include "point.hpp"
#include "utility.hpp"

struct PairingPreparer : public Player {
    PairingPreparer();
    virtual Point play(const std::vector<Point>& playerStones, const std::vector<Point>& opponentStones);
    /**
     * @brief Whether the necessary condition for the pairing strategy is satisfied 
     * 
     * @return true Board is prepared for finding the pairing strategy 
     * @return false Board is not prepared for finding the pairing strategy 
     */
    bool isFinished() const;

   private:
    bool finished;
    std::vector<int> remainingLayers;
    Point diagonalsStrategy(const std::vector<Point>& playerStones, const std::vector<Point>& opponentStones);

    Point centerStrategy(const std::vector<Point>& playerStones, const std::vector<Point>& opponentStones);
};