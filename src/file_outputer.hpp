#pragma once

#include <fstream>
#include <iostream>

#include "solution_outputer.hpp"

using std::array;
using std::iostream;

struct FileOutputer : public SolutionOutputer {
    FileOutputer(const std::string& output_folder) : output_folder(output_folder) {}

    void outputSolution(array<array<array<int, 7>, 7>, 7> solutionGrid, const Board& board) {
        std::string filename = output_folder + board.nameFile();
        std::ofstream fileStream(filename, std::ios::out);
        printSolution(solutionGrid, fileStream);
        fileStream.close();
    }

   private:
    void printSolution(const array<array<array<int, 7>, 7>, 7>& solution, ostream& os) {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                for (int k = 0; k < 7; ++k) {
                    os << solution[i][j][k] << '\t';
                }
                os << endl;
            }
            os << endl;
        }
    }

    string output_folder;
};