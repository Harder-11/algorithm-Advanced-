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
求一个数的所有因数(1 <= n <= 1e12)
直接暴力求即可,但是注意完全平方数的去重操作
利用整数分解定理可以知道一个数可以由若干质数相乘得到N = p1^α1 * p2^α2 * .....
注意最后特判n是否>1,如果>1就把此时的n加入fac就行
*/

int n;
std::vector<ll> fac;
void init(){
	for(int i = 2;i <= n / i;i++){
		if(n % i == 0){
			fac.push_back(i);
			while(n % i == 0) n /= i;
		}
	}
	if(n > 1) fac.push_back(n);
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