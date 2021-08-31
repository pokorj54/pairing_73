#include "hopcroft_karp.hpp"

#include <iostream>

using namespace std;


int main(void){
    HopcroftKarp hc = HopcroftKarp(3, 2);
    hc.addEdge(0, 0);
    hc.addEdge(1, 0);
    hc.addEdge(1, 1);
    assert(hc.maxBipartiteMatching() == 2);
    vector<int> right = hc.getRightPartiteMatching();
    assert(right[0] ==0);
    assert(right[1] ==1);
    vector<int> left = hc.getLeftPartiteMatching();
    assert(left[0] ==0);
    assert(left[1] ==1);
    assert(left[2] == -1);

    HopcroftKarp hc2 = HopcroftKarp(4, 4);
    hc2.addEdge(0, 1);
    hc2.addEdge(1, 2);
    hc2.addEdge(2, 3);
    assert(hc2.maxBipartiteMatching() == 3);
    vector<int> right2 = hc2.getRightPartiteMatching();
    assert(right2[0] == 4);
    assert(right2[1] == 0);
    assert(right2[2] == 1);
    assert(right2[3] == 2);
    vector<int> left2 = hc2.getLeftPartiteMatching();
    assert(left2[0] == 1);
    assert(left2[1] == 2);
    assert(left2[2] == 3);
    assert(left2[3] == -1);


    return 0;
}