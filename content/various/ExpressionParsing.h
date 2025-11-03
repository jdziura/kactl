/**
 * Author: Shahjalal Shohag
 * Description: Self-explanatory. Dziala arytmetyka w tym unarne +- i nawiasy
 * Status: untested
 * Time: O(n?)
 */
#pragma once

bool delim(char c) { return c == ' '; }
bool is_op(char c) { return c == '+' || 
    c == '-' || c == '*' || c == '/'; }
bool is_unary(char c) { return c == '+' || c == '-'; }
int pri(char op) {
  if (op < 0) return 3;
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return -1; }
void process_op(stack<int>& st, char op) {
  if (op < 0) {
    int l = st.top();
    st.pop();
    switch (-op) {
    case '+':
      st.push(l); break;
    case '-':
      st.push(-l); break;
    }
  } else {
    int r = st.top(); st.pop();
    int l = st.top(); st.pop();
    switch (op) {
    case '+':
      st.push(l + r); break;
    case '-':
      st.push(l - r); break;
    case '*':
      st.push(l * r); break;
    case '/':
      st.push(l / r); break;
    }
  }
}
int evaluate(string s) {
  stack<int> st;
  stack<char> op;
  bool may_be_unary = true;
  rep(i,0,sz(s)) {
    if (delim(s[i])) continue;
    if (s[i] == '(') {
      op.push('(');
      may_be_unary = true;
    } else if (s[i] == ')') {
      while (op.top() != '(') {
        process_op(st, op.top());
        op.pop();
      }
      op.pop();
      may_be_unary = false;
    } else if (is_op(s[i])) {
      char cur_op = s[i];
      if (may_be_unary && is_unary(cur_op))
        cur_op = -cur_op;
      while (!op.empty() && (
        (cur_op >= 0 && pri(op.top()) >= pri(cur_op)) ||
        (cur_op < 0 && pri(op.top()) > pri(cur_op))
      )) {
        process_op(st, op.top());
        op.pop();
      }
      op.push(cur_op);
      may_be_unary = true;
    } else {
      int number = 0;
      while (i < sz(s) && isalnum(s[i])) {
        number = number * 10 + s[i++] - '0';
      }
      --i;
      st.push(number);
      may_be_unary = false;
    }
  }
  while (!op.empty()) {
    process_op(st, op.top());
    op.pop();
  }
  return st.top();
}