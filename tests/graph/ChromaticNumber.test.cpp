#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef LOCAL
auto operator<<(auto& o, auto x) -> decltype(x.first, o);
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) {
  o << "{";
  for (int i = 0; auto y : x) o << ", " + !i++ * 2 << y;
  return o << "}"; }
auto operator<<(auto& o, auto x) -> decltype(x.first, o) {
  return o << "(" << x.first << ", " << x.second << ")"; }
void __print(auto... x) { ((cerr << x << " "), ...) << endl; }
#define debug(x...) __print("[" #x "]:", x)
#else
#define debug(...) 2137
#endif

#include "content/graph/ChromaticNumber.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vi g(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u] |= 1 << v;
    g[v] |= 1 << u;
  }
  cout << chromaticNumber(g) << '\n';
}
