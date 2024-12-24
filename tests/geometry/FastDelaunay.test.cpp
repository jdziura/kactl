#define PROBLEM "https://judge.yosupo.jp/problem/euclidean_mst"
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

#include "content/geometry/FastDelaunay.h"

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
  vector<P> p(n);
  rep(i, 0, n) cin >> p[i].x >> p[i].y;
  vi ord(n);
  iota(all(ord), 0);
  sort(all(ord), [&](int x, int y) { return p[x] < p[y]; });
  DSU dsu(n);
  vector<pii> ans;
  for (int i = 0, j = 0; i < n; i = j) {
    while (j < n && p[ord[i]] == p[ord[j]]) j++;
    rep(k, i, j - 1) {
      ans.push_back({ord[k], ord[k + 1]});
      dsu.unite(ord[k], ord[k + 1]);
    }
  }
  map<P, int> id;
  rep(i, 0, n) id[p[i]] = i;
  auto p2 = p;
  sort(all(p2));
  p2.resize(unique(all(p2)) - p2.begin());
  auto tr = triangulate(p2);
  vector<pii> ed;
  if (!sz(tr)) {
    for (int i = 0, j = 0; i < n; i = j) {
      while (j < n && p[ord[i]] == p[ord[j]]) j++;
      if (j != n) ed.push_back({ord[i], ord[j]});
    }
  } else {
    rep(i, 0, sz(tr) / 3) {
      ed.push_back({id[tr[3 * i]], id[tr[3 * i + 1]]});
      ed.push_back({id[tr[3 * i]], id[tr[3 * i + 2]]});
      ed.push_back({id[tr[3 * i + 1]], id[tr[3 * i + 2]]});
    }
  }
  sort(all(ed), [&](auto u, auto v) {
    return (p[u.first] - p[u.second]).dist2() < (p[v.first] - p[v.second]).dist2();
  });
  for (auto [i, j] : ed) if (dsu.unite(i, j)) ans.push_back({i, j});
  assert(dsu.cnt == 1);
  for (auto [i, j] : ans) cout << i << ' ' << j << '\n';
}
