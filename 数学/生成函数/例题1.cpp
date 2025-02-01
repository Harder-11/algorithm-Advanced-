#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1e9 + 9;
const int hs2 = 998244353;
const int base = 233;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
n种花,分别有f1,f2,...,fn个,求取s朵花的方案数
1 <= n <= 20,0 <= fi <= 1e12,0 <= s <= 1e14

思路看md文件
*/

ll fac = 1,inv,n,f[105],s,ans;

ll power(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

//计算C(x,n-1)
ll C(ll k){
	ll ans = 1;
	for(ll i = s - k + 1;i <= n + s - k - 1;i++){
		ans = (ans * (i % mod)) % mod;
	}
	return ans * inv % mod;
}

void dfs(ll pos,ll op,ll x){
	if(pos == n){
		if(x > s) return;
		ans = ((ans + op * C(x)) % mod + mod) % mod;
		return;
	}
	dfs(pos + 1,op,x);
	dfs(pos + 1,-op,x + f[pos + 1] + 1);
}

void solve(){
	cin >> n >> s;
	for(ll i = 1;i < n;i++){
		fac = (fac * i) % mod;
	}
	inv = power(fac,mod - 2);
	for(ll i = 1;i <= n;i++){
		cin >> f[i];
	}
	dfs(0,1,0);
	cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}