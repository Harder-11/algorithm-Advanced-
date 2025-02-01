#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 6005;
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
最经典的树形dp
儿子和父亲不能同时选,让求节点权值和最大
定义f[i][0]表示不选择i点时 ,i点及其子树能选出的最大的权值和
f[i][1]就是表示选择i点
很显然f[i][0] += Σ(max(f[j][0],f[j][1]))
f[i][1] = vi + Σf[j][0]
*/

int a[N],n;
vector<int> e[N];
int dp[N][2];

void dfs(int u,int fa){
    for(auto v : e[u]){
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0] += max(dp[v][0],dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) dp[i][1] = a[i];
    for(int i = 1,u,v;i < n;i++){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    cout << max(dp[1][0],dp[1][1]) << '\n';
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