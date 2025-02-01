#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 2004;
const double eps = 1e-9;
const int hs1 = 1e9 + 9;
const int hs2 = 998244353;
const int base = 233;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

ll n,a,b,m[N];

//由于mod不是指数,我们不能直接求逆元
//我们发现n!很小,这样我们就可以先对原式子的分子mod(mod * n!)
//然后再除以n!即可,这样就解决逆元问题

ll C(ll n,ll m){
	if(n < m) return 0;
	ll x = 1,y = 1,p = mod;
	for(int i = 1;i <= m;i++){
		x *= i;
		p *= i;
	}
	for(int i = n - m + 1;i <= n;i++){
		y = y * i % p;
	}
	return y / x % p;
}

ll dfs(ll x,ll sum,ll op,ll tot){
	if(x > n){
		return C(n + tot - sum,n) * op;
	}
	return (dfs(x + 1,sum,op,tot) + dfs(x + 1,sum + m[x] + 1,-op,tot) + mod) % mod;
}

void solve(){
	cin >> n >> a >> b;
	for(int i = 1;i <= n;i++) cin >> m[i];
	cout << (dfs(1,0,1,b) - dfs(1,0,1,a - 1) + mod) % mod << '\n';
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