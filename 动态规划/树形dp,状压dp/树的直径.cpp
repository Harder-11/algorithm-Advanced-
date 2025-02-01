#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs = 1331;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
树的直径:2遍dfs方法
首先随便选一个点为根节点,然后利用树型dp往下搜到距离最远的那个节点,假设为A
然后以A节点为根,找到离A节点最远的那个节点,这个距离就是树的直径
*/

int n;
int dp[N];
vector<int> e[N];
int dis,node;

void dfs(int u,int fa,int dist){
    //每次更新dis和最远节点值
    if(dist > dis){
        dis = dist;
        node = u;
    }
    for(auto v : e[u]){
        if(v == fa) continue;
        dfs(v,u,dist + 1);
    }
}

void solve(){
    cin >> n;
    for(int i = 1,u,v;i < n;i++){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0,0);
    dfs(node,0,0);
    cout << dis << '\n';
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