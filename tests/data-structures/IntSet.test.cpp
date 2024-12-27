#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
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

#include "content/data-structures/IntSet.h"

const int N = 10'000'100;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  string b;
  cin >> n >> q >> b;
  IntSet<N> s;
  rep(i, 0, n) if (b[i] == '1') s.add(i);
  while (q--) {
    int t, k;
    cin >> t >> k;
    if (t == 0) s.add(k);
    else if (t == 1) s.del(k);
    else if (t == 2) cout << s.has(k) << '\n';
    else if (t == 3) cout << (k ? s.next(k - 1) : (s.has(0) ? 0 : s.next(0))) << '\n';
    else cout << s.prev(k + 1) << '\n';
  }
}
