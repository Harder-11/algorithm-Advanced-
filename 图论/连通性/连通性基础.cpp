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
无向图割点,桥,双联通分量
给定无向连通图G = <V,E>
1.对于一个点x,若从图中删除x及其所有与x相连的边,图就不联通了,那么x就是G的割点
2.对于一条边e,从图中删去e,图不再联通,e就是x的割边
3.一个图如果不存在割点,则它是一个点双联通图,一个图的极大点双联通子图是他的点双联通分量
4.一个图如果不存在割边,则它是一个边双联通图,一个图的极大边双联通子图是他的边双联通分量
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