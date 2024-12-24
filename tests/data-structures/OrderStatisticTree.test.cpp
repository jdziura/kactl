#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
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

#include "content/data-structures/OrderStatisticTree.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  Tree<int> s;
  rep(i, 0, n) {
    int a;
    cin >> a;
    s.insert(a);
  }
  while (q--) {
    int t, x;
    cin >> t >> x;
    auto print = [&](auto it) { cout << (it != s.end() ? *it : -1) << '\n'; };
    if (t == 0) s.insert(x);
    else if (t == 1) s.erase(x);
    else if (t == 2) print(s.find_by_order(x - 1));
    else if (t == 3) cout << s.order_of_key(x + 1) << '\n';
    else if (t == 4) {
      auto it = s.lower_bound(x + 1);
      if (it == s.begin()) cout << -1 << '\n';
      else cout << *(--it) << '\n';
    } else if (t == 5) print(s.lower_bound(x));
  }
}
