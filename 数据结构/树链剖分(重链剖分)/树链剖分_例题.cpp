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
你决定设计自己的软件包管理器,不可避免的,你需要解决软件包的依赖问题,如果软件包a依赖于b
那么安装a之前就必须安装b,同时,如果想卸载软件包b,就必须先卸载软件包a
现在你已经获得了所有的软件包的依赖关系,而且由于你之前的工作,除了0号软件包以外,在你的管理器当中的
软件包都会依赖一个且仅一个软件包,而0号软件包不依赖任何一个软件包,且依赖关系部存在环
现在你要为你的软件包管理器写一个依赖程序,根据反馈,用户希望在安装或者卸载某个软件包的时候
快速地知道这个操作实际会改变多少个软件包的安装状态,你的任务是实现这个部分
注意:安装一个已安装的软件包,或者卸载一个未安装的软件包,都不会改变任何软件包的安装状态
即在此情况下,改变安装状态的软件包数量为0
输入:第一行一个正整数n,表示软件包的个数,从0开始编号
第二行有n-1个整数,第i个表示i号软件依赖的软件包编号
然后一行一个正整数q表示操作次数,格式如下:
- install x表示安装x号软件包
- uninstall x表示卸载x号软件包
一开始所有的软件包都未安装,对于每个操作都要输出这步操作会改变多少软件包的安装状态,然后应用这个操作

思路:首先进行树链剖分,实现dfs序,dfn一定是跟着重链一路走的,在dfs序的基础上通过dfs填写出id(L),R,index数组
那么此时对于一棵树及其子树在index里面一定是连续的,所以用线段树去维护id数组
(树上的一条链上的id是连续了,所以可以通过维护id数组相当于维护树上的链)
*/

//用线段树维护id数组
struct Segtree{
	int l,r,sum,lazy;
} tr[N << 2];
//链式前向星建图
int h[N],to[N << 1],nxt[N << 1],tot,cnt,n,m;
//树链剖分以及dfs序的所需数组
int son[N],dep[N],siz[N],top[N],fa[N],id[N];

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

void dfs1(int u,int f){
	dep[u] = dep[f] + 1;
	siz[u] = 1;
	fa[u] = f;
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

void dfs2(int u,int tp){
	top[u] = tp;
	id[u] = ++cnt;
	if(son[u]) dfs2(son[u],tp);
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v,v);
	}
}

void pushdown(int u){
	int k = tr[u].lazy;
	tr[ls].sum = (tr[ls].r - tr[ls].l + 1) * k;
	tr[rs].sum = (tr[rs].r - tr[rs].l + 1) * k;
	tr[ls].lazy = tr[rs].lazy = k;
	tr[u].lazy = -1;
}

void build(int u,int l,int r){
	tr[u].l = l;
	tr[u].r = r;
	tr[u].sum = 0;
	tr[u].lazy = -1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls,l,mid);
	build(rs,mid + 1,r);
}

int query(int u,int l,int r){
	if(tr[u].l >= l && tr[u].r <= r){
		return tr[u].sum;
	}
	int res = 0;
	int mid = (tr[u].l + tr[u].r) >> 1;
	if(tr[u].lazy != -1) pushdown(u);
	if(l <= mid) res += query(ls,l,r);
	if(r >= mid + 1) res += query(rs,l,r);
	return res;
}

void update(int u,int l,int r,int v){
	if(tr[u].l >= l && tr[u].r <= r){
		tr[u].sum = (tr[u].r - tr[u].l + 1) * v;
		tr[u].lazy = v;
		return;
	}
	int mid = (tr[u].l + tr[u].r) >> 1;
	if(tr[u].lazy != -1) pushdown(u);
	if(l <= mid) update(ls,l,r,v);
	if(r >= mid + 1) update(rs,l,r,v);
	tr[u].sum = tr[ls].sum + tr[rs].sum;
}

//注意,每条链上的dfs序是连续的,那么就可以按照以下的change函数的代码实现update
void change(int u,int v,int val){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]) swap(u,v);
		//上面交换的意义就体现出来了,就是从id[top[u]]到id[u]这条链上
		//并且要每次处理更深的那条链,这样u,v依次往上爬的时候就不会出问题
		update(1,id[top[u]],id[u],val);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u,v);
	update(1,id[u],id[v],val);
}

void solve(){
	cin >> n;
	for(int i = 2,x;i <= n;i++){
		cin >> x;
		x++;
		add(x,i);
		add(i,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	cin >> m;
	build(1,1,cnt);
	for(int i = 1,x;i <= m;i++){
		string op;
		cin >> op >> x;
		x++;
		int t = tr[1].sum;
		if(op == "install"){
			change(1,x,1);
			cout << abs(t - tr[1].sum) << '\n';
		} else {
			//这里把id[x],id[x] + siz[x] - 1就是把x及其子树的所有的节点lazy变成0
			update(1,id[x],id[x] + siz[x] - 1,0);
			cout << abs(t - tr[1].sum) << '\n';
		}

	}
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