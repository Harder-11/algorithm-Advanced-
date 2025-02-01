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
有n个男孩和m个女孩,需要选一个t人小组里面至少有4个男孩和1个女孩
求选小组的方案数
其中n,m <= 30,t <= n + m

思路:我们假设选k个女孩,那么此时1 <= k <= t - 4,那么此时有t - k个男孩
所以方案数就是Σ(k = 1,t - 4)C(k,m) * C(t - k,n)
此时应该用递推的方式求组合数,因为求阶乘会爆LL,而且本题没有取模就会出错
*/

ll n,m,t;

ll C(ll a,ll b){
	ll res = 1;
	for(int i = 1;i <= a;i++){
		res = res * (b - i + 1) / i;
	}
	return res;
}

void solve(){
	cin >> n >> m >> t;
	ll ans = 0;
	for(int i = max(4ll,t - m);i <= min(t - 1,n);i++){
		ans += C(i,n) * C(t - i,m);
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