/**
 * Author: Kacper Topolski, Ivan Gechu
 * Description: Given two matroids, finds a largest common independent set of maximal
 * weight. To minimize weight, multiply costs by $-1$.
 * Returns vector $V$ such that \texttt{V[i]=1} iff $i$-th element is included in found set.
 * Time: $O(r^2 (init + n \cdot add) + r n^3)$,
 * where $r$ is the size of the largest common independent set.
 * Here $r n^3$ comes from running Bellman-Ford $r$ times, which is practically faster.
 * Status: Tested on NAIPC 2018G (Rainbow Graph) and https://codeforces.com/gym/103373/problem/I
 */
#pragma once

const ll INF = 1e18;
template<class T, class U>
vector<bool> maxMatroidIsect(T& A, U& B, vector<ll>& c, int n){
  vector<bool> ans(n);
  bool ok = 1;
  while(ok) {
    vector<vector<pair<int, ll>>> G(n);
    vector<bool> good(n);
    vector<pair<ll, ll>> d(n, {INF, INF});
    vi prev(n, -1);
    A.init(ans); B.init(ans); ok = 0;
    rep(i, 0, n) if(!ans[i]) {
      if(A.canAdd(i)) d[i] = {-c[i], 0}, prev[i] = -2;
      good[i] = B.canAdd(i);
    }
    rep(i, 0, n) if(ans[i]) {
      ans[i] = 0;
      A.init(ans); B.init(ans);
      rep(j, 0, n) if(i != j && !ans[j]) {
        if(A.canAdd(j)) G[i].push_back({j, -c[j]});
        if(B.canAdd(j)) G[j].push_back({i, c[i]});
      }
      ans[i] = 1;
    }
    bool ford = 1;
    while(ford) {
      ford = 0;
      rep(i, 0, n) if(prev[i] != -1)
        for(auto [to, cst] : G[i]) {
          pair<ll, ll> nd = {d[i].first + cst, d[i].second+1};
          if(nd < d[to]) d[to] = nd, prev[to] = i, ford = 1;
        }
    }
    int e = -1;
    pair<ll, ll> dst = {INF, INF};
    rep(i, 0, n)
      if(good[i] && d[i] < dst) dst = d[i], e = i;
    if(e == -1) break;
    ans[e] = 1, ok = 1;
    while(prev[e] >= 0) ans[e=prev[e]] = 0, ans[e=prev[e]] = 1;
  }
  return ans;
}
// Matroid where each element has color
// and set is independent iff for each color c
// #{elements of color c} <= maxAllowed[c].
struct LimOracle {
  vi color; // color[i] = color of i-th element
  vi maxAllowed; // Limits for colors
  vi tmp;
  // Init oracle for independent set S; O(n)
  void init(vector<bool>& S) {
    tmp = maxAllowed;
    rep(i, 0, sz(S)) tmp[color[i]] -= S[i];
  }
  // Check if S+{k} is independent; time: O(1)
  bool canAdd(int k) { return tmp[color[k]] > 0;}
};
// Graphic matroid - each element is edge,
// set is independent iff subgraph is acyclic.
struct GraphOracle {
  vector<pii> elems; // Ground set: graph edges
  int n; // Number of vertices, indexed [0;n-1]
  vi par;
  int find(int i) {
    return par[i] == -1 ? i : par[i] = find(par[i]);
  }
  // Init oracle for independent set S; ~O(n)
  void init(vector<bool>& S) {
    par.assign(n, -1);
    rep(i, 0, sz(S)) if (S[i])
      par[find(elems[i].first)] = find(elems[i].second);
  }
  // Check if S+{k} is independent; time: ~O(1)
  bool canAdd(int k) {
    return find(elems[k].first) != find(elems[k].second);
  }
};
// Co-graphic matroid - each element is edge,
// set is independent iff after removing edges
// from graph number of connected components
// doesn't change.
// Works for multiedges and loops.
struct CographOracle {
  vector<pii> elems; // Ground set: graph edges
  int n; // Number of vertices, indexed [0;n-1]
  vector<vi> G;
  vi pre, low;
  int cnt;
  int dfs(int v, int p) {
    pre[v] = low[v] = ++cnt;
    bool skip = 0;
    for(auto e : G[v]) {
      if (e == p && !skip) {
        skip = 1;
        continue;
      }
      low[v] = min(low[v], pre[e] ?: dfs(e,v));
    }
    return low[v];
  }
  // Init oracle for independent set S; O(n)
  void init(vector<bool>& S) {
    G.assign(n, {});
    pre.assign(n, 0);
    low.resize(n);
    cnt = 0;
    rep(i, 0, sz(S)) if (!S[i]) {
      pii e = elems[i];
      if(e.first == e.second) continue;
      G[e.first].push_back(e.second);
      G[e.second].push_back(e.first);
    }
    rep(v, 0, n) if (!pre[v]) dfs(v, -1);
  }
  // Check if S+{k} is independent; time: O(1)
  bool canAdd(int k) {
    auto [u, v] = elems[k];
    if (u == v) return 1;
    return max(pre[u], pre[v]) != max(low[u], low[v]);
  }
};
// Matroid equivalent to linear space with XOR
struct XorOracle {
  vector<ll> elems; // Ground set: numbers
  vector<ll> base;
  // Init for independent set S; O(n+r^2)
  void init(vector<bool>& S) {
    base.assign(63, 0);
    rep(i, 0, sz(S)) if (S[i]) {
      ll e = elems[i];
      rep(j, 0, sz(base)) if ((e >> j) & 1) {
        if (!base[j]) {
          base[j] = e;
          break;
        }
        e ^= base[j];
      }
    }
  }
  // Check if S+{k} is independent; time: O(r)
  bool canAdd(int k) {
    ll e = elems[k];
    rep(i, 0, sz(base)) if ((e >> i) & 1) {
      if (!base[i]) return 1;
      e ^= base[i];
    }
    return 0;
  }
};
