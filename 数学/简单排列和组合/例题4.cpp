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
有3个群岛,每个群岛里面分别有a,b,c个小岛,在这些小岛上建桥,需要满足
一个群岛内的两个小岛至少要经过三座桥才能到达,求建桥的方案数,答案对998244353取模
1 <= a,b,c <= 5000

思路:根据题目可以知道在一个群岛里面是不能有桥的,那么只有三种连法:a-b,a-c,b-c
我们假设a群岛和b群岛之间建了i座桥,那么此时方案数就是
1 + Σ(i=1,a)C(a,i) * C(b,i) * i!,1是从a选0个*b选0个*0个数的总排列数
或者也可以写成1 + Σ(i=1,a)A(a,i) * C(b,i)
那么可以用杨辉三角求组合数C(m,n)再加上求阶乘的函数,复杂度O(c^2)
*/

ll fac[N],a,b,c;
ll C[5005][5005];

void init(){
	fill(fac,fac + N,1);
	C[0][0] = 1;
	for(int i = 1;i <= c;i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1;j < i;j++){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % hs2;
		}
	}
	for(int i = 1;i <= c;i++) fac[i] = fac[i - 1] * i % hs2;
}

ll calc(ll a,ll b){
	ll ans = 1;
	for(int i = 1;i <= a;i++){
		ans = (ans + (C[a][i] * C[b][i]) % hs2 * fac[i] % hs2) % hs2;
	}
	return ans;
}

void solve(){
	cin >> a >> b >> c;
	if(b < a) swap(a,b);
	if(c < a) swap(a,c);
	if(c < b) swap(b,c);
	init();
	cout << calc(a,b) * calc(b,c) % hs2 * calc(a,c) % hs2 << '\n';
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