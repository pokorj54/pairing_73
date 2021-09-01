#pragma once

#include "point.hpp"
#include "utility.hpp"

#include <vector>
#include <string>

using namespace std;


struct BoardPosition{
    vector<Point> croses, circles;
    
    void addPoint(const Point & p);

    size_t pliesMade() const{
        return croses.size() + circles.size();
    }

    void addPly(const Point & point){
        assert(!isInVector(croses, point) && !isInVector(circles, point));
        if(pliesMade() % 2 == 0){
            croses.push_back(point);
        }else{
            circles.push_back(point);
        }
    }

    string toString();
};

