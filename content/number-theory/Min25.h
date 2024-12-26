/**
 * Author: Nyaan, Adam Soltan
 * Source: https://judge.yosupo.jp/submission/235698
 * Description: Fast multiplicative function prefix sums.
 * Requires \texttt{isPrime} calculated up to $\sqrt{n}$.
 * Time: O(\tfrac{n^{3/4}}{\log n})
 */
#pragma once

#include "FastEratosthenes.h"

template<class T>
struct Min25 {
  ll n, sq, s, hls; vi p;
  Min25(ll N) : n(N) {
    sq = sqrt(n) + 5;
    while (sq * sq > n) sq--;
    hls = quo(n, sq);
    if (hls != 1 && quo(n, hls - 1) == sq) hls--;
    s = hls + sq;
    rep(i, 2, sq + 1) if (isPrime[i]) p.push_back(i);
  }
  vector<T> sieve(auto f) {
    vector<T> h(s);
    rep(i, 1, hls) h[i] = f(quo(n, i)) - 1;
    rep(i, 1, sq + 1) h[s - i] = f(i) - 1;
    for (ll x : p) {
      T xt = f(x) - f(x - 1), pi = h[s - x + 1];
      ll x2=x*x, imax=min(hls, quo(n, x2) + 1), ix=x;
      for (int i = 1; i < imax; i++, ix += x)
        h[i] -= ((ix<hls?h[ix]:h[s-quo(n,ix)])-pi)*xt;
      for (int i = sq; i >= x2; i--)
        h[s - i] -= (h[s - quo(i, x)] - pi) * xt;
    }
    return h;
  }
  vector<T> unsieve(vector<T>& fp, auto f) {
    vector<ll> ns(s);
    rep(i, 1, hls) ns[i] = quo(n, i);
    rep(i, 1, sq + 1) ns[s - i] = i;
    auto F = fp, G = fp;
    for (ll P : p | views::reverse) {
      for (ll pk=P, k=1; quo(n,P)>=pk; k++, pk*=P) {
        T x=fp[idx(P)], y=f(P,k,pk), z=f(P,k+1,pk*P);
        rep(i, 1, s) {
          ll m = ns[i];
          if (P * pk > m) break;
          G[i] += y * (F[idx(quo(m, pk))] - x) + z;
        }
      }
      copy_n(G.begin(),min(s,idx(P*P)+1),F.begin());
    }
    rep(i, 1, sz(ns)) F[i] += 1;
    return F;
  }
  ll quo(ll x, ll y) { return (double)x / y; }
  ll idx(ll x) { return x <= sq ? s - x : quo(n, x); }
};
