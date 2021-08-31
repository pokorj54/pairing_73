#include <vector>
#include <queue>
#include <climits>
#include <cassert>

using namespace std;

// Algorithm for bipartite matching
// Complexity: O(sqrt(N) * M)
// Author: Jara Urban
// does bfs from unmatched nodes while alternating edges between
// unmatched, matched, ... stops when it finds and unmatched node
// (has to be on the right side). then it does dfses on the created
// graph (finds alternating paths). repeats everything.
struct HopcroftKarp{
	/*
    * n is the size of left partite and m is the size of right partite
    * vertices of the partites are implicitly ordered from 0 to n-1 for the left partite 
    * and from 0 to m-1 for the right partite
    */
    HopcroftKarp(int n,int m):n(n),m(m),ma(n,-1),mb(m,n),g(n){}

	void addEdge(int u,int v){
        assert(u < n);
        assert(v < m);
        g[u].push_back(v);
    }

	int maxbpm(){
		int res=0;
		while(bfs())
			for(int i=0;i<n;++i)
				res+=ma[i]==-1&&dfs(i);
		return res;
	}

    const vector<int> & getleftpartiteMatching() const{
        return ma;
    }

    const vector<int> & getrightPartiteMatching() const{
        return mb;
    }

private:
	int n,m;
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