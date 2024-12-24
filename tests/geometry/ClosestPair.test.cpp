#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"
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

#include "content/geometry/ClosestPair.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<P> a(n);
    rep(i, 0, n) cin >> a[i].x >> a[i].y;
    auto [s, t] = closest(a);
    int x = -1, y = -1;
    rep(i, 0, n) {
      if (x == -1 && a[i] == s) x = i;
      else if (y == -1 && a[i] == t) y = i;
    }
    cout << x << ' ' << y << '\n';
  }
}
