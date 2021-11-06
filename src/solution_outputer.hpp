#pragma once

#include <array>

#include "board.hpp"

using std::array;

class SolutionOutputer {
    void outputSolution(array<array<array<int, 7>, 7>, 7> solutionGrid, const Board& board);
};