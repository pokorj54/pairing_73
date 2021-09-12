#pragma once

#include "board_position.hpp"
#include "player.hpp"

struct Match {
    static BoardPosition play(Player& first, Player& second, function<bool(BoardPosition)> shold_end) {
        BoardPosition result;
        while (true) {
            if (shold_end(result)) {
                break;
            }
            result.addPly(first.play(result.crosses, result.circles));
            if (shold_end(result)) {
                break;
            }
            result.addPly(second.play(result.circles, result.crosses));
        }
        return result;
    }
};
