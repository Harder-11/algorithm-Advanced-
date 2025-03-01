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
König定理:
二分图中的最大匹配数等于这个图中的最小点覆盖数
最小点覆盖就是:选最少的点,这些点所连的边的集合能包含图所有的边

证明可以看oi wiki
利用不等式最大匹配数 >= 最小点覆盖数 && 最大匹配数 <= 最小点覆盖数来证明二者相等
*/

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