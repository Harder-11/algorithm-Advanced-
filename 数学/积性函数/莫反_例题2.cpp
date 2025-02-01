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
求Σ(A1=1,k)Σ(A2=1,k)....Σ(AN=1,k)gcd(A1,A2,....AN) mod (1e9 +7)
*/

ll n,k;
int prime[N],tot,phi[N];
bool v[N];

ll power(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

void init(){
	phi[1] = 1;
	for(int i = 2;i < N;i++){
		if(!v[i]){
			prime[++tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1;j <= tot && i * prime[j] < N;j++){
			v[prime[j] * i] = 1;
			if(i % prime[j] == 0){
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
}

void solve(){
	cin >> n >> k;
	init();
	ll ans = 0;
	for(int i = 1;i <= k;i++){
		ans = (ans + power(k / i,n) * phi[i] % mod) % mod;
	}
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