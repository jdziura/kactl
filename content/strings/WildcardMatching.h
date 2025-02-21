/**
 * Author: maspy, Adam Soltan
 * Description: Finds all occurrences of $T$ in $S$ over an alphabet with wildcards.
 * Requires $|T| \leq |S|$.
 * Time: O(|S| \log |S|)
 */
#pragma once

#include "../numerical/FFT.h"

mt19937 rng(2137);
vector<bool> match(string s, string t, char w = '*') {
  int n = sz(s), m = sz(t); mint d = rng();
  vector<mint> f1(n),f2(n),f3(n),g1(m),g2(m),g3(m);
  rep(i, 0, n) f1[i] = s[i] == w ? 0 : s[i] + d;
  rep(i, 0, n) f2[i]=f1[i]*f1[i], f3[i]=f2[i]*f1[i];
  rep(i, 0, m) g1[i] = t[i] == w ? 0 : t[i] + d;
  rep(i, 0, m) g2[i]=g1[i]*g1[i], g3[i]=g2[i]*g1[i];
  auto mul = [&](auto a, auto b) {
    int sz = 1 << __lg(2 * n - 1); reverse(all(b));
    a.resize(sz); ntt(a, 0); b.resize(sz); ntt(b, 0);
    rep(i, 0, sz) a[i] *= b[i];
    ntt(a, 1); a.erase(a.begin(), a.begin() + m - 1);
    return a;
  };
  auto a = mul(f1,g3), b = mul(f2,g2), c = mul(f3,g1);
  vector<bool> ans(n - m + 1);
  rep(i, 0, n - m + 1) ans[i] = a[i]-b[i]-b[i]+c[i]==0;
  return ans;
}
