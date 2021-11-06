#pragma once

#include <sqlite3.h>

#include "solution_outputer.hpp"

struct SQLOutputer : public SolutionOutputer {
    SQLOutputer(string DB_filename) : DB_filename(DB_filename) {}

    void outputSolution(const array<array<array<int, 7>, 7>, 7>& solutionGrid, const Board& board) const;

    void initialize_DB();

   private:
    string DB_filename;
};