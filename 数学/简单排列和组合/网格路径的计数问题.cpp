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
在n * m的网络图里面,从(0,0)走到(n,m)每次只能往右或者上走,求方案数
显然可以用动态规划f[i][j] = f[i - 1][j] + f[i][j - 1]
但我们也可以看成组合数问题,此时用m个右,n个下,相当于一共有m + n个选择,从中任意选n个下出来
那么答案显然就C(m + n,m)
*/

int n,m;
int mat[1005][1005];

ll inv[N],pre[N];

ll power(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

void init(){
	pre[0] = inv[0] = 1;
	for(int i = 1;i <= n;i++){
		pre[i] = pre[i - 1] * i % mod;
		inv[i] = power(pre[i],mod - 2);
	}
}

//利用组合数求解,只需要求到m!和n!的逆元即可
void solve2(){
	init();
	cout << pre[n + m] * inv[n] % mod * inv[m] % mod << '\n'; 
}

//用动态规划做
void solve(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		mat[i][1] = 1; 
	}
	for(int i = 1;i <= m;i++){
		mat[1][i] = 1;
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			mat[i][j] = mat[i - 1][j] + mat[i][j - 1];
		}
	}
	cout << mat[n][m];
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