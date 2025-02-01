#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2000005;
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

ll n,prime[N],tot,mu[N],sum_mu[N];
map<ll,ll> mp;
bool vis[N];
int q;

//求莫比乌斯函数前缀和
ll s_mu(ll x){
	if(x < N) return sum_mu[x];
	if(mp[x]) return mp[x];
	ll res = 1;
	for(ll i = 2,j;i <= x;i = j + 1){
		j = x / (x / i);
		res -= s_mu(x / i) * (j - i + 1);
	}
	return mp[x] = res;
}

//求欧拉函数前缀和(莫反写法)
ll s_phi(ll x){
	ll res = 0;
	for(ll i = 1,j;i <= x;i = j + 1){
		j = x / (x / i);
		res += (s_mu(j) - s_mu(i - 1)) * (x / i) * (x / i);
	}
	return (res - 1) / 2 + 1;
}

void solve(){
	cin >> q;
	mu[1] = 1;
	for(int i = 2;i < N;i++){
		if(!vis[i]){
			prime[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1;j <= tot && i * prime[j] < N;j++){
			int p = prime[j];
			vis[i * p] = 1;
			if(i % p == 0){
				mu[i * p] = 0;
				break;
			}
			mu[i * p] = -mu[i];
		}
	}
	for(int i = 1;i < N;i++){
		sum_mu[i] = sum_mu[i - 1] + mu[i];
	}
	while(q--){
		int n;
		cin >> n;
		cout << s_phi(n) << " " << s_mu(n) << '\n';
	}
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