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
有一颗节点为N的树,以1为根,且树有点权
然后有M个操作,分为3种
操作1:把某个结点x的点权增加a
操作2:把某个结点x为根的子树中所有点的点权增加a
操作3:询问某个节点x到根的路径中所有点的权值和


思路:最基础的树剖 + 线段树的题
注意:不开long long见祖宗
*/
ll n,m,tot,cnt;
ll dep[N],top[N],siz[N],son[N],id[N],fa[N];
ll sum[N],num[N];
ll h[N],nxt[N << 1],to[N << 1];
struct Segtree {
	ll l,r;
	ll sum,lazy;
} tr[N << 2];

void add(ll u,ll v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

void dfs1(ll u,ll f){
	dep[u] = dep[f] + 1;
	fa[u] = f;
	siz[u] = 1;
	for(ll i = h[u];i;i = nxt[i]){
		ll v = to[i];
		if(v == f) continue;
		dfs1(v,u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]){
			son[u] = v;
		}
	}
}

void dfs2(ll u,ll tp){
	id[u] = ++cnt;
	num[cnt] = u;
	top[u] = tp;
	if(son[u]) dfs2(son[u],tp);
	for(ll i = h[u];i;i = nxt[i]){
		ll v = to[i];
		if(v == son[u] || v == fa[u]) continue;
		dfs2(v,v);
	}
}

void update(ll u){
	tr[u].sum = tr[ls].sum + tr[rs].sum;
}

void build(ll u,ll l,ll r){
	tr[u].l = l;
	tr[u].r = r;
	tr[u].lazy = tr[u].sum = 0;
	if(l == r){
		tr[u].sum = sum[num[l]];
		return;
	}
	ll mid = (l + r) >> 1;
	build(ls,l,mid);
	build(rs,mid + 1,r);
	update(u);
}

void pushdown(ll u){
	if(tr[u].lazy){
		ll k = tr[u].lazy;
		tr[ls].lazy += k;
		tr[rs].lazy += k;
		tr[ls].sum += (tr[ls].r - tr[ls].l + 1) * k;
		tr[rs].sum += (tr[rs].r - tr[rs].l + 1) * k;
		tr[u].lazy = 0;
	}
}

void modify(ll u,ll l,ll r,ll v){
	if(tr[u].l >= l && tr[u].r <= r){
		tr[u].lazy += v;
		tr[u].sum += (tr[u].r - tr[u].l + 1) * v;
		return;
	}
	pushdown(u);
	ll mid = (tr[u].l + tr[u].r) >> 1;
	if(l <= mid) modify(ls,l,r,v);
	if(r >= mid + 1) modify(rs,l,r,v);
	update(u);
}

ll query(ll u,ll l,ll r){
	if(tr[u].l >= l && tr[u].r <= r){
		return tr[u].sum;
	}
	pushdown(u);
	ll res = 0;
	ll mid = (tr[u].l + tr[u].r) >> 1;
	if(l <= mid) res += query(ls,l,r);
	if(r >= mid + 1) res += query(rs,l,r);
	return res;
}

ll ask(ll u,ll v){
	ll res = 0;
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]){
			swap(u,v);
		}
		res += query(1,id[top[u]],id[u]);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u,v);
	res += query(1,id[u],id[v]);
	return res;
}

void solve(){
	cin >> n >> m;
	for(ll i = 1;i <= n;i++) cin >> sum[i];
	for(ll i = 1,u,v;i < n;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,cnt);
	while(m--){
		ll op,x,a;
		cin >> op;
		if(op == 1){
			cin >> x >> a;
			modify(1,id[x],id[x],a);
		} else if(op == 2){
			cin >> x >> a;
			modify(1,id[x],id[x] + siz[x] - 1,a);
		} else {
			cin >> x;
			cout << ask(1,x) << '\n';
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