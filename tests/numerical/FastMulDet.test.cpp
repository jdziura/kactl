#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"
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

#include "content/numerical/FastMulDet.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, k;
  cin >> n >> k;
  vi a(k), b(k); vector<ll> c(k);
  rep(i, 0, k) cin >> a[i] >> b[i] >> c[i];
  auto mul = [&](const vector<ll>& u) {
    vector<ll> v(n);
    rep(i, 0, k) (v[a[i]] += c[i] * u[b[i]]) %= mod;
    return v;
  };
  cout << det(n, mul) << '\n';
}
