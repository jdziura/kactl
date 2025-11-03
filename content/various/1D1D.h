/**
 * Author: Warsaw Eagles
 * Description: $n>0$ dlugosc paska,
 *   \texttt{cost(i, j)} koszt odcinka $[i, j]$
 *   Dla $a \leq b \leq c \leq d$ \texttt{cost} ma spelniac $cost(a, c) + cost(b, d) \leq cost(a, d) + cost(b, c)$.
 *   Dzieli pasek $[0, n)$ na odcinki $[0, cuts[0]], ..., (cuts[i-1], cuts[i]]$,
 *   gdzie \texttt{cuts.back() == n - 1}, aby sumaryczny koszt wszystkich odcinkow byl minimalny.
 *   \texttt{cuts} to prawe końce tych odcinkow.
 *   Zwraca \texttt{(opt\_cost, cuts)}.
 *   Aby maksymalizowac koszt zamienic nierownosci tam, gdzie wskazane.
 *   Aby uzyskac O(n), nalezy przepisac overtake w oparciu o dodatkowe zalozenia,
 *   aby chodzil w O(1).
 * Time: O(n\log n),
 */

pair<ll, vi> dp_1d1d(int n, function<ll(int,int)> cost) {
	vector<pair<ll, int>> dp(n);
	vi lf(n + 2), rg(n + 2), dead(n);
	vector<vi> events(n + 1);
	int bg = n, en = n + 1;
	rg[bg] = en; lf[en] = bg;
	auto score = [&](int i, int j) {
		return dp[j].x + cost(j + 1, i);
	};
	auto overtake = [&](int a, int b, int mn) {
		int bp = mn - 1, bk = n;
		while (bk - bp > 1) {
			int bs = (bp + bk) / 2;
			if (score(bs, a) <= score(bs, b)) // tu >=
				bk = bs;
			else
				bp = bs;
		}
		return bk;
	};
	auto add = [&](int i, int mn) {
		if (lf[i] == bg) return;
		events[overtake(i, lf[i], mn)].eb(i);
	};
	rep(i,0,n) {
		dp[i] = {cost(0, i), -1};
		rep(j,0,sz(events[i])) {
			int x = events[i][j];
			if (dead[x])
				continue;
			dead[lf[x]] = 1; lf[x] = lf[lf[x]];
			rg[lf[x]] = x; add(x, i);
		}
		if (rg[bg] != en)
			dp[i] = min(dp[i], {score(i, rg[bg]), rg[bg]}); // tu max
		lf[i] = lf[en]; rg[i] = en;
		rg[lf[i]] = i; lf[rg[i]] = i;
		add(i, i + 1);
	}
	vi cuts;
	for (int p = n - 1; p != -1; p = dp[p].y)
		cuts.eb(p);
	reverse(all(cuts));
	return mp(dp[n - 1].x, cuts);
}