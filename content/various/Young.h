/**
 * Author: maspy, mango_lassi
 * Description: RSK mapping calculates unique bijection of permutation p and pair of Young Tableau (A, B).
 * Hook length formula calculates number of Young Tableaus for a given Young Diagram.
 * Time: O(n \sqrt{n} \log n)/O(n^2)
 * Status: RSK tested locally a bit. Hook length untested.
 */
#pragma once

using vvi=vector<vi>;
pair<vvi, vvi> rsk_slow(vi A, int nrow = -1) {
  if (nrow == -1) nrow = sz(A);
  vvi X(nrow), Y(nrow);
  rep(i,0,sz(A)) {
    int a = A[i];
    int col = i;
    rep(row,0,nrow) {
      int r = min(col + 1, sz(X[row]));
      int l = r - 1;
      while (0 <= l && X[row][l] > a)
        tie(l, r) = mp(3 * l - 2 * r, l);
      while (l + 1 < r) {
        int m = (l + r) / 2;
        (m < 0 || X[row][m] < a ? l : r) = m;
      }
      col = r;
      if (col == sz(X[row])) {
        X[row].eb(a), Y[row].eb(i);
        break;
      } else {
        swap(X[row][col], a);
      }
    }
  }
  while (sz(X) && X.back().empty()) 
    X.pop_back();
  while (sz(Y) && Y.back().empty())
    Y.pop_back();
  return {X, Y};
}
pair<vvi, vvi> rsk(vi A) {
  int N = sz(A);
  if (N == 0) return {};
  int M = 1;
  while (M * M < N) ++M;
  auto [X1, Y1] = rsk_slow(A, M);
  reverse(all(A));
  int m = sz(X1);
  auto [X2, Y2] = rsk_slow(A, m);
  reverse(all(A));
  for (auto& x: A) x = N - 1 - x;
  auto [X3, Y3] = rsk_slow(A, m);
  X1.resize(sz(X2[0]));
  Y1.resize(sz(X2[0]));
  rep(i,0,sz(X2)) {
    rep(j,M,sz(X2[i])) {
      X1[j].eb(X2[i][j]);
      Y1[j].eb(Y3[i][j]);
    }
  }
  return {X1, Y1};
}
vi irsk(int n, vvi p, vvi q) {
  vi pi(n);
  per(ind,0,n) {
    int i = 0, j = 0;
    for (; i < sz(q); ++i) {
      for (j = 0; j < sz(q[i]) && q[i][j] != ind; ++j) {}
      if (j < sz(q[i])) break;
    }
    int cur = p[i][j];
    p[i].pop_back();
    q[i].pop_back();
    for (--i; i >= 0; --i) {
      j = upper_bound(p[i].begin(), p[i].end(), cur) - p[i].begin();
      swap(p[i][j - 1], cur);
	}
	pi[ind] = cur;
  }
  return pi;
}
// untested, be careful
ll hook(vi A) {
  if (sz(A) == 0) return 1;
  int h = sz(a), w = A[0];
  int n = 0; for (auto a: A) n += a;
  vi B(w);
  reverse(all(A));
  ll ans = fact[n]; // n!
  ll div = 1;
  for (auto a: A) {
    rep(j,0,a) { div = div * (B[j] + a - j) % MOD, ++B[j]; }
  }
  ans = ans * modPow(div, MOD - 2) % MOD;
  return ans;
}
