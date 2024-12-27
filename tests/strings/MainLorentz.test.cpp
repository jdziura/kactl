#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"
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

#include "content/strings/MainLorentz.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  auto sqrr = lorentz(s);
  vector<array<int, 3>> sqr;
  for (auto [b, e, l]: sqrr) sqr.push_back({l, b, e + 2 * l - 1});
  sort(all(sqr));
  set<pii> vis;
  vector<array<int, 3>> ans;
  for (auto [t, l, r] : sqr) {
    if (vis.insert({l, r}).second) ans.push_back({t, l, r});
  }
  cout << sz(ans) << '\n';
  for (auto [t, l, r] : ans) cout << t << ' ' << l << ' ' << r << '\n';
}
