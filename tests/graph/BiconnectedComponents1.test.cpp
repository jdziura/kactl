#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
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
  vector<bool> b(m, 1);
  vi vis(n, -1);
  vector<vi> c;
  bicomps([&](const vi& ei) {
    vi cc;
    for (int i : ei) {
      b[i] = 0;
      auto [u, v] = e[i];
      if (vis[u] != sz(c)) cc.push_back(u);
      if (vis[v] != sz(c)) cc.push_back(v);
      vis[u] = vis[v] = sz(c);
    }
    c.push_back(cc);
  });
  rep(i, 0, m) if (b[i]) {
    auto [u, v] = e[i];
    c.push_back({u, v});
  }
  rep(i, 0, n) if (!sz(ed[i])) c.push_back({i});
  cout << sz(c) << '\n';
  rep(i, 0, sz(c)) {
    cout << sz(c[i]);
    for (int x : c[i]) cout << ' ' << x;
    cout << '\n';
  }
}
