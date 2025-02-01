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
给定一个没有前导0的数字n,求有多少没有前导0的数字m,满足:
1.n的数位里面有的数字和m数位里面有的数字一致
2.m中a(0 <= a <= 9)出现的次数不超过n中a出现的次数
(1 <= n <= 1e18)

思路:首先肯定要统计0~9出现的次数,按题意枚举每个数分别出现了多少个
我们假设有sum个数字,cnt[i]为数字i出现的次数,那么全部的排列就有
sum!/(cnt[0]! * cnt[1]! * ... * cnt[9]!)
然后考虑有前导0的情况,把非0的数仿照上面的办法求出排列数,然后把一个0放到开头固定,剩下
的0插空放在这sum个数里面即可
把上面两个值相减就是答案
*/

int cnt[10],a[10];
ll fac[N],ans;
ll n;

void dfs(int x){
	if(x == 10){
		int s = 0;
		for(int i = 0;i < 10;i++) s += a[i];
		ll p = fac[s];
		for(int i = 0;i < 10;i++) p /= fac[a[i]];
		if(a[0] >= 1) p -= (p * a[0] / s);
		ans += p;
		return;
	}
	for(int i = 1;i <= cnt[x];i++){
		a[x] = i;
		dfs(x + 1);
	}
	if(cnt[x] == 0) dfs(x + 1);
}

void solve(){
	cin >> n;
	while(n){
		cnt[n % 10]++;
		n /= 10;
	}
	fac[0] = 1;
	for(int i = 1;i <= 19;i++) fac[i] = fac[i - 1] * i;
	dfs(0);
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