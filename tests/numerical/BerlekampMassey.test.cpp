#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
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

const ll mod = 998244353;
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}

#define mod dummy
#define modpow dummy2
#include "content/number-theory/ModPow.h"
#undef mod
#undef modpow

#include "content/numerical/BerlekampMassey.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  if (n == 0) {
    cout << 0 << '\n';
    return 0;
  }
  vector<ll> a(n);
  rep(i, 0, n) cin >> a[i];
  auto c = berlekampMassey(a);
  cout << sz(c) << '\n';
  rep(i, 0, sz(c)) cout << c[i] << " \n"[i == sz(c) - 1];
}
