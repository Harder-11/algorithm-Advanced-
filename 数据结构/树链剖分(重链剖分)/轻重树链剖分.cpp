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
轻重树链剖分:
前面已经知道了普通的树链剖分,既然普通树链剖分这么好写,为什么要用轻重树链剖分呢?
--对于一种叫做"毛毛虫树"的结构(类似与一条链的烷烃),这样通过普通链分解就极大概率分解到从头到尾的一条链
我们假设链最长长度是10,数据量是1e5,那么都有1e4条链,那么从头到尾跑都是1e4级别,会TLE

所以在链分解之前,首先要做一个预处理就是对于子树轻重的划分
首先利用树dp求出所有子树的size
定义重儿子是当前结点中所有子树size最大的子树
定义轻儿子是当前结点中所有子树size最小的子树
定理:轻儿子的size必定小于等于当前子树size的一半
定理扩展:树上每经过一条轻边之后,子树尺寸缩减一半

那么链分解后的结构树:
在对链分解之后,借助面向对象的思想,我们把一整个重链看成一个整体,作为一个大的结点看待,树上的轻链看出结构
树的一部分,这样的话,整棵树就被压缩了(有点像SCC缩点,就把整条链当做一个结点看),可以证明,被压缩后的树深度不超过log(N)

那么此时已经知道了最深不超过logN,那么求LCA就可以用以下的暴力算法:
int lca(int x,iny y){
	while(x != y){
		if(dep[x] < dep[y]) swap(x,y);
		x = fa[x]; 
	}
	return x;
}
在这段代码后,x和y都在一条链上了,然后此时的LCA(x,y) = min(dep[x],dep[y])
这个复杂度就是树深度,那么就可以使用树链剖分求LCA

所以说,树链剖分的本质是,对于结构树的压缩重构,使得新的结构数在上面暴力移动的时候复杂度不多于log(即在进行树链剖分之后重链形成的结构树
树的直径变为logN)
树链剖分本事不具备任何维护信息的功能,换句话说树链剖分本身不是数据结构,只是利用dfs的整理过程
*/

//fa[x]表示x的父节点,dep[x]表示结点x在书中的深度
//siz[x]表示节点x为根的子树的节点个数,son[x]表示结点x的重儿子
//top[x]表示结点x所在重链的顶部节点,dfn[x]表示节点x的dfn序,rnk[x]表示dfs序所对应的结点序号rnk[dfn[x]] = x
int dep[N],top[N],fa[N],siz[N],son[N],dfn[N],rnk[N],cnt;
//链式前向星建图
int h[N],nxt[N << 1],to[N << 1],tot;

void add(int u,int v){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	h[u] = cnt; 
}

//第一次dfs求出fa,dep,siz,son数组
void dfs1(int u,int f){
	dep[u] = dep[f] + 1;
	fa[u] = f;
	siz[u] = 1;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		dfs1(v,u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]){
			son[u] = v;
		}
	}
}

//第二次dfs求出top,dfn,rnk数组
void dfs2(int u,int tp){
	top[u] = tp;
	dfn[u] = ++cnt;
	rnk[cnt] = u;
	if(son[u] == -1) return;
	dfs2(son[u],tp);
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v,v);
	}
}


//树链剖分求LCA
int lca(int x,int y){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
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