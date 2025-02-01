#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
const int mod = 998244353;
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
具体题目与分析看md文件
*/

ll mu[N],prime[N],inv[N],f[N],vis[N],tot;
ll n;

ll m(ll x){
	return (x % mod + mod) % mod; 
}

void init(int n){
	mu[1] = 1;
	for(int i = 2;i <= n;i++){
		if(vis[i] == 0){
			prime[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1;j <= tot && i * prime[j] <= n;j++){
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0){
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 2;i * j <= n;j++){
			f[i] = (f[i] + f[i * j]) % mod;
		}
	}
}

void solve(){
	cin >> n;
	ll sum = 0;
	for(int i = 1,x;i <= n;i++){
		cin >> x;
		f[x] = (f[x] + x) % mod;
		sum = (sum + x) % mod;
	}
	init(1000000);
	inv[1] = 1;
	for(int i = 2;i < N;i++){
		inv[i] = m(-inv[mod % i] * (mod / i));
	}
	ll ans = 0;
	for(int i = 1;i < N;i++){
		ll res = 0;
		for(int j = 1;j * i < N;j++){
			res = m(res + m(f[i * j] * f[i * j] * mu[j]));
		}
		ans = m(ans + m(inv[i] * res));
	}
	cout << m((ans - sum) * inv[2]) << '\n'; 
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