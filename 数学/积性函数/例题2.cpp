#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 20000005;
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
求从1~n的(i^n mod (1e9 + 7))的异或和,1 <= n <= 1.3 * 1e7
我们很容易发现f(n) = n^N是一个积性函数,也就是任给一个p,q,都有(pq)^N=p^N*q^N
我们就需要计算所有的f(p)
*/

int minp[N],prime[N],res[N],tot;

ll power(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

//利用欧拉筛在O(n)的时间直接一次遍历即可填充完res数组
void init(int n){
	for(int i = 2;i <= n;i++){
		if(minp[i] == 0){
			minp[i] = i;
			res[i] = power(i,n);
			prime[++tot] = i;
		}
		for(int j = 1;j <= tot && i * prime[j] <= n;j++){
			minp[i * prime[j]] = prime[j];
			res[i * prime[j]] = 1ll * res[i] * res[prime[j]] % mod;
			if(i % prime[j] == 0) break;
		}
	}
}

void solve(){
	int n;
	cin >> n;
	init(n);
	int ans = 1;
	for(int i = 2;i <= n;i++) ans ^= res[i];
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