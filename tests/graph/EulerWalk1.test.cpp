#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef LOCAL
auto& operator<<(auto&, pair<auto, auto>);
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) {
  o << "{";
  for (int i = 0; auto y : x) o << ", " + !i++ * 2 << y;
  return o << "}";
}
auto& operator<<(auto& o, pair<auto, auto> x) {
  return o << "(" << x.first << ", " << x.second << ")"; }
void __print(auto... x) { ((cerr << " " << x), ...) << endl; }
#define debug(x...) cerr << "[" #x "]:", __print(x)
#else
#define debug(...) 2137
#endif

#include "content/graph/EulerWalk.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> adj(n);
    int s = 0;
    rep(i, 0, m) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
      s = u;
    }
    rep(i, 0, n) if (sz(adj[i]) % 2) s = i;
    auto w = eulerWalk(adj, m, s);
    if (sz(w) != m + 1) cout << "No\n";
    else {
      cout << "Yes\n";
      rep(i, 0, m + 1) cout << w[i].first << " \n"[i == m];
      rep(i, 1, m + 1) cout << w[i].second << " \n"[i == m];
    }
  }
}
