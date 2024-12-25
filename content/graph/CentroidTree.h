/**
 * Author: MIT, Kacper Topolski, Adam Soltan
 * Description: Centroid decomposition tree.
 * Example usage can be extended for weighted trees with a BST.
 * Time: O(n \log n + q \log^2 n)
 */
#pragma once

#include "../data-structures/FenwickTree.h"

struct CT {
  vi sub, cp, d; // centroid subtree, parent, depth
  vector<vi> g, dst; // dst[depth][descendant]
  CT(vector<vi>& G) : sub(sz(G)), cp(sz(G), -2),
    d(sz(G)), g(G), dst(__lg(sz(G)) + 1, vi(sz(G))) {
    rec(0, 0);
  }
  void dfs(int u, int p) {
    sub[u] = 1;
    for (int v : g[u]) if (v != p && cp[v] == -2)
      dfs(v, u), sub[u] += sub[v];
  }
  void gen(int u, int p, int lev) {
    dst[lev][u] = dst[lev][p] + 1;
    for (int v : g[u]) if (v != p && cp[v] == -2)
      gen(v, u, lev);
  }
  int rec(int u, int dd) {
    dfs(u, -1);
    int p = -1, s = sub[u]; rep:
    for (int v : g[u])
      if (v != p && cp[v] == -2 && sub[v] > s / 2) {
        p = u, u = v; goto rep; }
    sub[u] = s, d[u] = dd, cp[u] = -1;
    for (int v : g[u]) if (cp[v] == -2)
      gen(v, u, d[u]), cp[rec(v, dd + 1)] = u;
    return u;
  }
  void path(int u, auto f) { // f(centroid, son, dist)
    for (int x = u, y = -1; x != -1; y = x, x = cp[x])
      f(x, y, dst[d[x]][u]);
  }
};
struct ContourAdd : CT {
  vector<FT> d, c;
  ContourAdd(vector<vi>&G) : CT(G),d(sz(g),FT(0)),c(d){
    rep(i, 0, sz(g)) d[i] = c[i] = FT(sub[i] + 1);
  }
  // Add x to verts whose distance from p is in [l, r)
  void add(int p, int l, int r, int x) {
    path(p, [&](int u, int v, int dd) {
      d[u].update(max(0, l - dd), x);
      if (r - dd < sub[u])
        d[u].update(max(0, r - dd), -x);
      if (v != -1) {
        c[v].update(max(0, l - dd), x);
        if (r - dd < sub[u])
          c[v].update(max(0, r - dd), -x);
      }
    });
  }
  ll get(int p) {
    ll ans = 0;
    path(p, [&](int u, int v, int dd) {
      ans += d[u].query(dd + 1);
      if (v != -1) ans -= c[v].query(dd + 1);
    });
    return ans;
  }
};
