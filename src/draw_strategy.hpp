#include <array>

#include "board.hpp"
using std::array;

array<array<array<int, 7>, 7>, 7> compute_draw_strategy(const Board& board);
