#pragma once

#include <sqlite3.h>

#include <utility>
#include <vector>

#include "solution_outputer.hpp"

using namespace std;

struct SQLOutputer : public SolutionOutputer {
    SQLOutputer(string DB_filename);

    ~SQLOutputer();

    void outputSolution(const array<array<array<int, 7>, 7>, 7>& solutionGrid, const Board& board);

    void initialize_DB();

    void insertAllToDatabase();

   private:
    string DB_filename;
    vector<pair<array<array<array<int, 7>, 7>, 7>, Board>> buffer;
};