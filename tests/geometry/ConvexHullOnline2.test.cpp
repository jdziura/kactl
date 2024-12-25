#define PROBLEM "https://judge.yosupo.jp/problem/convex_layers"
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

#include "content/geometry/ConvexHullOnline2.h"
using P = Point<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<P> a(n);
  rep(i, 0, n) cin >> a[i].x >> a[i].y;
  DynHull<ll> hi(a), lo(a, 1);
  rep(i, 0, n) hi.add(i), lo.add(i);
  vi ans(n, -1);
  int it = 0;
  for (;;) {
    vi hh = hi.hull(), lh = lo.hull();
    if (!sz(hh)) break;
    for (int i : hh) if (ans[i] == -1) {
      ans[i] = it;
      hi.del(i); lo.del(i);
    }
    for (int i : lh) if (ans[i] == -1) {
      ans[i] = it;
      hi.del(i); lo.del(i);
    }
    it++;
  }
  rep(i, 0, n) cout << ans[i] + 1 << '\n';
}
