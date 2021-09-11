#pragma once

#include "player.hpp"
#include "utility.hpp"

#include <vector>

using namespace std;

struct CannotPlayMoveException : public exception{

};


struct GivenMovesPlayer : Player{
    GivenMovesPlayer(const vector<Point> & moves ):moves(moves){}

    virtual Point play(const vector<Point> & playerStones, const vector<Point> & opponentStones){
        size_t i = playerStones.size();
        if(i >= moves.size()){
            moves.push_back(Point::first());
        }
        Point nextMove = moves[i];
        if(isInVector(playerStones, nextMove) || isInVector(opponentStones, nextMove)){
            throw CannotPlayMoveException();
        }
        return nextMove;
    }

    private:
        vector<Point> moves;

};
