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
在有向图G = <V,E>中,如果对于任意两点u,v,存在一条从u到v或者从v到u的路径---那么就是弱连通
在有向图G = <V,E>中,如果对于任意两点u,v都互相可达---强联通

1.有向图的强联通分量:在有向图G中,如果两个顶点vi,vj之间(vi > vj)有一条从vi到vj的有向路径
同时还有一条从vj到vi的有向路径,则称两个顶点强联通
2.如果有向图G的每两个顶点都强联通,那么G是一个强联通图
3.有向图的极大强联通子图,成为强联通分量

Kosaraju算法:
1.对原图进行一次dfs(任意起点)
2.在第一次dfs形成的森林的每一棵树里面,以第一次搜索出栈时间的逆序对反图进行dfs
这次搜索A能到达的点和A都在一个强联通分量里面

tarjan算法:
1.dfn[n]时间戳
2.low[n]:它和它子树里返祖边和横插边能连接到还没出栈的dfn最小的点
3.在dfs的时候维护一个栈,第一次访问某个点就把这个点加入到栈里面
当一个点x的dfn[x] = low[x]的时候,他就是这个强联通分量里面在搜索树中最高的点
将栈里面的点出栈直到x也出栈为止,这些点组成一个强联通分量
*/


//tarjan求强联通分量的代码
int stk[N],dfn[N],low[N],cnt;
int h[N],nxt[N],to[N],tot,top;
//vis是指的还在不在栈中而不是访问标记
//num用来记录每个点在哪个强联通分量里面
//siz是强联通分量的大小
int ans,vis[N],num[N],siz[N];

void add(int u,int v){
    nxt[++tot] = h[u];
    to[tot] = v;
    h[u] = tot;
}

void tarjan(int u){
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    vis[u] = 1;
    for(int i = h[u];i;i = nxt[i]){
        int v = to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u],low[v]);
        } else if(vis[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(dfn[u] == low[u]){
        ans++;
        do {
            num[stk[top]] = ans;
            siz[ans]++;
            vis[stk[top]] = 0;
        } while(stk[top--] != u);
    }
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