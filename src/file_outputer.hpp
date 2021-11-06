#pragma once

#include <fstream>
#include <iostream>

#include "solution_outputer.hpp"
#include "utility.hpp"

using std::array;
using std::iostream;

struct FileOutputer : public SolutionOutputer {
    FileOutputer(const std::string& output_folder) : output_folder(output_folder) {}

    void outputSolution(const array<array<array<int, 7>, 7>, 7>& solutionGrid, const Board& board) {
        std::string filename = output_folder + board.toString('_') + ".txt";
        std::ofstream fileStream(filename, std::ios::out);
        fileStream << solution_to_string(solutionGrid);
        fileStream.close();
    }

   private:
    string output_folder;
};