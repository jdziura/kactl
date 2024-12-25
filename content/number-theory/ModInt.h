/**
 * Author: Adam Soltan
 * Description: Operators for modular arithmetic.
 */
#pragma once

template<int M, int R>
struct Mod {
  static const int mod = M, rt = R;
  int x;
  Mod(ll y = 0) : x(y % M) { x += (x < 0) * M; }
  Mod& operator+=(Mod o) {
    if ((x += o.x) >= M) x -= M;
    return *this; }
  Mod& operator-=(Mod o) {
    if ((x -= o.x) < 0) x += M;
    return *this; }
  Mod& operator*=(Mod o) {
    x = 1ll * x * o.x % M;
    return *this; }
  Mod& operator/=(Mod o) { return *this *= o.inv(); }
  friend Mod operator+(Mod a, Mod b) { return a += b; }
  friend Mod operator-(Mod a, Mod b) { return a -= b; }
  friend Mod operator*(Mod a, Mod b) { return a *= b; }
  friend Mod operator/(Mod a, Mod b) { return a /= b; }
  auto operator<=>(const Mod&) const = default;
  Mod pow(ll n) const {
    Mod a = x, b = 1;
    for (; n; n /= 2, a *= a) if (n % 2) b *= a;
    return b; }
  Mod inv() const { assert(x); return pow(M - 2); }
  friend ostream& operator<<(ostream& os, Mod x) {
    return os << x.x; }
};
using mint = Mod<998244353, 3>;
