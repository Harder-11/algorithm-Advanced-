#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 12005;
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
https://www.luogu.com.cn/problem/P2764
给定有向图G=<V,E>,设P是G的一个简单路(顶点不相交)的集合
如果V中每个顶点恰好在P的一条路上,则称P是G的一个路径覆盖
P中路径可以从V的任何一个顶点开始,长度也是任意的,特别的可以为0
G的最小路径覆盖是G的所含路径条数最少的路径覆盖;
设计一个有效算法求一个有向无环图G的最小路径覆盖
1<=n<=150,1<=m<=6000

首先我们给每个点都搞一条路径去覆盖,那么此时有n条路径
然后我们把每个点拆为两个点,表示为该点的入和出,那么如果有a连向b的边就可以看做a出->b入
然后我们创建一个超级源点S和超级汇点T,此时S向所有的出点连容量为1的边
然后所有的入点向T连一个容量为1的边,最后求最大流,最后答案就是点数-最大流
为什么这样是正确的?
因为每个点只能在图上属于一个路径,那么最大流容量为1刚好可以满足这个条件
那么求到的最大流的值就是可以减少的路径条数

*/

int n,m;
int h[N],to[N],nxt[N],w[N],dep[N],q[N],cnt;

void add(int u,int v,int c){
    nxt[cnt] = h[u];
    to[cnt] = v;
    w[cnt] = c;
    h[u] = cnt++;
}

void addEdge(int u,int v,int c){
    add(u,v,c);
    add(v,u,0);
}

bool bfs(int s,int t){
    memset(dep,0,sizeof dep);
    memset(q,0,sizeof q);
    dep[s] = 1;
    int l = 0,r = 0;
    q[r++] = s;
    while(l < r){
        int u = q[l++];
        if(u == t) return 1;
        for(int i = h[u];~i;i = nxt[i]){
            int v = to[i];
            if((dep[v] == 0) && (w[i] != 0)){
                q[r++] = v;
                dep[v] = dep[u] + 1;
            }
        }
    }
    return 0;
}

int dfs(int x,int flow,int t){
    if(x == t) return flow;
    int sum = 0;
    for(int i = h[x];~i;i = nxt[i]){
        int v = to[i];
        if((w[i] != 0) && (dep[v] == dep[x] + 1)){
            int tmp = dfs(v,min(flow - sum,w[i]),t);
            w[i] -= tmp;
            w[i ^ 1] += tmp;
            sum += tmp;
            if(sum == flow) return flow;
        }
    }
    return sum;
}

int dinic(int s,int t){
    int ans = 0;
    while(bfs(s,t)){
        ans += dfs(s,INF,t);
    }
    return ans;
}

void solve(){
    cin >> n >> m;
    memset(h,-1,sizeof h);
    int T = 2 * n + 1;
    for(int i = 1;i <= n;i++){
        addEdge(0,2 * i - 1,1);
        addEdge(2 * i,T,1);
    }
    for(int i = 1;i <= m;i++){
        int u,v;
        cin >> u >> v;
        addEdge(2 * u - 1,2 * v,1);
    }
    int flow = dinic(0,T);
    vector<int> match(n + 1);
    for(int u = 1;u <= n;u++){
        int l = 2 * u - 1;
        //我们枚举左侧节点2u-1,到右侧节点2v的边,如果w=0,那么u和v匹配
        for(int i = h[l];~i;i = nxt[i]){
            int v = to[i];
            if(v >= 2 && v <= 2 * n && v % 2 == 0 && w[i] == 0){
                match[u] = v / 2;
                break;
            }
        }
    }
    //标记那些顶点有入边匹配
    vector<bool> check(n + 1,false);
    vector<vector<int>> paths;
    //这个填写check数组很重要,上面的match是得到的左侧节点连接的右侧点信息
    //这里check就把右侧点置为1,这样一来,一条链上的最开始的结点会是false
    //因为没有其他点向其连边,自然就不会为1
    for(int u = 1;u <= n;u++){
        if(match[u]){
            check[match[u]] = 1;
        }
    }
    for(int u = 1;u <= n;u++){
        if(!check[u]){
            vector<int> path;
            int cur = u;
            while(cur){
                path.push_back(cur);
                cur = match[cur];
            }
            paths.push_back(path);
        }
    }
    for(auto &x : paths){
        int len = x.size();
        for(int i = 0;i < len;i++){
            cout << x[i] << " \n"[i == len - 1];
        }
    }
    cout << paths.size() << '\n';
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