/**
 * Author: chilli, Andrew He, Adamant, Adam Soltan
 * Description: Fast operations on polynomials.
 * Time: O(n \log n), \texttt{eval} and \texttt{interp} are O(n \log^2 n)
 */
#pragma once

#include "FFT.h"

using Poly = vector<mint>;
Poly& operator+=(Poly& a, const Poly& b) {
  a.resize(max(sz(a), sz(b)));
  rep(i, 0, sz(b)) a[i] += b[i];
  return a;
}
Poly& operator-=(Poly& a, const Poly& b) {
  a.resize(max(sz(a), sz(b)));
  rep(i, 0, sz(b)) a[i] -= b[i];
  return a;
}
Poly& operator*=(Poly& a, const Poly& b) {
  if (min(sz(a), sz(b)) < 50) {
    Poly c(sz(a) + sz(b) - 1);
    rep(i,0,sz(a)) rep(j,0,sz(b)) c[i+j] += a[i]*b[j];
    return a = c;
  }
  return a = conv(move(a), b);
}
Poly operator+(Poly a, const Poly& b){ return a += b; }
Poly operator-(Poly a, const Poly& b){ return a -= b; }
Poly operator*(Poly a, const Poly& b){ return a *= b; }
Poly modK(Poly a, int k) {
  return a.resize(min(sz(a), k)), a;
}
Poly inv(const Poly& a) { // a[0] != 0
  Poly b = {1 / a[0]};
  while (sz(b) < sz(a))
    b = modK(b*(Poly{2} - modK(a,2*sz(b))*b), 2*sz(b));
  return modK(b, sz(a));
}
Poly deriv(Poly a) {
  if (!sz(a)) return {};
  rep(i, 1, sz(a)) a[i - 1] = a[i] * i;
  return a.pop_back(), a;
}
Poly integr(const Poly& a) {
  if (!sz(a)) return {};
  Poly b(sz(a) + 1);
  rep(i, 1, sz(b)) b[i] = a[i - 1] / i;
  return b;
}
Poly shift(Poly p, mint c) { // p(x + c)
  int n = sz(p);
  Poly q(n, 1); mint fac = 1;
  rep(i, 1, n) {
    p[i] *= (fac *= i);
    q[n - 1 - i] = q[n - i] * c / i;
  }
  p *= q;
  p.erase(p.begin(), p.begin() + n - 1);
  fac = 1;
  rep(i, 1, n) p[i] /= (fac *= i);
  return p;
}
Poly log(const Poly& a) { // a[0] = 1
  Poly b = integr(deriv(a) * inv(a));
  return b.resize(sz(a)), b;
}
Poly exp(const Poly& a) { // a[0] = 0
  Poly b = {1};
  if (!sz(a)) return b;
  while (sz(b) < sz(a)) {
    b.resize(sz(b) * 2);
    b *= Poly{1} + modK(a, sz(b)) - log(b);
    b.resize(sz(b) / 2 + 1);
  }
  return modK(b, sz(a));
}
Poly pow(Poly a, ll m) {
  int p = 0, n = sz(a);
  if (!m) { a.assign(n, 0); a[0] = 1; return a; }
  while (p < n && !a[p].x) p++;
  if (p >= (n + m - 1) / m) return Poly(n);
  mint j = a[p];
  a = Poly(p + all(a)) * Poly{1 / j};
  a.resize(n);
  Poly res = exp(log(a) * Poly{m}) * Poly{j.pow(m)};
  res.insert(res.begin(), p * m, 0);
  return modK(res, n);
}
Poly& operator/=(Poly& a, Poly b) {
  if (sz(a) < sz(b)) return a = {};
  int s = sz(a) - sz(b) + 1;
  reverse(all(a)), reverse(all(b));
  a.resize(s), b.resize(s);
  a *= inv(b);
  a.resize(s), reverse(all(a));
  return a;
}
Poly operator/(Poly a, Poly b) { return a /= b; }
Poly& operator%=(Poly& a, const Poly& b) {
  if (sz(a) < sz(b)) return a;
  return a = modK(a - (a / b) * b, sz(b) - 1);
}
Poly operator%(Poly a,const Poly& b) { return a %= b; }
vector<mint> eval(const Poly& a,const vector<mint>& x){
  int n = sz(x);
  if (!n) return {};
  vector<Poly> up(2 * n);
  rep(i, 0, n) up[i + n] = Poly{0 - x[i], 1};
  for (int i = n - 1; i > 0; i--)
    up[i] = up[2 * i] * up[2 * i + 1];
  vector<Poly> down(2 * n);
  down[1] = a % up[1];
  rep(i, 2, 2 * n) down[i] = down[i / 2] % up[i];
  vector<mint> y(n);
  rep(i, 0, n) y[i] = down[i + n][0];
  return y;
}
Poly interp(vector<mint> x, vector<mint> y) {
  int n = sz(x);
  vector<Poly> up(2 * n);
  rep(i, 0, n) up[i + n] = Poly{0 - x[i], 1};
  for (int i = n - 1; i > 0; i--)
    up[i] = up[2 * i] * up[2 * i + 1];
  vector<mint> a = eval(deriv(up[1]), x);
  vector<Poly> down(2 * n);
  rep(i, 0, n) down[i + n] = Poly{y[i] / a[i]};
  for(int i = n - 1; i > 0; i--)
    down[i] = down[2*i]*up[2*i+1]+down[2*i+1]*up[2*i];
  return down[1];
}
// B(x) = product of (1 + x^k)^{a_k} for k=1..inf
Poly subsetSum(Poly a) { // a[0] = 0
  int n = sz(a);
  Poly b(n);
  rep(i, 1, n) b[i] = mint(i).inv() * (i % 2 ? 1 : -1);
  for (int i = n - 2; i > 0; i--)
    for (int j = 2; i * j < n; j++)
      a[i * j] += b[j] * a[i];
  return exp(a);
}
// B(x) = product of 1 / (1 - a_k*x^k) for k=1..inf
Poly eulerTransform(Poly a) { // a[0] = 0
  int n = sz(a);
  Poly b(n);
  rep(i, 1, n) b[i] = mint(i).inv();
  for (int i = n - 1; i > 0; i--) {
    mint m = a[i];
    for (int j = 2; i * j < n; j++)
      m *= a[i], a[i * j] += b[j] * m;
  }
  return exp(a);
}