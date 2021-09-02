#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <cassert>

using namespace std;

// Todo templatovat

// Algorithm for bipartite matching
// Complexity: O(sqrt(N) * M)
// Author: Jara Urban
// does bfs from unmatched nodes while alternating edges between
// unmatched, matched, ... stops when it finds and unmatched node
// (has to be on the right side). then it does dfses on the created
// graph (finds alternating paths). repeats everything.
template<typename L, typename R>
struct HopcroftKarp{
	/*
    * n is the size of left partite and m is the size of right partite
    * vertices of the partites are implicitly ordered from 0 to n-1 for the left partite 
    * and from 0 to m-1 for the right partite
    */
    HopcroftKarp(int n,int m):n(n),m(m),ma(n,-1),mb(m,n),g(n){}

	void addEdge(L u,R v){
		int uid, vid;
		if(leftToInt.count(u) == 0){
			leftToInt.insert({u, leftToInt.size()});
			intToLeft.push_back(u);
		}
		if(rightToInt.count(v) == 0){
			rightToInt.insert({v, rightToInt.size()});
			intToRight.push_back(v);
		}
		uid = leftToInt.at(u);
		vid = rightToInt.at(v);
        assert(uid < n);
        assert(vid < m);
        g[uid].push_back(vid);
    }
	
	/*
	* Calculates the maximum bipartite matching size
	*/
	size_t maxBipartiteMatching(){
		size_t res=0;
		while(bfs())
			for(int i=0;i<n;++i)
				res+=ma[i]==-1&&dfs(i);
		return res;
	}

	/*
	* Returns for each vertice in the left partite what is his pair in the right partite
	*/
    unordered_map<L, R> getLeftPartiteMatching() const{
		unordered_map<L, R> result;
		for(const L & l : intToLeft){
			result.insert({l, intToRight.at(ma.at(leftToInt.at(l)))});
		}
        return result;
    }

	/*
	* Returns for each vertice in the right partite what is his pair in the left partite
	*/
    unordered_map<R, L> getRightPartiteMatching() const{
        unordered_map<R, L> result;
		for(const R & r : intToRight){
			result.insert({r, intToLeft.at(mb.at(rightToInt.at(r)))});
		}
        return result;
    }

	size_t leftPartiteSize() const{
		return n;
	}

	size_t rightPartiteSize() const{
		return m;
	}

private:
	int n,m;
	unordered_map<L,int> leftToInt;
	unordered_map<R,int> rightToInt;
	vector<L> intToLeft;
	vector<R> intToRight;

	vector<int>ma,mb,dist; // n is a dummy node
	vector<vector<int>>g;
	bool bfs(){
		dist.assign(n+1,INT_MAX);
		queue<int>q;
		for(int i=0;i<n;++i)
			if(ma[i]==-1){
				q.push(i);
				dist[i]=0;
			}
		while(q.size()){
			int u=q.front();q.pop();
			if(u==n)break;
			for(auto v:g[u])if(dist[mb[v]]==INT_MAX){
				dist[mb[v]]=dist[u]+1;
				q.push(mb[v]);
			}
		}
		return dist[n]!=INT_MAX;
	}
	bool dfs(int u){
		if(u==n)return true;
		for(auto v:g[u])if(dist[mb[v]]==dist[u]+1&&dfs(mb[v])){
			mb[v]=u;
			ma[u]=v;
			return true;
		}
		dist[u]=INT_MAX;
		return false;
	}
};