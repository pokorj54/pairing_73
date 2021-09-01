#pragma once

#include "point.hpp"

#include <vector>
#include <string>

using namespace std;


struct BoardPosition{
    vector<Point> croses, circles;
    
    void addPoint(const Point & p);

    size_t pliesMade() const{
        return croses.size() + circles.size();
    }

    string toString();
};

