#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_subtree_add_subtree_sum"
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

#include "content/graph/LCT.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  LinkCut lct(n);
  rep(i, 0, n) {
    cin >> lct.t[i].v;
    lct.t[i].pull();
  }
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    lct.link(u, v);
  }
  while (q--) {
    int qt;
    cin >> qt;
    if (qt == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      lct.cut(u, v);
      lct.link(w, x);
    } else if (qt == 1) {
      int v, p, x;
      cin >> v >> p >> x;
      lct.cut(p, v);
      lct.t[v].add(x);
      lct.link(p, v);
    } else {
      int v, p;
      cin >> v >> p;
      lct.cut(p, v);
      cout << lct.t[v].s << '\n';
      lct.link(p, v);
    }
  }
}
