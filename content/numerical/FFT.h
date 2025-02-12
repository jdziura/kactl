/**
 * Author: MIT
 * Description: Multiply polynomials for any modulus.
 * Works for $n + m \leq 2^{24}$ and $c_k \leq 5 \cdot 10^{25}$.
 * Time: O((n + m) \log (n + m))
 */
#pragma once

#include "../number-theory/ModInt.h"

template<class T>
void ntt(vector<T>& a, bool inv) {
  int n = sz(a); vector<T> b(n);
  for (int i = n / 2; i; i /= 2, swap(a, b)) {
    T w = T(T::rt).pow((T::mod - 1) / n * i), m = 1;
    for (int j=0; j<n; j += 2 * i, m *= w) rep(k,0,i) {
      T u = a[j + k], v = a[j + k + i] * m;
      b[j/2 + k] = u + v, b[j/2 + k + n/2] = u - v;
    }
  }
  if (inv) {
    reverse(1 + all(a));
    T z = T(n).inv(); rep(i, 0, n) a[i] *= z;
  }
}
template<class T>
vector<T> conv(vector<T> a, vector<T> b) {
  int s = sz(a) + sz(b) - 1, n = 1 << __lg(2 * s - 1);
  a.resize(n); ntt(a, 0); b.resize(n); ntt(b, 0);
  rep(i, 0, n) a[i] *= b[i];
  ntt(a, 1); a.resize(s);
  return a;
}
template<class T>
vector<T> mconv(const auto& x, const auto& y) {
  auto con = [&](const auto& v) {
    vector<T> w(sz(v)); rep(i, 0, sz(v)) w[i] = v[i].x;
    return w; };
  return conv(con(x), con(y));
}
template<class T>
vector<T> conv3(const vector<T>& a,const vector<T>& b){
  using m0=Mod<754974721, 11>; auto c0=mconv<m0>(a, b);
  using m1=Mod<167772161, 3>;  auto c1=mconv<m1>(a, b);
  using m2=Mod<469762049, 3>;  auto c2=mconv<m2>(a, b);
  int n = sz(c0); vector<T> d(n);
  m1 r01 = m1(m0::mod).inv();
  m2 r02 = m2(m0::mod).inv(), r12 = m2(m1::mod).inv();
  rep(i, 0, n) {
    int x = c0[i].x, y = ((c1[i] - x) * r01).x,
        z = (((c2[i] - x) * r02 - y) * r12).x;
    d[i] = (T(z) * m1::mod + y) * m0::mod + x;
  }
  return d;
}
