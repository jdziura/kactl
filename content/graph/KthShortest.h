/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: N/A
 * Description: Given directed weighted graph with non-negative edge weights gets K-th
 * shortest walk (not necessarily simple) or $-1$ if no next path (can only happen in DAG).
 * Time: O(m \log m + k \log m)
 * Memory: O(m \log m + k \log m) (uses persistent heaps)
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

constexpr ll INF = 1e18;
struct Eppstein {
	using T = ll; using Edge = pair<int, T>;
	struct Node { int E[2] = {}, s = 0; Edge x; };
	T shortest; // Shortest path length
	priority_queue<pair<T, int>> Q;
	vector<Node> P{1}; vi h;
	Eppstein(vector<vector<Edge>>& G, int s, int t) {
		int n = sz(G); vector<vector<Edge>> H(n);
		rep(i,0,n) for(auto &[j, w] : G[i])
			H[j].push_back({i,w});
		vi ord, par(n, -1); vector<T> d(n, -INF);
		Q.push({d[t] = 0, t});
		while (!Q.empty()) {
			auto [dd, v] = Q.top(); Q.pop();
			if (d[v] == dd) {
				ord.push_back(v);
				for(auto &[u, w] : H[v])
				if (dd-w > d[u]) {
					Q.push({d[u] = dd-w, u});
					par[u] = v;
				}
			}
		}
		if ((shortest = -d[s]) >= INF) return;
		h.resize(n);
		for(auto &v : ord) {
			int p = par[v]; if (p+1) h[v] = h[p];
			for(auto &[u, w] : G[v]) if (d[u] > -INF) {
				T k = w - d[u] + d[v];
				if (k || u != p)
					h[v] = push(h[v], {u, k});
				else p = -1;
			}
		}
		P[0].x.first = s; Q.push({0, 0});
	}
	int push(int t, Edge x) {
		P.push_back(P[t]);
		if (!P[t = sz(P)-1].s || P[t].x.second >= x.second)
			swap(x, P[t].x);
		if (P[t].s) {
			int i = P[t].E[0], j = P[t].E[1];
			int d = P[i].s > P[j].s;
			int k = push(d ? j : i, x);
			P[t].E[d] = k; // Don't inline k!
		}
		P[t].s++; return t;
	}
	ll nextPath() { // next length, -1 if no next path
		if (Q.empty()) return -1;
		auto [d, v] = Q.top(); Q.pop();
		for (int i : P[v].E) if (i)
			Q.push({ d-P[i].x.second+P[v].x.second, i });
		int t = h[P[v].x.first];
		if (t) Q.push({d - P[t].x.second, t });
		return shortest - d; } };
