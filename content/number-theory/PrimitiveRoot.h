/**
 * Author: Adam Soltan
 * Description: Finds a primitive root modulo $p$.
 */
#pragma once

#include "Factor.h"
#include "ModMulLL.h"

mt19937_64 rng(2137);
ll primitiveRoot(ll p) {
  auto f = factor(p - 1); sort(all(f));
  f.resize(unique(all(f)) - f.begin()); rep:
  ll g = rng() % (p - 1) + 1;
  for (auto x : f) if (modpow(g, (p - 1) / x, p) == 1)
    goto rep;
  return g;
}
