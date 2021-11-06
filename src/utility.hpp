#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

/**
 * @brief Determines if element t is contained in vector v
 * 
 * @tparam T any element that is comparable by ==
 * @param v vector of elements
 * @param t searched element
 * @return true if v contains t
 * @return false if v does not contain t
 */
template <typename T>
bool isInVector(const vector<T>& v, T t) {
    return std::find(v.begin(), v.end(), t) != v.end();
}

template <typename T>
void _print(const T& a, ostream& os) {
    os << a;
}

template <typename T>
void _print(const pair<T, T>& v, ostream& os) {
    os << "(";
    _print(v.first, os);
    os << ", ";
    _print(v.second, os);
    os << ")";
}

template <typename T>
void _print(const set<T>& s, ostream& os) {
    os << "{";
    size_t i = 0;
    for (T t : s) {
        ++i;
        _print(t, os);
        if (i != s.size()) {
            os << ", ";
        }
    }
    os << "}";
}

template <typename T>
void _print(const vector<T>& v, ostream& os) {
    if (v.size() == 0) {
        os << "[]";
        return;
    }
    os << "[";
    for (size_t i = 0; i < v.size() - 1; ++i) {
        _print(v[i], os);
        os << ", ";
    }
    if (v.size() != 0) {
        _print(v[v.size() - 1], os);
    }
    os << "]";
}

template <typename T>
void print(T t, ostream& os) {
    _print(t, os);
}

string solution_to_string(const array<array<array<int, 7>, 7>, 7>& solution);