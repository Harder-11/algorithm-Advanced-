#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1005;
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
EK算法是FF方法里面最简答的一个,效率也是最底下的一个
EK算法的流程与ff方法完全相同,只是在寻找增广路的时候使用了BFS
时间复杂度:O(n*m*m),时间复杂度O(m*m)(邻接矩阵)
由于时间复杂度太高,非常暴力,所以使用的地方非常少

*/

int res[N],pre[N],f[N][N],c[N][N];
queue<int> q;

int EK(int s,int t){
    int ans = 0;
    //一直找增广路
    while(1){
        memset(res,0,sizeof res);
        res[s] = INF;
        pre[s] = -1;
        while(!q.empty()){
            int x = q.front();
            q.pop();
            for(int i = 1;i <= t;i++){
                if(!res[i] && f[x][i] < c[x][i]){
                    q.push(i);
                    pre[i] = x;
                    //取当前可以增加的流量值与本身的流量值取min
                    res[i] = min(c[x][i] - f[x][i],res[x]);
                }
            }
        }
        if(res[t] == 0) break; //找不到增广路,退出
        int k = t;
        while(pre[k] != -1){
            f[pre[k]][k] += res[t];//正向边加上新的流量
            f[k][pre[k]] -= res[t];//反向边减去新的流量
            k = pre[k];
        }
        ans += res[t];
    }
    return ans;
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