/**
 * Author: maspy
 * Source: yosupo
 * Description: $c_k=\min_{i+j=k}(a_i+b_j)$, $b$ is convex
 * Time: O(n \log n)
 * Status: https://github.com/yosupo06/library-checker-problems/blob/master/convolution/min_plus_convolution_convex_arbitrary/sol/correct.cpp
 */
#pragma once

// select(i,j,k) : (i,j) -> (i,k)
template <typename F>
vi monotone_minima(int H, int W, F select) {
  vi min_col(H);
  auto dfs = [&](auto& dfs, int x1, int x2, int y1, int y2) -> void {
    if (x1 == x2) return;
    int x = (x1 + x2) / 2;
    int best_y = y1;
    for (int y = y1 + 1; y < y2; ++y) {
      if (select(x, best_y, y)) best_y = y;
    }
    min_col[x] = best_y;
    dfs(dfs, x1, x, y1, best_y + 1);
    dfs(dfs, x + 1, x2, best_y, y2);
  };
  dfs(dfs, 0, H, 0, W);
  return min_col;
}
vi min_plus_convolution(vi A, vi B) {
  int N = A.size(), M = B.size();
  // B is convex
  for (int i = 0; i < M - 2; ++i) assert(B[i] + B[i + 2] >= 2 * B[i + 1]);
  auto select = [&](int i, int j, int k) -> bool {
    if (i < k) return false;
    if (i - j >= M) return true;
    return A[j] + B[i - j] >= A[k] + B[i - k];
  };
  vi J = monotone_minima(N + M - 1, N, select);
  vi C(N + M - 1);
  for (int i = 0; i < N + M - 1; ++i) {
    int j = J[i];
    C[i] = A[j] + B[i - j];
  }
  return C;
}
