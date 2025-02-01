/**
 * Author: pajenegod, Adam Soltan
 * Description: Calculates a DP from every root in a tree.
 * Use \texttt{dp}, \texttt{rdp} and \texttt{p} for edge dp.
 * Time: O(\sum d \log d)
 */
#pragma once

struct S {
  void init(int u) {}
  void join(int u, int i, const S& c) {}
  void push(int u, int i) {} // i = -1 if root
};
vector<S> reroot(vector<vi>& g) {
  int n = sz(g), t = 1;
  vi q(n), p(n);
  for (int u : q) for (int v : g[u]) if (p[u] != v) {
    p[v] = u, q[t++] = v;
  }
  vector<S> dp(n), rdp(n), ans(n);
  for (int i = n - 1; i >= 0; i--) {
    int u = q[i], k = -1;
    dp[u].init(u);
    rep(j, 0, sz(g[u])) {
      if (g[u][j] != p[u]) dp[u].join(u,j,dp[g[u][j]]);
      else k = j;
    }
    ans[u] = dp[u], dp[u].push(u, k);
  }
  if (n == 1) return dp;
  for (int u : q) {
    int d = sz(g[u]); vector<S> e(d);
    rep(i, 0, d) e[i].init(u);
    for (int b = __lg(d); b >= 0; b--) {
      for (int i = d - 1; i >= 0; i--) e[i] = e[i / 2];
      rep(i, 0, d - (d & !b)) {
        S& s = g[u][i] != p[u] ? dp[g[u][i]] : rdp[u];
        e[(i >> b) ^ 1].join(u, i, s);
      }
    }
    rep(i, 0, sz(g[u])) {
      if (p[u]!=g[u][i]) (rdp[g[u][i]]=e[i]).push(u,i);
      else ans[u].join(u, i, rdp[u]);
    }
    ans[u].push(u, -1);
  }
  return ans;
}
