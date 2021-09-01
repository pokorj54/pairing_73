#pragma once

#include "point.hpp"

#include <vector>
#include <functional>

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

    vector<Point> getPointsOnLine() const{
        vector<Point> result;
        int a = x;
        int b = y;
        int c = z;
        for(int i = 0; i < 7; ++i){
            if(x == increasing){
                ++a;
            }else if(x == decreasing){
                --a;
            }
            if(y == increasing){
                ++b;
            }else if(y == decreasing){
                --b;
            }
            if(z == increasing){
                ++c;
            }else if(z == decreasing){
                --c;
            }
            result.push_back(Point(a,b,c));
        }
        return result;
    }

    bool containsPoint(const Point & point) const{
        for(const Point & p : getPointsOnLine()){
            if(p == point){
                return true;
            }
        }
        return false;
    }

    static vector<Line> generateAllCanonicalLines(){
        vector<Line> result;
        for(int i = -1; i <= 7; ++i){
            for(int j = -1; j <= 7; ++j){
                for(int k = -1; k <= 7; ++k){
                    if(isConstant(i) && isConstant(j) && isConstant(k)){
                        continue;
                    }
                    Line l = Line(i, j, k);
                    if(l.isCanonical()){
                        result.push_back(l);
                    }
                }
            }
        }
        return result;
    }

    bool operator==(const Line & o) const{
         return x == o.x && y == o.y && z == o.z;
    }

    bool isCanonical() const{
        return (x == increasing) 
            || (x != decreasing && y == increasing) 
            || (x != decreasing && y != decreasing && z == increasing);
    }

    /*
    * Returns new line that covers the same points but is flipped ( increasing -> decreasing and vice versa)
    */
    Line getFlippedLine() const{
        return Line(flipDirection(x), flipDirection(y), flipDirection(z));
    }

    static bool isConstant(int a){
        return a >= 0 && a <7;
    }

    static int flipDirection(int a){
        return a == increasing ? decreasing : (a == decreasing ? increasing : a); 
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