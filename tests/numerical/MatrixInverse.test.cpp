#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
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

#include "content/number-theory/ModInt.h"
int abs(mint x) { return x.x; }

#include "content/numerical/MatrixInverse.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<mint>> a(n, vector<mint>(n));
  rep(i, 0, n) rep(j, 0, n) cin >> a[i][j].x;
  if (matInv(a) < n) {
    cout << -1 << '\n';
  } else {
    rep(i, 0, n) rep(j, 0, n) cout << a[i][j] << " \n"[j == n - 1];
  }
}
