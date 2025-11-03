/**
 * Author: noshi91
 * Description: Maszynka do niektorych dpkow. $dp[i] = \min_{j}(dp[j] + cost(j+1,i)))$
 * Useful z AliensTrickiem. Consider also LiChao
 * Status: https://contest.ucup.ac/submission/1462651
 * Time: O(n)?
 */
#pragma once

template <class T>
class larsch {
  struct reduce_row;
  struct reduce_col;
  struct reduce_row {
    int n;
    function<T(int, int)> f;
    int cur_row;
    int state;
    unique_ptr<reduce_col> rec;
    reduce_row(int n_) : n(n_), f(), cur_row(0), state(0), rec() {
      const int m = n / 2;
      if (m != 0) rec = make_unique<reduce_col>(m);
    }
    void set_f(function<T(int, int)> f_) {
      f = f_;
      if (rec) {
        rec->set_f([&](int i, int j) -> T
              { return f(2 * i + 1, j); });
      }
    }
    int get_argmin() {
      const int cur_row_ = cur_row;
      cur_row += 1;
      if (cur_row_ % 2 == 0) {
        const int prev_argmin = state;
        const int next_argmin = [&]() {
          if (cur_row_ + 1 == n) { return n - 1; }
          else { return rec->get_argmin(); }
        }();
        state = next_argmin;
        int ret = prev_argmin;
        rep(j,prev_argmin+1,next_argmin+1) {
          if (f(cur_row_, ret) > f(cur_row_, j)) ret = j;
        }
        return ret;
      } else {
        if (f(cur_row_, state) <= f(cur_row_, cur_row_)) {
          return state;
        } else {
          return cur_row_;
        }
      }
    }
  };
  struct reduce_col {
    int n;
    function<T(int, int)> f;
    int cur_row;
    vi cols;
    reduce_row rec;
    reduce_col(int n_) : n(n_), f(), cur_row(0), cols(), rec(n) {}
    void set_f(function<T(int, int)> f_) {
      f = f_;
      rec.set_f([&](int i, int j) -> T
            { return f(i, cols[j]); });
    }
    int get_argmin() {
      const int cur_row_ = cur_row;
      cur_row += 1;
      const auto cs = [&]() -> vi {
        if (cur_row_ == 0) { return {{0}}; }
        else {
          return {{2 * cur_row_ - 1, 2 * cur_row_}};
        }
      }();
      for (const int j : cs) {
        while ([&]() {
          const int size = cols.size();
          return size != cur_row_ && 
            f(size - 1, cols.back()) > f(size - 1, j); 
          }
        ()) { 
          cols.pop_back();
        }
        if (sz(cols) != n) { cols.eb(j); }
      }
      return cols[rec.get_argmin()];
    }
  };
  unique_ptr<reduce_row> base;
public:
  larsch(int n, function<T(int, int)> f)
    : base(std::make_unique<reduce_row>(n)) {
    base->set_f(f);
  }
  int get_argmin() { return base->get_argmin(); }
};
// Example usage: calc jest domkniety (0-indexed)
// dp[0] to pusty dp[i+1].x -> wynik konczacy sie w i
// dp[i+1].y -> liczba przedzialow uzytych
// kara jest z aliensow
// pair<db, int> maybe(db kara) {
//   dp[0] = {0, 0};
//   auto f = [&](int i_, int j) -> db {
//     int i = i_ + 1;
//     if (j >= i) return INF;
//     return dp[j].x + calc(j, i - 1) + kara;
//   };
//   larsch<db> larsch_(n, f);
//   rep(i,0,n) {
//     int j = larsch_.get_argmin();
//     dp[i+1].x = f(i, j);
//     dp[i+1].y = dp[j].y + 1;
//   }
//   return dp[n];
// }
