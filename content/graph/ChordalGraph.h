/**
 * Author: Shahjalal Shohag
 * Date: 2022-10-27
 * License: MIT
 * Source: https://github.com/ShahjalalShohag/code-library/blob/master/Graph%20Theory/Chordal%20Graph.cpp
 * Description: A graph is chordal if any cycle C >= 4 has a chord i.e. an edge (u, v) where u and v is in the cycle but (u, v) is not
 * A perfect elimination ordering (PEO) in a graph is an ordering of the vertices of the graph such that,
 * $\forall v:$ v and its neighbors that occur after v in the order (later) form a clique.
 * A graph is chordal if and only if it has a perfect elimination ordering.
 * Optimal vertex coloring of the graph: first fit: col[i] = smallest color that is not used by any of the neighbours earlier in PEO.
 * Max clique = Chromatic number = 1+max over number of later neighbours for all vertices.
 * Chromatic polynomial = $(x-d_1)(x-d_2)\dots(x-d_n)$ where $d_i$ = number of neighbors of i later in PEO.
 * Time: O(n+m)
 * Status: Tested on https://www.codechef.com/problems/EGGFREE
 */
#pragma once

// 0-indexed, adj list
vi perfectEliminationOrder(vector<vi>& g) {
	int top = 0, n = sz(g);
	vi ord, vis(n), indeg(n);
	vector<vi> bucket(n);
	rep(i, 0, n) bucket[0].push_back(i);
	for(int i = 0; i < n; ) {
		while(bucket[top].empty()) --top;
		int u = bucket[top].back();
		bucket[top].pop_back();
		if(vis[u]) continue;
		ord.push_back(u);
		vis[u] = 1;
		++i;
		for(int v : g[u]) {
			if(vis[v]) continue;
			bucket[++indeg[v]].push_back(v);
			top = max(top, indeg[v]);
		}
	}
	reverse(all(ord));
	return ord;
}
//ord = perfectEliminationOrder(g)
bool isChordal(vector<vi>& g, vi ord) {
	int n = sz(g);
	set<pii> edg;
	rep(i, 0, n) for(auto v:g[i]) edg.insert({i,v});
	vi pos(n); rep(i, 0, n) pos[ord[i]] = i;
	rep(u, 0, n){
		int mn = n;
		for(auto v : g[u]) if(pos[u] < pos[v])
      mn=min(mn,pos[v]);
		if(mn != n) {
			int p = ord[mn];
			for(auto v : g[u])
        if(pos[v]>pos[u] && v!=p && !edg.count({v, p}))
          return 0;
		}
	}
	return 1;
}