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
给出一个数n,求1到n中有多少数不是2,5,11,13的倍数
1 <= n <= 1e18

思路:很简单的容斥,设a1,a2,a3,a4分别是是2的倍数,5的倍数,11的倍数,13的倍数
那么正难则反,我们求是2,5,11,13的倍数的数,那么就用容斥
而容斥其实类似于状态压缩,我们用二进制位1表示选,0表示不选,那么此时就是遍历1到1 << 4
如果有1个1说明就是选单个的情况,那么就是加,那么根据容斥规律奇数个1就是+,偶数个1就是减
*/

int a[4] = {2,5,11,13};
ll n;

void solve(){
	while(cin >> n){
		ll ans = 0;
		for(int i = 1;i < (1 << 4);i++){
			ll r = 1;
			for(int j = 0;j < 4;j++){
				if((i >> j) & 1){
					r *= a[j];
				}
			}
			if(__builtin_popcount(i) & 1){
				ans += n / r;
			} else ans -= n / r;
		}
		cout << n - ans << '\n';
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