#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 10000005;
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
求正整数n的所有正因子的个数,有q次询问
1 <= n <= 1e7,q <= 1e5

思路:本质就是求d(n)
首先我们用欧拉筛预处理最小质因子,得到最小质因子之后不重复地取出最小质因子并统计出现次数e
n = p1^e1 * p2^e2 * .... * pk^ek
则正整数因子的个数为d(n) = (e1+1)(e2+1)....(ek+1)
*/

//spf是x的最小质因子
int spf[N],prime[N],tot;

void init(){
	for(int i = 2;i <= N;i++){
		//这里可以用!spf[i]代替i是质数,因为没有最小质因子的那肯定就是质数了
		if(!spf[i]){
			spf[i] = i;
			prime[++tot] = i;
		}
		for(int j = 1;j <= tot && i * spf[j] <= N;j++){
			//如果没有标记的话,prime[j] * i的最小质因子就是prime[j]
			spf[i * prime[j]] = prime[j];
			if(i % prime[j] == 0) break;
		}
	}
}

//calc本质就是整数分解定理而已
//分解出来有ei个pi,那么就有ei+1种选择(可以不选pi)
ll calc(int n){
	ll res = 1;
	while(n > 1){
		int fac = spf[n];
		int e = 0;
		while(spf[n] == fac){
			n /= fac;
			e++;
		}
		res *= (e + 1);
	}
	return res;
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