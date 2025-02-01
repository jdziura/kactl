/**
 * Author: Adam Soltan
 * Description: Arithmetic for fast hashing modulo $2^{61} - 1$ (prime).
 * Time: About $30\%$ faster than naive modulo.
 */
#pragma once

const ll MOD = (1ll << 61) - 1;
ll add(ll a, ll b) {
  return a+b >= MOD ? a+b - MOD : a+b; }
ll sub(ll a, ll b) { return add(a, MOD - b); }
ll mul(ll a, ll b) {
  auto c = (__int128)a * b;
  return add(c & MOD, c >> 61);
}
