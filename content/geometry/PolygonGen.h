/**
 * Author: Warsaw Eagles
 * Description: Zwraca wielokat o $n$ punktach w zakresie $[-\texttt{r}, \texttt{r}]$,
 * ktory nie zawiera jakiejkolwiek trojki wspolliniowych punktow.
 * Ciagnie do $\sim 80$. Dla $n < 3$ zwraca zdegenerowane.
 */
#pragma once

vector<P> gen_polygon(int n, int r) {
  vector<P> t;
  while (sz(t) < n) {
	P p(randr(-r, r), randr(-r, r));
    if ([&]() {
	  rep(i,0,sz(t)) rep(j,0,i)
        if (eq(cross(t[j] - t[i], p - t[j]), 0))
		  return false;
		return find(t.begin(), t.end(), p) == t.end();
	}())
	  t.eb(p);
  }
  bool go = true; 
  while (go) {
    go = false;
    rep(i,0,n)
      rep(j,0,i - 1)
        if ((i+1) % n != j && sz(segIsect({t[i], t[(i+1)%n]}, {t[j], t[j+1]}))) {
          swap(t[(i + randr(0, 1)) % n], t[(j + randr(0, 1)) % n]);
          go = true;
        }
  }
  return t;
}