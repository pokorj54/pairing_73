#include "hopcroft_karp.hpp"

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


    return 0;
}