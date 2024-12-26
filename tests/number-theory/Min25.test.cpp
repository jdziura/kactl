#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_multiplicative_function"
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

const int LIM = 4e5;
#include "content/number-theory/ModInt.h"
#include "content/number-theory/FastEratosthenes.h"
#include "content/number-theory/Min25.h"

using mi = Mod<469762049, -1>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  eratosthenes();
  int t;
  cin >> t;
  while (t--) {
    ll n;
    mi a, b;
    cin >> n >> a.x >> b.x;
    Min25<mi> m(n);
    mi i2 = mi(2).inv();
    auto s = m.sieve([&](ll x) { return i2 * x * (x + 1); });
    auto c = m.sieve([&](ll x) { return x; });
    rep(i, 0, sz(s)) s[i] = a * c[i] + b * s[i];
    auto f = m.unsieve(s, [&](ll p, ll k, ll) { return a * k + b * p; });
    cout << f[1].x << '\n';
  }
}
