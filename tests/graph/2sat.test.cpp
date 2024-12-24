#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
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
  o << '{';
  for (int i = 0; auto y : x) o << ", " + !i++ * 2 << y;
  return o << '}';
}
auto& operator<<(auto& o, pair<auto, auto> x) {
  return o << '(' << x.first << ", " << x.second << ')';
}
void __print(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "[" #x "]:", __print(x)
#else
#define debug(...) 2137
#endif

#include "content/graph/2sat.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  int n, m;
  cin >> s >> s >> n >> m;
  TwoSat sat(n);
  while (m--) {
    int u, v, z;
    cin >> u >> v >> z;
    u = u >= 0 ? u - 1 : ~(-u - 1);
    v = v >= 0 ? v - 1 : ~(-v - 1);
    sat.either(u, v);
  }
  cout << "s ";
  if (!sat.solve()) {
    cout << "UNSATISFIABLE\n";
    return 0;
  }
  cout << "SATISFIABLE\nv";
  rep(i, 0, n) cout << ' ' << (sat.values[i] ? 1 : -1) * (i + 1);
  cout << " 0\n";
}
