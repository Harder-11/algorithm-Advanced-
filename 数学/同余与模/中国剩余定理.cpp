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
中国剩余定理:
1.计算所有的模的积n
2.对于第i个方程:a.计算mi = n / ni;b.计算mi在模ni意义下的逆元mi^(-1);c.计算ci = mi*mi^(-1)
3.方程组在模n意义下的唯一解就是:x = Σ(i=1,k)aici(mod n)
*/

//a数组和r数组分别是同余的数和模数
ll n,a[N],b[N],M = 1;

void exgcd(ll a,ll b,ll &x,ll &y){
	if(b == 0){
		x = 1,y = 0;
		return;
	}
	exgcd(b,a % b,x,y);
	ll t = x;
	x = y;
	y = t - a / b * y;
}

ll CRT(){
	ll ans = 0,Mi,x,y;
	for(int i = 1;i <= n;i++){
		Mi = M / a[i];
		exgcd(Mi,a[i],x,y);
		ans = ((ans + b[i] * Mi * x % M) % M + M) % M;
	}
	return (ans % M + M) % M;
}


void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i] >> b[i];
		M *= a[i];
	}
	cout << CRT() << '\n';
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