/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Ogolniej, $opt(i,j-1)\le opt(i,j)\le opt(i+1,j)$. 
 *  Consider also, LineContainer (ch. Data structures), monotone queues, ternary search.
 * Time: O(N^2)
 */

using vl=vector<ll>;
ll knuth(vector<vl> c) {
  int n = sz(c);
  vector<vl> dp(n, vl(n, numeric_limits<ll>::max()));
  vector<vi> opt(n, vi(n));
  rep(i,0,n) {
	opt[i][i] = i;
	dp[i][i] = c[i][i];
  }
  per(i,0,n-1) rep(j,i+1,n) {
    rep(k,opt[i][j - 1],min(j, opt[i + 1][j]+1)) {
      if (ckmin(dp[i][j], dp[i][k] + dp[k + 1][j] + c[i][j]))
        opt[i][j] = k;
    }
  }
  return dp[0][n - 1];
}