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
TSP(Travelling Saleman Problem,TSP)又称旅行推销员问题
给你一张图(你可以认为是抽象了的地图,由若干点和边组成,求从某个起点出发,经过所有点的最短路径)
由于已经走过的点与接下来走的最短路径是没有任何关系的
那么确定状态f[st][i]表示当前状态st,最后到达的一个点是i,所经过的最短距离
那么状态转移方程就是
f[st][i] = min(f[st'][j] + a[j][i])
其中st'就是去掉当前节点对应的二进制的那一位1的数,j就是之前已经是1的那些节点(从二进制数中找)
st' = st - (1 << (i - 1))
终点就是min(f[(1 << n) - 1][i])

扩展:要回到原点怎么办?
如果要回到原点并且不重复经过任何一个节点,那么走出来的顺序一定是一个环,并且环中不包含任何重复节点
那么此时就固定以1作为起点,然后求到所有的f[(1 << n) - 1][i]
对于每一个i(i=2,3,....)求每个节点到1的值加上即可(必须是和1直接相邻的边,否则会经过其他节点,不符合题意,设为INF)
时间复杂度2^n * n^2
*/

int n,m,k,x,y,z;
//图很小,直接用邻接矩阵存图
int a[25][25];
ll f[(1 << 20) + 10][21];
ll ans = LLONG_MAX;

ll dfs(int st,int x){
    if(f[st][x] <= 1e18){
        return f[st][x];
    }
    //先把当前的状态算出来,方便后面使用
    //注意这里主函数里面是枚举的最后一个到达的节点,那么首先要把该节点给删去
    //得到now状态,再用now状态去枚举才行
    int now = st - (1 << (x - 1));
    for(int i = 1;i <= n;i++){
        if(a[i][x] == 0) continue;
        //当遇到当前状态位是1,那么就继续dfs递归并且加上边权
        if(((now >> (i - 1)) & 1) == 1){
            f[st][x] = min(f[st][x],dfs(now,i) + a[i][x]);
        }
    }
    return f[st][x];
}

void solve(){
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        cin >> x >> y >> z;
        //处理重边的办法
        a[x][y] = min(a[x][y],z);
        a[y][x] = min(a[y][x],z);
    }
    memset(f,0x3f,sizeof f);
    f[1][1] = 0;
    int st = (1 << n) - 1; 
    for(int i = 2;i <= n;i++){
        ll tmp = dfs(st,i);
        if(a[i][1] != 0) ans = min(ans,tmp + a[i][1]);
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
/*
5 9
1 2 2
1 3 7
1 4 2
1 5 4
2 3 10
2 4 6
2 5 3
3 4 4
4 5 1
*/