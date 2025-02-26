/**
 * Author: Adam Soltan
 * Description: Finds all subset sums of a multiset with sum $s$.
 * \texttt{cnt[k]} should be the number of elements with value $k$.
 * Usage: subsetSum<MAXN>(s, cnt);
 * Time: O(\tfrac{s \sqrt{s}}{32})
 */
#pragma once

template<int N>
vi subsetSum(int s, vi& cnt) {
  if (s < 3*N/4) return subsetSum<3*N/4>(s, cnt);
  bitset<N> b; b[0] = 1;
  rep(i, 1, sz(cnt)) {
    for (int j = 1; j <= cnt[i]; j *= 2)
      b |= b << (j * i), cnt[i] -= j;
    if (cnt[i]) b |= b << (cnt[i] * i);
  }
  vi ans;
  rep(i, 0, s + 1) if (b[i]) ans.push_back(i);
  return ans;
}
