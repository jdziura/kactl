#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"
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

#include "content/geometry/ManhattanMST.h"

struct DSU {
  int n, cnt;
  vector<int> p;
  DSU(int _n) {
    n = _n;
    cnt = n;
    p.resize(n, -1);
  }
  int get(int x) {
    return p[x] < 0 ? x : p[x] = get(p[x]);
  }
  int size(int x) {
    return -p[get(x)];
  }
  bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    if (-p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    cnt--;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<P> a(n);
  rep(i, 0, n) cin >> a[i].x >> a[i].y;
  auto ed = manhattanMST(a);
  sort(all(ed));
  ll s = 0;
  vector<pii> ans;
  DSU dsu(n);
  for (auto [w, u, v] : ed) {
    if (dsu.unite(u, v)) {
      s += w;
      ans.push_back({u, v});
    }
  }
  cout << s << '\n';
  for (auto [u, v] : ans) cout << u << ' ' << v << '\n';
}
