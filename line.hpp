#pragma once

#include "point.hpp"

#include <vector>

using namespace std;


/*
* Represents a winning line in 7^3
*/
struct Line{
    static const int increasing = -1;
    static const int decreasing = 7;

    int x,y,z;
    Line(int x, int y, int z): x(x), y(y), z(z){
        assert(x >= -1 && x <= 7);
        assert(y >= -1 && y <= 7);
        assert(z >= -1 && z <= 7);
        assert(!isConstant(x) || !isConstant(y) || !isConstant(z));
    }

    vector<Point> getPointsOnLine() const;

    bool containsPoint(const Point & point) const;

    static constexpr vector<Line> generateAllLines();

    bool operator==(const Line & o) const{
         return x == o.x && y == o.y && z == o.z;
    }

    static bool isConstant(int a){
        return a >= 0 && a <7;
    }
};

namespace std
{
    template<> 
    struct hash<Line>
    {
        std::size_t operator()(const Line & line) const noexcept
        {
            return (line.x + 1) + (line.y+1)*9 + (line.z+1)*9*9; 
        }
    };
}