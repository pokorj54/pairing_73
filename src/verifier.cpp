#include <cassert>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

const int n = 7;
int game[n][n][n];

const int cross = -1;
const int circle = -2;

bool loadGame(istream& is) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (!is.good()) {
                    return false;
                }
                is >> game[i][j][k];
            }
        }
    }
    return true;
}

// for given int returns nth_element of
using index_to_point = function<int(int)>;

int valueAt(int i, const index_to_point& a, const index_to_point& b, const index_to_point& c) {
    assert(i >= 0 && i < n);
    assert(a(i) >= 0 && a(i) < n);
    assert(b(i) >= 0 && b(i) < n);
    assert(c(i) >= 0 && c(i) < n);
    return game[a(i)][b(i)][c(i)];
}

bool lineIsCovered(const index_to_point& a, const index_to_point& b, const index_to_point& c) {
    // covered by circle
    for (int i = 0; i < n; ++i) {
        if (valueAt(i, a, b, c) == circle) {
            return true;
        }
    }
    // two same pozitive values at the line - trying all posibilities
    for (int i = 0; i < n; ++i) {
        if (valueAt(i, a, b, c) <= 0) {
            continue;
        }
        for (int j = i + 1; j < n; ++j) {
            if (valueAt(j, a, b, c) <= 0) {
                continue;
            }
            if (valueAt(i, a, b, c) == valueAt(j, a, b, c)) {
                return true;
            }
        }
    }
    return false;
}

// =============================
// index_to_point functions

int increasing(int i) {
    return i;
}

int decreasing(int i) {
    return n - i - 1;
}

index_to_point constant(int c) {
    return [c](int x) {(void)x; return c; };
}

// ==========================

bool areAllLinesCovered() {
    // prparing functions
    vector<index_to_point> functions;
    for (int i = 0; i < n; ++i) {
        functions.push_back(constant(i));
    }
    functions.push_back(increasing);
    functions.push_back(decreasing);
    // iterating all lines
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < n + 2; ++j) {
            for (int k = 0; k < n + 2; ++k) {
                if (i < n && j < n && k < n) {  // all constant case
                    continue;
                }
                if (!lineIsCovered(functions[i], functions[j], functions[k])) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isPairigValid() {
    unordered_map<int, int> values;
    // adding to map
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int value = game[i][j][k];
                if (values.count(value) == 0) {
                    values[value] = 1;
                } else {
                    values[value] += 1;
                }
            }
        }
    }
    // same number of circles and crosses
    if (values[circle] != values[cross]) {
        return false;
    }
    // every number is exactly two time present
    for (const pair<int, int> p : values) {  // if reference is present I got warning but don't understand it
        if (p.first <= 0) {
            continue;
        }
        if (p.second != 2) {
            return false;
        }
    }
    return true;
}

int main(void) {
    if (!loadGame(cin)) {
        cout << "Invalid input" << endl;
        return 1;
    }
    if (!isPairigValid()) {
        cout << "Pairing is not valid" << endl;
        return 1;
    }
    if (!areAllLinesCovered()) {
        cout << "Not all lines covered" << endl;
        return 1;
    }
    cout << "All lines covered" << endl;
    return 0;
}