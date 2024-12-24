#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
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

#include "content/data-structures/UnionFind.h"
#include "content/graph/BiconnectedComponents.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<pii> e(m);
  ed.resize(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    ed[u].push_back({v, i});
    ed[v].push_back({u, i});
    e[i] = {u, v};
  }
  int cnt = n;
  UF uf(n);
  bicomps([&](const vi& ei) {
    for (int i : ei) {
      auto [u, v] = e[i];
      cnt -= uf.join(u, v);
    }
  });
  vector<vi> c(n);
  rep(i, 0, n) c[uf.find(i)].push_back(i);
  cout << cnt << '\n';
  rep(i, 0, n) if (uf.find(i) == i) {
    cout << sz(c[i]);
    for (int x : c[i]) cout << ' ' << x;
    cout << '\n';
  }
}
