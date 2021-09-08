#pragma once

#include "point.hpp"
#include "utility.hpp"

#include <vector>
#include <string>

using namespace std;


struct BoardPosition{
    vector<Point> crosses, circles;
    
    void addPoint(const Point & p);

    size_t pliesMade() const{
        return crosses.size() + circles.size();
    }

    void addPly(const Point & point){
        assert(!isInVector(crosses, point) && !isInVector(circles, point));
        if(pliesMade() % 2 == 0){
            crosses.push_back(point);
        }else{
            circles.push_back(point);
        }
    }

    friend ostream & operator << (ostream & os, const BoardPosition & board ){
        for(size_t i = 0; i < board.crosses.size(); ++i){
            if(i != 0){
                os << " ";
            }
            os << board.crosses[i];
            if(i < board.circles.size()){
                cout << " " << board.circles[i];
            }
        }
        return os;
    };
};

