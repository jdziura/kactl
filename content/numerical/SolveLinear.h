/**
 * Author: Per Austrin, Simon Lindholm, Adam Soltan
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $Ax = b$. If no solutions exist, returns $-1$.
 * Otherwise, returns the rank of $A$ and transforms it s.t.\ $\{ A'_1, A'_2, \dots \}$
 * is a basis of the kernel of $A$.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once

const double eps = 1e-12;

template<class T>
int solveLinear(vector<vector<T>>& A, vector<T>& b, vector<T>& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		T v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = abs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (abs(b[j]) > eps) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,0,n) if (j != i) {
			T fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}
	x.assign(m, 0);
	for (int i = rank - 1; i >= 0; i--) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
	}
	vector<vector<T>> ker(m - rank, vector<T>(m));
	rep(i, rank, m) {
		ker[i - rank][col[i]] = 1;
		rep(j, 0, rank) ker[i - rank][col[j]] -= A[j][i] / A[j][j];
	}
	return A = ker, rank;
}
