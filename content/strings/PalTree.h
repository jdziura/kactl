/**
 * Author: UW1, Adam Soltan
 * Description: Palindrome tree. Can be used for counting number of occurrences,
 * just add $1$ to suffix link path. Replace array with map if ML is tight.
 * Time: O(26 N), \texttt{split} is O(n \log n)
 * Status: split tested on https://acm.timus.ru/problem.aspx?space=1&num=2058
 */
#pragma once

const int A = 26;
struct PalTree {
  int last = 0;
  vi len = {0, -1}, link = {1, 0}, s = {-1};
  vector<array<int, A>> to = {{}, {}};
  int find(int u) {
    while (s.back() != s[sz(s)-len[u]-2]) u = link[u];
    return u;
  }
  int add(int x) { // x in [0, A)
    s.push_back(x); last = find(last);
    if (!to[last][x]) {
      to.push_back({});
      len.push_back(len[last] + 2);
      link.push_back(to[find(link[last])][x]);
      to[last][x] = sz(to) - 1;
    }
    return last = to[last][x];
  }
};
// min even/odd palindromic split of prefix of size i
const int INF = 1e9;
struct F { int e, o; };
F op(F x, F y) { return {min(x.e,y.e), min(x.o,y.o)}; }
vector<F> split(vi v) {
  PalTree t;
  vector<F> s(2), ans(sz(v) + 1, {INF, INF});
  vi go(2), d(2); ans[0] = s[0] = s[1] = {0, INF};
  rep(i, 0, sz(v)) {
    int x = t.add(v[i]), y = t.link[x];
    if (x >= sz(go)) {
      d.push_back(t.len[x] - t.len[y]);
      go.push_back(d[x] == d[y] ? go[y] : y);
      s.push_back(ans[0]);
    }
    for (int u = x; t.len[u] > 0; u = go[u]) {
      s[u] = ans[i + 1 - t.len[go[u]] - d[u]];
      if (d[u] == d[t.link[u]])
        s[u] = op(s[u], s[t.link[u]]);
      ans[i+1] = op(ans[i+1], {s[u].o+1, s[u].e+1});
    }
  }
  return ans;
}
