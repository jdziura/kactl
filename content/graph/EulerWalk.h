/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of pairs (node, incoming edge) in the Eulerian path/cycle
 * with src at both start and end, or empty list if no cycle/path exists.
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vector<pii> eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges); vector<pii> ret, s = {{src, -1}};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back().first, y, e, &it = its[x], end = sz(gr[x]);
		if (it == end) {
			ret.push_back(s.back()); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back({y, e});
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}
