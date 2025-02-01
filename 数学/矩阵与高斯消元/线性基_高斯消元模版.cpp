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
把每个LL类型的拆为二进制形式,将所有的二进制拼在一起看做方程组
用类似于高斯消元方法即可
*/

ll a[N],n;

ll deg(ll num,int x){
	return num & (1 << x);
}

void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	int r = 1;
	for(int c = 63;~c && r <= n;c--){
		for(int i = r;i <= n;i++){
			if(deg(a[i],c)){
				swap(a[r],a[i]);
				break;
			}
		}
		if(!deg(a[r],c)) continue;
		for(int i = 1;i <= n;i++){
			if(i == r) continue;
			if(deg(a[i],c)){
				a[i] ^= a[r];
			}
		}
		r++;
	}
	ll ans = 0;
	for(int i = 1;i < r;i++){
		ans ^= a[i];
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