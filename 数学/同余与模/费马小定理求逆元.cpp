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
设p为质数，如果p不整除a，那么a^(p-1) 在模p的意义下与1同余
那么显然对于一个质数p,0 < a < p,a的逆元就是a^(p - 2),可以用乘法快速幂求得
*/

ll power(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

//求逆元直接调用快速幂求mod - 2次幂即可
ll getinv(ll x){
	return power(x,mod - 2);
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