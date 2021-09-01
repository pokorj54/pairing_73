#pragma once

#include <cassert>
/*
* Class for representing point in 7_3
*/
struct Point{
    int x, y, z;
    Point(int x, int y, int z): x(x), y(y), z(z){
        assert(x >= 0 && x <7);
        assert(y >= 0 && y <7);
        assert(z >= 0 && z <7);
    }

    bool operator==(const Point & o) const{
         return x == o.x && y == o.y && z == o.z;
    }
};

namespace std
{
    template<> 
    struct hash<Point>
    {
        std::size_t operator()(const Point & point) const noexcept
        {
            return point.x + point.y*7 + point.z*7*7; 
        }
    };
}