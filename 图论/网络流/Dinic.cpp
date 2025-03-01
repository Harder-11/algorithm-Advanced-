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
Dinic算法是基于"层次图"的时间效率优先的最大流算法
层次图:是从源点走到那个点的最短路径长度
那么我们得到一个定理:从源点开始,在层次图中沿着边不管怎么走,经过的路径一定是终点在剩余图中的最短路
如果回溯到了原点而且没法继续往下走的时候,dfs结束
所以一次dfs可以找到多条增广路
dfs结束后,对残留网再次分层,当bfs分层操作不能到达汇点的时候,算法结束
*/

int n,m;
int h[N],to[N],w[N],nxt[N],cnt;
//dep是用作分层图,q是模拟队列
int dep[N],q[N];

void add(int u,int v,int c){
    nxt[cnt] = h[u];
    to[cnt] = v;
    w[cnt] = c;
    h[u] = cnt++;
}

bool bfs(int s,int t){
    memset(dep,0,sizeof dep);
    memset(q,0,sizeof q);
    dep[s] = 1;
    int l = 0,r = 0;
    q[r++] = s;
    while(l < r){
        int x = q[l++];
        if(x == t) return 1;
        for(int i = h[x];i != -1;i = nxt[i]){
            int v = to[i];
            //如果w[i] == 0,说明是饱和弧了,不能走,直接进行下一层循环
            if((dep[v] == 0) && (w[i] != 0)){
                q[r++] = v;
                dep[v] = dep[x] + 1;
            }
        }
    }
    return 0;
}

int dfs(int x,int flow,int t){
    if(x == t) return flow;
    //当前点x能往后面流出的流量
    int sum = 0;
    for(int i = h[x];i != -1;i = nxt[i]){
        int v = to[i];
        if((w[i] != 0) && (dep[v] == dep[x] + 1)){
            //取决的流量是剩余的流量和w[i]本身弧流量的更小值
            int tmp = dfs(v,min(flow - sum,w[i]),t);
            w[i] -= tmp;
            w[i ^ 1] += tmp;
            sum += tmp;
            if(sum == flow) return sum;
        }
    }
    return sum;
}

ll dinic(){
    ll ans = 0;
    while(bfs(1,m)){
        ans += dfs(1,INF,m);
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