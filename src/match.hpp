#pragma once

#include "board.hpp"
#include "player.hpp"

/**
 * @brief Class that provides a match between two players
 * 
 */
struct Match {
    /**
     * @brief Provides match between first and second player until condition should_end is met
     * 
     * @param first Player who playes first 
     * @param second Player who plays second
     * @param should_end Function that takes current board and determines if the match should be ended (the Board returned) 
     * @return Board Board after the match was ended.
     */
    static Board play(Player& first, Player& second, function<bool(Board)> should_end) {
        Board result;
        while (true) {
            if (should_end(result)) {
                break;
            }
            result.addPly(first.play(result.getCrosses(), result.getCircles()));
            if (should_end(result)) {
                break;
            }
            result.addPly(second.play(result.getCircles(), result.getCrosses()));
        }
        return result;
    }
};
