/**
 * Author: Dominik Wawszczak
 * Description: Wavelet z dowolnymi updatami. Wolny, \tilde 2s na qoju dla $n$=$q$=1e5. Potrzebuje treapa.
 * getsum to suma prefiksowa wartości w treapie
 * Time: O((n + q) \log^2 n)
*/
#pragma once

class wavelet_tree {
private:
  struct wavelet_node {
    int low, high, mid;
    pt rank;
    wavelet_node *left = nullptr, *right = nullptr;
  };
  wavelet_node *root;
  map<int, int> scale;
  vi scale_rev;
  void build(wavelet_node *v, const vi &b) {
    if (v->low == v->high) return;
    v->mid = (v->low + v->high) >> 1;
    v->rank = nullptr;
    v->rank = merge(v->rank, new tnode(0));
    rep(i, 0, sz(b))
      v->rank = merge(v->rank, 
        new tnode(b[i] <= v->mid));
    v->left = new wavelet_node;
    v->left->low = v->low;
    v->left->high = v->mid;
    v->right = new wavelet_node;
    v->right->low = v->mid + 1;
    v->right->high = v->high;
    vi b_left, b_right;
    rep(i, 0, sz(b)) {
      if (b[i] <= v->mid) b_left.eb(b[i]);
      else b_right.eb(b[i]);
    }
    build(v->left, b_left);
    build(v->right, b_right);
  }
  void destroy(wavelet_node *v) {
    if (v->left) destroy(v->left);
    if (v->right) destroy(v->right);
    delete v;
  }
  int kth(wavelet_node *v, int l, int r, int k) {
    if (v->low == v->high) return v->low;
    int a = get_sum(v->rank, l);
    int b = get_sum(v->rank, r);
    int le_mid = b - a;
    if (le_mid > k) return kth(v->left, a, b, k);
    return kth(v->right, l - a, r - b, k - le_mid);
  }
  int cnt_ge(wavelet_node *v, int l, int r, int k) {
    if (v->low == v->high) 
      return (v->low >= k) * (r - l);
    int a = get_sum(v->rank, l);
    int b = get_sum(v->rank, r);
    if (k <= v->mid) return (r - b) - (l - a) 
      + cnt_ge(v->left, a, b, k);
    return cnt_ge(v->right, l - a, r - b, k);
  }
  int cnt(wavelet_node *v, int l, int r, int k) {
    if (v->low == v->high) 
      return (v->low == k) * (r - l);
    int a = get_sum(v->rank, l);
    int b = get_sum(v->rank, r);
    if (k <= v->mid) return cnt(v->left, a, b, k);
    return cnt(v->right, l - a, r - b, k);
  }
  void erase(wavelet_node *v, int i) {
    if (v->low == v->high) return;
    int a = get_sum(v->rank, i)
    int b = get_sum(v->rank, i + 1);
    if (b - a == 1) erase(v->left, a);
    else erase(v->right, i - a);
    v->rank = treap_erase(v->rank, i + 1);
  }
  void insert(wavelet_node *v, int i, int val) {
    if (v->low == v->high) return;
    if (val <= v->mid) 
      insert(v->left, get_sum(v->rank, i), val);
    else 
      insert(v->right, i - get_sum(v->rank, i), val);
    v->rank = 
      treap_insert(v->rank, i + 1, val <= v->mid);
  }
public:
  wavelet_tree(const vi &a, const vi& all_vals) {
    scale.clear();
    scale_rev.clear();
    for (auto val : all_vals) scale[val];
    for (auto &[key, val] : scale) {
      val = sz(scale_rev);
      scale_rev.eb(key);
    }
    vi b(sz(a));
    rep(i, 0, sz(a)) b[i] = scale[a[i]];
    root = new wavelet_node;
    root->low = 0;
    root->high = sz(scale_rev) - 1;
    build(root, b);
  }
  ~wavelet_tree() {
    destroy(root);
  }
  // b = a[l..r]
  // sort(b)
  // return b[k]
  int kth(int l, int r, int k) {
    return scale_rev[kth(root, l, r + 1, k)];
  }
  // return (a[l] >= k) + ... + (a[r] >= k)
  int cnt_ge(int l, int r, int k) {
    auto it = scale.lower_bound(k);
    if (it == scale.end()) return 0;
    return cnt_ge(root, l, r + 1, it->y);
  }
  // return (a[l] == k) + ... + (a[r] == k)
  int cnt(int l, int r, int k) {
    auto it = scale.find(k);
    if (it == scale.end()) return 0;
    return cnt(root, l, r + 1, it->y);
  }
  void erase(int i) { erase(root, i); }
  void insert(int i, int val) { insert(root, i, val); }
  void change(int i, int val) {
    erase(i);
    auto it = scale.find(val);
    assert(it != scale.end());
    insert(i, it->y);
  }
};
