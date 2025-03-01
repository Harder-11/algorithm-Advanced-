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

// 原题说明参考：https://www.luogu.com.cn/problem/P3225
// 题目描述：煤矿工地可看作由隧道连接挖煤点构成的无向图，要求在工地任一挖煤点坍塌后，其它挖煤点仍有道路通向救援出口。
// 思路：利用 Tarjan 算法求割点和双联通分量，然后构造块树。若图中无割点，则答案为2且方案数为 n*(n-1)/2（n为顶点数）；
// 否则，对于每个双联通分量（BCC），如果其中恰好包含1个割点，则该 BCC 在块树上为“叶子”，
// 救援出口的选择数即为 (BCC 内顶点数-1)（非割点的数目）；答案即为叶子 BCC 的个数，方案数为各叶子贡献数的乘积。
// 注：若只有一个顶点，则答案为1，方案数为1。

// 原代码中使用的图邻接表
int n, m, u, v, root;
int dfn[N], low[N], vis[N], b[N]; // b[x]==1 表示 x 为割点
// 注意：原代码中的 tot 在我们新实现中仅作为时间戳计数使用
int tot;
int h[N], to[N], nxt[N], cnt;
vector<int> res[N]; // 此处保留原有变量，但我们不在后续中使用它
// 为了区分割点与非割点，原代码中用 col[] 进行染色；本题不再使用该数组
int col[N];

// 重置图数据（注意：变量名不能变）
void add(int u, int v){
    nxt[++cnt] = h[u];
    to[cnt] = v;
    h[u] = cnt; 
}

// 为了提取双联通分量（BCC）和割点，我们新增结构体 Edge 及全局容器
struct Edge {
    int u, v;
};

stack<Edge> stEdge;           // 边栈，用于记录当前的搜索路径
vector<vector<int>> bcc;      // 存储所有 BCC，每个 BCC 为若干顶点集合

// 新实现的 Tarjan 算法（增加父节点参数 fa，逻辑与原代码风格保持一致）
// 注：b[] 数组用于标记割点（1 表示割点）；dfn[] 与 low[] 均从 1 开始计时。
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    int children = 0;
    for (int i = h[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == fa) continue;  // 避免走回父亲（幽默提醒：矿井里走路，别走回头路）
        if(!dfn[v]){
            stEdge.push({u, v});
            children++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            // 若 u 为根节点且其孩子数大于1，或者 u 不是根且 low[v] >= dfn[u]，则 u 为割点
            if((fa == -1 && children > 1) || (fa != -1 && low[v] >= dfn[u])){
                b[u] = 1;  // 标记 u 为割点
                vector<int> comp;
                // 从边栈中弹出边直到当前边 (u,v) 为止，构成一个 BCC
                while(!stEdge.empty()){
                    Edge e = stEdge.top();
                    stEdge.pop();
                    comp.push_back(e.u);
                    comp.push_back(e.v);
                    if(e.u == u && e.v == v) break;
                }
                // 去重排序
                sort(comp.begin(), comp.end());
                comp.erase(unique(comp.begin(), comp.end()), comp.end());
                bcc.push_back(comp);
            }
        } else if(dfn[v] < dfn[u]){
            stEdge.push({u, v});
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 1;
    // 注意：输入以隧道数 n 为开头，n==0 时结束（与题目样例一致）
    while(cin >> n && n != 0){
        // 重置图相关数据
        cnt = 0;
        memset(h, 0, sizeof(h));
        // 题目中点编号不一定连续，这里 m 表示各边中最大点编号
        m = 0;
        for (int i = 1; i <= n; i++){
            cin >> u >> v;
            m = max(m, max(u, v));
            add(u, v);
            add(v, u);
        }
        
        // 重置辅助数组（1..m）
        for (int i = 1; i <= m; i++){
            dfn[i] = 0;
            low[i] = 0;
            b[i] = 0;
        }
        tot = 0;
        // 清空边栈和 bcc 容器
        while(!stEdge.empty()) stEdge.pop();
        bcc.clear();

        // 运行 Tarjan 算法（图是连通的，但为了保险起见逐点启动）
        for (int i = 1; i <= m; i++){
            if(!dfn[i])
                tarjan(i, -1);
        }
        // 如果还有剩余边，则构成一个 BCC
        if(!stEdge.empty()){
            vector<int> comp;
            while(!stEdge.empty()){
                Edge e = stEdge.top();
                stEdge.pop();
                comp.push_back(e.u);
                comp.push_back(e.v);
            }
            sort(comp.begin(), comp.end());
            comp.erase(unique(comp.begin(), comp.end()), comp.end());
            bcc.push_back(comp);
        }
        
        // 计算答案：
        // 如果图中只有一个顶点，答案为 1 方案数为 1
        ll ways = 1;
        int ans = 0;
        if(m == 1){
            ans = 1;
            ways = 1;
        } else {
            // 检查是否存在割点
            bool anyCut = false;
            for (int i = 1; i <= m; i++){
                if(b[i]){
                    anyCut = true;
                    break;
                }
            }
            // 若无割点，则图为双联通，矿主只需设两个救援出口，方案数为全顶点两两组合数
            if(!anyCut){
                ans = 2;
                ways = (ll)m * (m - 1) / 2;
            } else {
                // 对每个 BCC，若其中恰好包含 1 个割点，则该 BCC在块树上为叶子，
                // 可在该 BCC中除割点之外的任一非割点处设置救援出口
                for(auto &comp : bcc){
                    int cutCount = 0;
                    for(auto x : comp){
                        if(b[x]) cutCount++;
                    }
                    if(cutCount == 1){
                        ans++;
                        // 非割点数 = (BCC 内顶点总数 - 1)
                        ways *= (comp.size() - 1);
                    }
                }
            }
        }
        cout << "Case " << caseNo++ << ": " << ans << " " << ways;
        if(!cin.eof()) cout << "\n";
    }
    return 0;
}
