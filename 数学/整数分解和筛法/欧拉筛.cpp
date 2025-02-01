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
很明显,埃氏筛在把不同质数的倍数置为合数的时候会重复计算很多
比如6是2的倍数同时也是3的倍数,14是2的倍数也是7的倍数,所以时间复杂度会大于O(n)
怎么避免这些重复计算呢?
--使用欧拉筛就可以避免
欧拉筛:每个合数只需要被其最小的质因子筛掉,这样复杂度就是线性的O(n)

*/

const int maxn = 1e7 + 5;
bool not_prime[maxn];
int prime[maxn],tot = 0;

void init(){
	for(int i = 2;i <= maxn;i++){
		if(!not_prime[i]) prime[++tot] = i;
		for(int j = 1;j <= tot && i * prime[j] <= maxn;j++){
			not_prime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
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