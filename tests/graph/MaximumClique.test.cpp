#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
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

#include "content/graph/MaximumClique.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vb g(n);
  rep(i, 0, n) rep(j, 0, n) if (i != j) g[i][j] = 1;
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u][v] = g[v][u] = 0;
  }
  Maxclique mc(g);
  vi s = mc.maxClique();
  cout << sz(s) << '\n';
  rep(i, 0, sz(s)) cout << s[i] << " \n"[i == sz(s) - 1];
}
