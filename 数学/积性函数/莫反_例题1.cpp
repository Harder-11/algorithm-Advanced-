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
两个长度为n的序列a,b,求满足gcd(x,y)=1并且a(b_x) = b(a_y)的数对(x,y)的数量
(1 <= n <= 1e5,1 <= ai,bi <= n)

*/

int n,a[N],b[N];
ll g[N],cnt[N];
int prime[N],minp[N],mu[N],tot;

void init(){
	mu[1] = 1;
	for(int i = 2;i < N;i++){
		if(minp[i] == 0){
			minp[i] = i;
			//此时只有1个质因数,所以令为-1
			mu[i] = -1;
			prime[++tot] = i;
		}
		for(int j = 1;j <= tot && i * prime[j] < N;j++){
			minp[i * prime[j]] = prime[j];
			if(minp[i] == prime[j]){
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
}

void solve(){
	cin >> n;
	init();
	for(int i = 0;i < n;i++){
		cin >> a[i];
		a[i]--;
	}
	for(int i = 0;i < n;i++){
		cin >> b[i];
		b[i]--;
	}
	for(int d = 1;d <= n;d++){
		for(int i = d - 1;i < n;i += d){
			cnt[a[b[i]]]++;
		}
		for(int i = d - 1;i < n;i += d){
			g[d] += cnt[b[a[i]]];
		}
		for(int i = d - 1;i < n;i += d){
			cnt[a[b[i]]]--;
		}
	}
	ll ans = 0;
	for(int i = 1;i <= n;i++){
		ans += mu[i] * g[i];
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