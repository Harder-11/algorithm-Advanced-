#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 10005;
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
给定一棵无向树,当一个点被覆盖的时候,与它相邻的所有点都会被覆盖,问最少的点数
如果仍然是设dp[N][2],当前点选择就是dp[i][1],不选就是dp[i][0]
那么此时对于每个点的转移方程,假设要选当前的节点那么显然就是dp[i][1] = Σ(dp[j][0])
但是不选当前结点的情况就比较麻烦,不知道是选上父亲覆盖当前节点还是选儿子覆盖当前节点
那么此时换思路:确定状态dp[i][0]:选点i,并且以点i为根的子树都被覆盖了
dp[i][1]:不选点i,i被其儿子覆盖(i的儿子至少有1个要选)
dp[i][2]:不选i点,i被其父亲覆盖(儿子可选可不选)
那么此时的状态转移方程就是dp[i][0] = 1 + Σmin(dp[u][0],dp[u][1],dp[u][2])
dp[i][2] = Σmin(dp[u][1],dp[u][0])(此时就不能靠父亲了,因为i不选,所以没有dp[u][2])
对于dp[i][1],他的所有儿子里面必须有一个取dp[u][0],剩下的所有儿子里面在dp[u][1]和dp[u][0]
里面选出累加和最小的所有节点
那么如果i没有子节点,dp[i][1] = INF,否则dp[i][1] = Σ(dp[u][0],dp[u][1]) + (inc)
其中,对于inc来说,如果存在有min(dp[u][0],dp[u][1])=dp[u][0],inc = 0
否则,inc = min(dp[u][0],dp[u][1])
*/

int n;
vector<int> e[N];
int dp[N][3];

void dfs(int u,int fa){
    dp[u][0] = 1,dp[u][1] = INF;
    for(auto v : e[u]){
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0] += min({dp[v][0],dp[v][1],dp[v][2]});
        dp[u][2] += min(dp[v][1],dp[v][0]);
    }
    for(auto v : e[u]){
        if(v == fa) continue;
        dp[u][1] = min(dp[u][1],dp[u][2] - min(dp[v][0],dp[v][1]) + dp[v][0]);
    }
}

void solve(){
    cin >> n;
    for(int i = 1,u,v;i < n;i++){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    //最后输出的根节点不能有dp[1][2]
    cout << min({dp[1][0],dp[1][1]}) << '\n';
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