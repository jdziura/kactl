#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
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

#include "content/numerical/FFTPoly.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  ll m;
  cin >> n >> m;
  Poly f(n), g(m);
  rep(i, 0, n) cin >> f[i].x;
  rep(i, 0, m) cin >> g[i].x;
  Poly q = f / g, r = f % g;
  while (sz(r) && !r.back().x) r.pop_back();
  cout << sz(q) << ' ' << sz(r) << '\n';
  rep(i, 0, sz(q)) cout << q[i].x << " \n"[i == sz(q) - 1];
  rep(i, 0, sz(r)) cout << r[i].x << " \n"[i == sz(r) - 1];
}
