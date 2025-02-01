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
线性求逆元,求出1,2....b中每个数关于质数p的逆元
如果对每个数都进行单次求逆元是O(NlogN)复杂度,有可能会被卡掉

*/
int inv[N],p;

//线性求模p意义下的n个数的逆元
void init(){
	inv[1] = 1;
	for(int i = 2;i <= N;i++){
		inv[i] = (ll)(p - p / i) * inv[p % i] % p;
	}
}

int s[N],a[N],sv[N];
//线性求任意n个数的逆元
//加上这n个数是a[i],s是n个数的前缀积,sv[n]是n个数积的逆元
ll res(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return res;
}

void init1(){
	s[0] = 1;
	for(int i = 1;i <= n;i++) s[i] = s[i - 1] * a[i] % p;
	sv[n] = power(s[n],p - 2);
	for(int i = n;i >= 1;i--) sv[i - 1] = sv[i] * a[i] % p;
	for(int i = 1;i <= n;i++) inv[i] = sv[i] * s[i - 1] % p;
}

void solve(){

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