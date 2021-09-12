#pragma once

#include "board.hpp"
#include "player.hpp"

struct Match {
    static Board play(Player& first, Player& second, function<bool(Board)> shold_end) {
        Board result;
        while (true) {
            if (shold_end(result)) {
                break;
            }
            result.addPly(first.play(result.getCrosses(), result.getCircles()));
            if (shold_end(result)) {
                break;
            }
            result.addPly(second.play(result.getCircles(), result.getCrosses()));
        }
        return result;
    }
};
