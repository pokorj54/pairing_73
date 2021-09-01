#include "hopcroft_karp.hpp"

#include "line.hpp"

#include <iostream>

using namespace std;


int main(void){
    HopcroftKarp<int, int> hc = HopcroftKarp<int, int>(3, 2);
    hc.addEdge(0, 0);
    hc.addEdge(1, 0);
    hc.addEdge(1, 1);
    assert(hc.maxBipartiteMatching() == 2);
    unordered_map<int,int> right = hc.getRightPartiteMatching();
    assert(right[0] ==0);
    assert(right[1] ==1);
    unordered_map<int,int> left = hc.getLeftPartiteMatching();
    assert(left[0] ==0);
    assert(left[1] ==1);
    assert(left.count(2) == 0);

    HopcroftKarp<int, int> hc2 = HopcroftKarp<int, int>(4, 4);
    hc2.addEdge(0, 1);
    hc2.addEdge(1, 2);
    hc2.addEdge(2, 3);
    assert(hc2.maxBipartiteMatching() == 3);
    unordered_map<int,int> right2 = hc2.getRightPartiteMatching();
    assert(right2.count(0) == 0);
    assert(right2[1] == 0);
    assert(right2[2] == 1);
    assert(right2[3] == 2);
    unordered_map<int,int> left2 = hc2.getLeftPartiteMatching();
    assert(left2[0] == 1);
    assert(left2[1] == 2);
    assert(left2[2] == 3);
    assert(left2.count(3) == 0);


    HopcroftKarp<Point, Line> hc3 = HopcroftKarp<Point, Line>(3, 3);
    hc3.addEdge(Point(0,0,0), Line(Line::increasing, 0,0));
    hc3.addEdge(Point(0,0,2), Line(Line::increasing, 0,0));
    hc3.addEdge(Point(0,0,1), Line(Line::increasing, 0,2));
    hc3.addEdge(Point(0,0,2), Line(Line::increasing, 0,1));
    hc3.addEdge(Point(0,0,1), Line(Line::increasing, 0,1));
    assert(hc3.maxBipartiteMatching() == 3);
    unordered_map<Line,Point> right3 = hc3.getRightPartiteMatching();
    assert(right3.at(Line(Line::increasing, 0,0)) == Point(0,0,0));
    assert(right3.at(Line(Line::increasing, 0,1)) == Point(0,0,2));
    assert(right3.at(Line(Line::increasing, 0,2)) == Point(0,0,1));
    unordered_map<Point,Line> left3 = hc3.getLeftPartiteMatching();
    assert(left3.at(Point(0,0,0)) == Line(Line::increasing, 0,0));
    assert(left3.at(Point(0,0,1)) == Line(Line::increasing, 0,2));
    assert(left3.at(Point(0,0,2)) == Line(Line::increasing, 0,1));
    
    return 0;
}