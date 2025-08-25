/**
 * Author: Adam Soltan
 * Description: Wavelet tree. Can be sped up with bitset. Easily extendable to support sum.
 * Time: O((n + q) \log n)
*/
#pragma once

struct Node {
  int lo, hi;
  vector<int> s;
  Node *l = 0, *r = 0;
  Node(auto st, auto ed, auto sst) {
    int n = ed - st;
    lo = sst[0];
    hi = sst[n - 1] + 1;
    if (lo + 1 < hi) {
      int mid = sst[n / 2];
      if (mid==sst[0])mid=*upper_bound(sst,sst+n,mid);
      s.reserve(n + 1);
      s.push_back(0);
      for (auto it = st; it != ed; it++) {
        s.push_back(s.back() + (*it < mid));
      }
      auto k = stable_partition(st, ed, [&](int x) {
        return x < mid;
      });
      auto sm = lower_bound(sst, sst + n, mid);
      if (k != st) l = new Node(st, k, sst);
      if (k != ed) r = new Node(k, ed, sm);
    }
  }
  int kth(int a, int b, int k) {
    if (lo + 1 == hi) return lo;
    int x = s[a], y = s[b];
    return k < y - x ? l->kth(x, y, k)
                     : r->kth(a-x,b-y,k-(y-x));
  }
  int count(int a, int b, int k) {
    if (lo >= k) return 0;
    if (hi <= k) return b - a;
    int x = s[a], y = s[b];
    return (l ? l->count(x, y, k) : 0) +
           (r ? r->count(a - x, b - y, k) : 0);
  }
  int freq(int a, int b, int k) {
    if (k < lo || hi <= k) return 0;
    if (lo + 1 == hi) return b - a;
    int x = s[a], y = s[b];
    return (l ? l->freq(x, y, k) : 0) +
           (r ? r->freq(a - x, b - y, k) : 0);
  }
};