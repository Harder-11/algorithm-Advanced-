#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
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
给定两个数字a,b(1 <= a < b <= 9),满足位数中只有a和b的数称为好数
满足其数位和也是好数的好数称为极好数,求位数为n的极好数的数量,对答案取模1e9 + 7
1 <= n <= 1e6

思路:对于一个n位的数,假设有x个a,n - x个b,那么此时数位和就是ax + b(n - x)
那么此时数位和是只和a,b的个数有关
那么此时对于ax + b(n - x) <= 9x + 9(n - x) = 9n
所以我们只需要枚举a的个数即可,从1到1e6
*/

ll inv[N],fac[N],ans;
int n,a,b;

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
	inv[0] = fac[0] = 1;
	for(int i = 1;i < N;i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	for(int i = 1;i < N;i++){
		inv[i] = power(fac[i],mod - 2);
	}
}

ll C(int n,int m){
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

bool check(int n){
	while(n){
		if(n % 10 != b && n % 10 != a) return 0;
		n /= 10;
	}
	return 1;
}

void solve(){
	cin >> a >> b >> n;
	init();
	for(int i = 0;i <= n;i++){
		if(check(a * i + b * (n - i))){
			ans = (ans + C(n,i)) % mod;
		}
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