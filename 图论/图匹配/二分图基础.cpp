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
二分图又称为二部图,是图论中的一种特殊模型,设G=<V,E>是一个无向图,如果顶点V可以分成
两个互不相交的子集(A,B),并且图中的每条边(i,j)所关联的两个顶点i和j分别属于这两个不同的顶点集(i in A,j in B)
则图G成为一个二分图
二分图的充分必要条件:至少有两个顶点并且没有奇环
二分图的判断:黑白染色法:只要全部染色后出现矛盾(那么肯定存在奇环),那么就不是二分图,反之就是二分图
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