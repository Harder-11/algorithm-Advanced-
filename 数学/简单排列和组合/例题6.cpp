#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
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
求满足以下条件的数列的个数,对答案取模998244353
1.数列的长度为n
2.数列中每个元素都是1到m的整数
3.数列中有恰好一对相等的元素
4.数列a中存在一个下标i,满足如果j < i,则aj < a(j + 1),如果j >= i,aj > a(j + 1)
2 <= n <= m <= 2e5

思路:分析题干给的条件,可以得出:1 <= ai <= m,a1 < ... < a(i-1) < ai > a(i+1) > ... > an
而数列中恰好有一对相等的元素,说明a1~an有n-1个不相同的[1,m]中的数
目前我们已经确定了三个数:最大的那个数和相同的那两个数,其余的数字都有两种选择:放左边或者右边
所以此时有2^(n-3)种,然后确定数组中的数字,从1~m选取n-1个数,然后选取一个非最大值的数字作为重复数字
此时有C(m,n - 1) * (n-2)种选法,所以最终答案就是
注意:n = 2的时候必定无解,需要特判
*/

ll n,m;
ll ans = 1,res = 1;

ll power(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

ll inv(ll x){
	return power(x,mod - 2);
}

void solve(){
	cin >> n >> m;
	if(n == 2){
		cout << 0 << '\n';
		return;
	}
	for(int i = 1;i <= m;i++) ans = ans * i % mod;
	for(int i = 1;i <= n - 1;i++) res = res * i % mod;
	for(int i = 1;i <= m - n + 1;i++){
		res = res * i % mod;
	}
	ans = ((ans * inv(res) % mod) * (n - 2) % mod) * power(2,n - 3) % mod;
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