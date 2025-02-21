/**
 * Author: Adam Soltan
 * Description: Divides the interval $[1, \infty)$ into constant division
 * intervals. For a significant speedup, get rid of \texttt{v} and do the
 * calculations directly in the loop.
 * Time: O(\sqrt{n})
 */
#pragma once

vector<ll> sameFloor(ll n) {
  vector<ll> v;
  for (ll i = 1; i <= n; i = n/(n/i)+1) v.push_back(i);
  return v.push_back(n + 1), v;
}
vector<ll> sameCeil(ll n) {
  vector<ll> v;
  for (ll i = 1, j; i < n; i = (n + j - 2) / (j - 1)) {
    j = (n + i - 1) / i;
    v.push_back(i);
  }
  return v.push_back(n), v;
}
