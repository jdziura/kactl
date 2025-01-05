/**
 * Author: Krzysztof Potępa
 * Date: N/A
 * License: N/A
 * Description: 1. Interpolate set of points (i, vec[i])  and return it evaluated at x;
 * 2. Given n points (x, f(x)) compute n-1-degree polynomial f that passes through them;
 * Time: O(n) and O(n^2)
 */
#pragma once


template<class T>
T polyExtend(vector<T>& vec, T x) {
	int n = sz(vec);
	vector<T> fac(n, 1), suf(n, 1);

	rep(i, 1, n) fac[i] = fac[i-1] * i;
	for (int i=n; --i;) suf[i-1] = suf[i]*(x-i);

	T pref = 1, ret = 0;
	rep(i, 0, n) {
		T d = fac[i] * fac[n-i-1] * ((n-i)%2*2-1);
		ret += vec[i] * suf[i] * pref / d;
		pref *= x-i;
	}
	return ret;
}
template<class T>
vector<T> polyInterp(vector<pair<T, T>> P) {
	int n = sz(P);
	vector<T> ret(n), tmp(n);
	T last = 0;
	tmp[0] = 1;

	rep(k, 0, n-1) rep(i, k+1, n)
		P[i].second = (P[i].second-P[k].second) / (P[i].first-P[k].first);

	rep(k, 0, n) rep(i, 0, n) {
		ret[i] += P[k].second * tmp[i];
		swap(last, tmp[i]);
		tmp[i] -= last * P[k].first;
	}
	return ret;
}
