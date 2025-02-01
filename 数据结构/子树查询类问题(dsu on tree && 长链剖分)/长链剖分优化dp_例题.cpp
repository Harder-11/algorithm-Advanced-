#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
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
题目大意:给定一棵以1为根,n个结点的树
设d(u,x)为u子树到u距离为x的结点数,对于每个点,求一个最小的k,使得d(u,k)最大

思路:非常常规的dp,设f(i,j)表示点i的j级子节点的数量,转移方程很显然
f(i,j) = Σf(v,j - 1),其中v是i的子节点
我们可以采用一个策略:对于一个节点u,我们先对它的重儿子做dp,这里可以使用一些技巧
让重儿子把dp出来的东西直接存到fu里面去(当然观察dp式可以发现这边需要错一位),然后再把其他儿子dp出来的东西与fu暴力合并
这里详细说一说如何实现这个优化
首先我们抛弃传统的dp预先为每个结点申请一片空间的写法,而是在dp的过程中,动态为节点申请内存,所以这里要采用指针的写法
然后我们只对每一个长链的顶端节点申请内存,而对于一条长链上的所有节点,我们让他们可以公用一片空间;
具体来说就是加上对节点u申请了内存之后,设v是u的重儿子,我们就把fu数组的起点(的指针)加一当做fv数组的起点(的指针),以此类推
这也就是上面说的"让重儿子把dp出来的东西直接存到fu里面去"
当然在dp开始前要为以树根为顶端的长链申请内存,而且光有dp数组也没有用,我们还要统计答案
我们可以先令u节点的答案为它的重儿子+1,然后在暴力合并的过程当中每次检测当前的dep是否由于ansu(ansu就是题目要求的东西)
最后如果发现f(u,ansu) = 1,即u的子树是一条链,无论在哪个深度下都只有一个点的时候,那么就把当前结点答案的ansu置为0

*/

int n;
int h[N],to[N << 1],nxt[N << 1],tot;
//buf数组单纯用来给fa数组分配内存用的,一开始now就指向buf
int buf[N],*fa[N],*g[N],*now = buf;
int ans[N],dep[N],son[N];

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

void dfs1(int u,int f){
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		dfs1(v,u);
		if(dep[v] > dep[son[u]]) son[u] = v;
	}
	dep[u] = dep[son[u]] + 1;
}

void dfs2(int u,int f){
	fa[u][0] = 1;
	if(son[u]){
		//共享内存,这样可以节约内存空间
		//目的是让 重儿子 son[u] 的 DP 数据直接在父节点 u 的 DP 数组之后存储。
		//这种设计利用了重儿子计算完后，深度信息直接可以在父节点的数组中复用，避免额外分配内存。
		//注意,这里必须是+1,因为DP转移公式fa[u][i]+=fa[v][i - 1]中
		//fa[u][i]必须直接从fa[son[u]][i-1]继承,二者的空间必须是相差1的
		fa[son[u]] = fa[u] + 1;
		dfs2(son[u],u);
		//从重儿子结点继承答案
		ans[u] = ans[son[u]] + 1;
		for(int i = h[u];i;i = nxt[i]){
			int v = to[i];
			if(v == son[u] || v == f) continue;
			//分配内存
			fa[v] = now;
			//这里now加多少是有讲究的,虽然是让now跳到一个空的buf里面去
			//但是如果+1的话,就会导致fa[v]赋值给之前+1,就可能发生内存冲突
			//(因为之前fa[son[u]]和fa[u]+1共用内存)
			now += dep[v];
			dfs2(v,u);
			for(int i = 1;i <= dep[v];i++){
				fa[u][i] += fa[v][i - 1];
				//两种情况,fa[u][i] > fa[u][ans[u]]肯定会改变ans[u]的值
				//或者二者相等并且i < ans[u],取dep更小的i
				if(fa[u][i] > fa[u][ans[u]] || (fa[u][i] == fa[u][ans[u]] && i < ans[u])){
					ans[u] = i;
				}
			}
		}
	}
	//最后千万不要忘记特判,如果最后求到此时u节点的答案是1,那么就把ans[u] = 0
	//因为就算距离为0(就是u本身),此时一层的结点数也是1
	if(fa[u][ans[u]] == 1) ans[u] = 0;
}

void solve(){
	cin >> n;
	for(int i = 1,u,v;i < n;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	fa[1] = now;
	now += dep[1];
	dfs2(1,0);
	for(int i = 1;i <= n;i++) cout << ans[i] << '\n';
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