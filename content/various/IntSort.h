/**
 * Author: platelet
 * Description: Extremely fast sort.
 */
#pragma once

constexpr int N = 10'000'000;
unsigned a[N], b[N];
void sort(unsigned* a, int n) {
  unsigned buc[4][256] = {};
  rep(i, 0, n) {
    buc[0][a[i] & 255]++;
    buc[1][a[i] >> 8 & 255]++;
    buc[2][a[i] >> 16 & 255]++;
    buc[3][a[i] >> 24]++;
  }
  rep(k, 0, 4) {
    unsigned offset = 0;
    rep(i, 0, 256)
      swap(buc[k][i], offset), offset += buc[k][i];
  }
  rep(i, 0, n) b[buc[0][a[i] & 255]++] = a[i];
  rep(i, 0, n) a[buc[1][b[i] >> 8 & 255]++] = b[i];
  rep(i, 0, n) b[buc[2][a[i] >> 16 & 255]++] = a[i];
  rep(i, 0, n) a[buc[3][b[i] >> 24 & 255]++] = b[i];
}