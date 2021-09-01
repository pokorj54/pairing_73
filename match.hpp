#pragma once

#include "player.hpp"
#include "board_position.hpp"

struct Match{
    static BoardPosition play(Player & first, Player & second, size_t numberOfPlies){
        BoardPosition result;
        while(true){
            if(numberOfPlies == 0){
                break;
            }
            result.addPly(first.play(result.croses, result.circles));
            --numberOfPlies;
            if(numberOfPlies == 0){
                break;
            }
            result.addPly(second.play(result.circles, result.croses));
            --numberOfPlies;
        }
        return result;
    }
};
