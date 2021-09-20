#pragma once

#include <vector>

#include "player.hpp"
#include "utility.hpp"

using namespace std;
/**
 * @brief Exception signaling that GivenMovePlayer cannot play according given moves
 * 
 */
struct CannotPlayMoveException : public exception {
};

/**
 * @brief Player that is given sequence of points (moves) and plays it's ith ply as a the ith given point 
 * 
 */
struct GivenMovesPlayer : Player {
    GivenMovesPlayer(const vector<Point>& moves) : moves(moves) {}

    virtual Point play(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        size_t i = playerStones.size();
        if (i >= moves.size()) {
            moves.push_back(Point::first());
        }
        Point nextMove = moves[i];
        if (isInVector(playerStones, nextMove) || isInVector(opponentStones, nextMove)) {
            throw CannotPlayMoveException();
        }
        return nextMove;
    }

   private:
    vector<Point> moves;
};
