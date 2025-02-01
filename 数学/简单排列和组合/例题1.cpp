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
求位数不超过n,并且数位只含有7,8的数的个数

思路:可以枚举位数k = 1,2....n
那么每一位就只能填7或者8,那么k位数就有2^k种方案,总方案就是2^1 + 2^2 + ... + 2^n = 2^(n+1) - 2
*/

ll n;

void solve(){
	cin >> n;
	cout << (ll)pow(2,n + 1) - 2 << '\n';
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