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
埃氏筛: 
埃氏筛的核心思想就是用质数把质数的倍数给筛掉
时间复杂度为O(Nlog(logN))
*/
const int maxn = 1e7 + 5;
bool not_prime[maxn];
int prime[maxn],tot = 0;

//埃氏筛
void init(){
	for(int i = 2;i <= maxn;i++){
		//如果是质数就往prime里面加入当前的i
		if(!not_prime[i]){
			prime[++tot] = i;
			//把当前的质数的所有 <= n的倍数全部置为合数
			for(int j = 2 * i;j <= maxn;j += i){
				not_prime[j] = 1;
			}
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