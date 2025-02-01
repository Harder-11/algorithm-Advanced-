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
空间异或线性基
贪心法:对原集合的每个数p转为二进制,从高到低位扫,对于第x位是1的,如果ax不存在
那么令ax <- p并结束扫描,如果存在,则令p <- p XOR ax
查询原集合内任意几个元素XOR的最大值,只需要将线性基从高位向低位扫,若XOR上当前扫到的ax答案变大,就把答案异或上ax

*/

ll p[64];

void insert(ll x){
	for(int i = 63;~i;i--){
		if(!(x >> i)){
			continue;
		}
		if(!p[i]){
			p[i] = x;
			break;
		}
		x ^= p[i];
	}
}

void solve(){
	int n;
	cin >> n;
	ll a;
	for(int i = 1;i <= n;i++){
		cin >> a;
		insert(a);
	}
	ll ans = 0;
	for(int i = 63;~i;i--){
		ans = max(ans,ans ^ p[i]);
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