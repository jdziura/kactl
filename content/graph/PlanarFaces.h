/**
 * Author: Adam Soltan
 * Description: Finds the faces of a simple planar graph and returns
 * the vertex indices for each face in either clockwise (inner)
 * or counterclockwise (outer) order. Disconnected graphs may have multiple
 * outer faces and require careful handling.
 * Time: O(n \log n)
 * Status: Tested on https://codeforces.com/gym/105112/problem/I
 */
#pragma once

#include "../geometry/Point.h"
#include "../geometry/AngleCmp.h"

template<class P>
vector<vi> planarFaces(vector<vi>& g, vector<P>& p) {
  int n = sz(g); P o;
  auto cmp = [&](int x,int y) {
    return angleCmp(p[x] - o, p[y] - o); };
  vector<vi> vis(n);
  rep(i, 0, n) {
    o = p[i], sort(all(g[i]), cmp);
    vis[i].resize(sz(g[i]));
  }
  vector<vi> f;
  rep(i, 0, n) rep(j, 0, sz(adj[i])) {
    if (vis[i][j]) continue;
    vi s; int u = i, k = j;
    while (!vis[u][k]) {
      vis[u][k] = 1; s.push_back(u);
      int v = adj[u][k]; o = p[v];
      int kk=lower_bound(all(g[v]),u,cmp)-g[v].begin();
      u = v, k = (kk + 1) % sz(adj[u]);
    }
    f.push_back(s);
  }
  return f;
}
