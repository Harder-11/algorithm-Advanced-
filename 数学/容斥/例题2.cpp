#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 100005;
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
共有4种硬币,面值分别为c1,c2,c3,c4
某人去商店买东西,去了n次,对于每次购买,他带了di枚i种硬币,想购买s的价值的东西
请问有多少种付款方法?

输入第一行是5个整数,代表c1,c2,c3,c4,n
接下来n行,每行有5个整数描述一次购买,分别代表d1,d2,d3,d4,s
*/

ll c[5],d[5],n,s;
ll f[N];

void solve(){
	cin >> c[1] >> c[2] >> c[3] >> c[4] >> n;
	f[0] = 1;
	//把所有价值为i时的硬币组成的方案数求出来
	for(int j = 1;j <= 4;j++){
		for(int i = 1;i < N;i++){
			if(i >= c[j]) f[i] += f[i - c[j]];
		}
	}
	for(int k = 1;k <= n;k++){
		cin >> d[1] >> d[2] >> d[3] >> d[4] >> s;
		ll ans = 0;
		for(int i = 1;i < (1 << 4);i++){
			ll m = s,bit = 0;
			for(int j = 1;j <= 4;j++){
				if((i >> (j - 1)) & 1){
					m -= (d[j] + 1) * c[j];
					bit++;
				}
			}
			if(m >= 0) ans += (bit % 2 * 2 - 1) * f[m];
		}
		cout << f[s] - ans << '\n';
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