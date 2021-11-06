#include "utility.hpp"

string solution_to_string(const array<array<array<int, 7>, 7>, 7>& solution) {
    stringstream ss;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int k = 0; k < 7; ++k) {
                ss << solution[i][j][k] << '\t';
            }
            ss << endl;
        }
        ss << endl;
    }
    return ss.str();
}