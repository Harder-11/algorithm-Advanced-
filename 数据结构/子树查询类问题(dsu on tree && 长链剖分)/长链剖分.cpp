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
长链剖分:
首先,长链剖分是dsu on tree的一种特殊情况,就是说现在不查整个子树
而是给定一个深度deep,你需要合并子树deep相同的信息
静态查询子树和深度有关的信息,它一定是"静态子树类查询问题的子集"
那么为什么要用长链剖分呢?
--他的复杂度很优秀,它的基础复杂度是O(N),不带log,这样的话长链剖分再套个线段树
就能比dsu on tree在相同复杂度上做到更多功能

一般将的长链剖分指的是dsu on tree的第一步(树链剖分预处理)这部分用长链剖分代替轻重链剖分
所以只要会dsu on tree就会长链剖分

与重链剖分不同的是,长链剖分中,L[x],R[x]表示的覆盖作用域变了,此时不同链之间的
的作用域是没有任何交集的,也就是说数据结构仅被同一重链的结点所共用
并且不共用数据结构了,那么我们先处理轻儿子或者重儿子都一样的,就可以把顺序任意调换
那么就是以下步骤:
dsu(x){
	1.处理重儿子
	2.处理轻儿子同时把轻儿子的信息往重儿子上边并
	3.计算答案
}

例题:给一棵以1为根,大小为n的有根树,每个点有点权,查询若干次,每次查询以x为根的子树
深度为y的这一层中,所有点权的和(此时把节点x的深度看做0)
*/

int h[N],to[N << 1],nxt[N << 1],cnt;
//son仍然是记录的重儿子,只不过这里指的是长链剖分的重儿子
int fa[N],len[N],son[N],L[N],R[N],dfn;
int n,m,x,y,u,v;
ll val[N],ans[N],sum[N];
vector<pair<int,int>> lis[N];

void add(int u,int v){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	h[u] = cnt;
}

//树剖剖分部分,dfs1填写fa,len,son数组
void dfs1(int u,int f){
	fa[u] = f;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == u) continue;
		dfs1(v,u);
		if(!son[u] || len[son[u]] < len[v]){
			son[u] = v;
		}
	}
	len[u] = len[son[u]] + 1;
}

//dfs2填写L和R数组
//这里的L和R表示的是x节点的下属长链中dfn的最小值和最大值
void dfs2(int u){
	L[u] = ++dfn;
	R[u] = L[u] + len[u] - 1;
	if(son[u]) dfs2(son[u]);
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v != fa[u] && v != son[u]){
			dfs2(v);
		}
	}
}

void dsu(int u){
	if(son[u]){
		dsu(son[x]);
	}
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v != fa[u] && v != son[u]){
			dsu(v);
			for(int j = L[v],k = 1;j <= R[v];j++,k++){
				sum[L[u] + k] += sum[j];
			}
		}
	}
	sum[L[u]] += val[u];
	for(auto x : lis[u]){
		ans[x.first] = sum[L[u] + x.second];
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