#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;
using vi=vector<int>;
using vl=vector<ll>;
using vpi=vector<pi>;
#define mp make_pair
#define eb emplace_back
#define x first
#define y second
#define sz(x)int((x).size())
#define all(x)begin(x),end(x)
#define rep(i,a,b)for(int i=(a);i<(b);i++)
#define per(i,a,b)for(int i=(b)-1;i>=(a);i--)
bool ckmin(auto&a,auto b){return b<a?a=b,1:0;}
bool ckmax(auto&a,auto b){return b>a?a=b,1:0;}
#ifdef LOCAL
auto&operator<<(auto&o,pair<auto,auto>p);
auto operator<<(auto&o,auto x)->decltype(x.end(),o){
  o<<"{";int i=0;
  for(auto&e:x)o<<","+!i++<<e;
  return o<<"}";
}
auto&operator<<(auto&o,pair<auto,auto>p){
  return o<<"("<<p.x<<", "<<p.y<<")";}
#define debug(X...)cerr<<"["#X"]: ",[](auto...$){\
  ((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define debug(...){}
#endif

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	return 0;
}
