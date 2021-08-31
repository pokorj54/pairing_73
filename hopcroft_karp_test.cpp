#include "hopcroft_karp.hpp"

int main(void){
    HopcroftKarp hc = HopcroftKarp(3, 2);
    hc.addEdge(0, 0);
    hc.addEdge(1, 0);
    hc.addEdge(1, 1);
    assert(hc.maxbpm() == 2);
    vector<int> right = hc.getrightPartiteMatching();
    assert(right[0] ==0);
    assert(right[1] ==1);

    HopcroftKarp hc2 = HopcroftKarp(4, 4);
    hc2.addEdge(0, 1);
    hc2.addEdge(1, 2);
    hc2.addEdge(2, 3);
    assert(hc2.maxbpm() == 3);
    vector<int> right2 = hc2.getrightPartiteMatching();
    assert(right2[1] == 0);
    assert(right2[2] == 1);
    assert(right2[3] == 2);
    
    return 0;
}