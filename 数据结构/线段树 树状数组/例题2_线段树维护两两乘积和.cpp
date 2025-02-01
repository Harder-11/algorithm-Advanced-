#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
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
给一串数字a1,a2...an需要进行以下m次操作
1 l r v,区间a[l]到a[r]的所有数字全部 +v
2 l r v,区间a[l]到a[r]的所有数字全部 *v
3 l r,求区间a[l]到a[r]之间两两之间数字的乘积和
比如2,3,4,5的乘积和就是2*3+2*4+2*5+3*4+3*5+4*5
第一行给出三个值n,m,p,表示有n个数字,m次操作,对p取模

思路:本题维护的是Σ(i,r)Σ(j = i + 1,r)xi * xj
那么对于区间两两乘积求和就是ΣΣ(axi + b)(axj + b)
= a^2 * ΣΣ(xi * xj) + ab * (r - l + 1) * Σxi + n * (n - 1) / 2 * b^2
*/

ll A[N],mod;

struct tnode {
	//这里由上面推导的式子看出不仅需要维护两两乘积和,还需要维护区间累加和
	//其中sum[0]是维护的区间和,sum[1]是两两乘积和
	//lazy[0]是a,lazy[1]是b
	ll sum[2],lazy[2];
	int l,r;
};

tnode operator + (const tnode &a,const tnode &b){
	tnode c;
	c.l = a.l;
	c.r = b.r;
	c.lazy[0] = 1;
	c.lazy[1] = 0;
	c.sum[0] = (a.sum[0] + b.sum[0]) % mod;
	c.sum[1] = (a.sum[1] + b.sum[1]) % mod;
	c.sum[1] = (c.sum[1] + a.sum[0] * b.sum[0] % mod) % mod;
	return c;
}

struct SegTree {
	tnode tr[N << 2];
	void init_lazy(int u){
		tr[u].lazy[0] = 1;
		tr[u].lazy[1] = 0;
	}
	void union_lazy(int fa,int ch){
		ll tmp[2];
		tmp[0] = tr[fa].lazy[0] * tr[ch].lazy[0] % mod;
		tmp[1] = ((tr[fa].lazy[0] * tr[ch].lazy[1] % mod) + tr[fa].lazy[1]) % mod;
		tr[ch].lazy[0] = tmp[0];
		tr[ch].lazy[1] = tmp[1];
	}
	void cal_lazy(int u){
		ll len = (tr[u].r - tr[u].l + 1) % mod;
		tr[u].sum[1] = (len * (len - 1) / 2 % mod * tr[u].lazy[1] % mod * tr[u].lazy[1] % mod + 
		tr[u].lazy[0] * tr[u].lazy[0] % mod * tr[u].sum[1] % mod + 
		tr[u].lazy[0] * tr[u].lazy[1] % mod * (len - 1) % mod * tr[u].sum[0] % mod) % mod;
		tr[u].sum[0] = (len * tr[u].lazy[1] % mod + tr[u].lazy[0] * tr[u].sum[0] % mod) % mod;
	}
	void pushdown(int u){
		if(tr[u].lazy[0] != 1 || tr[u].lazy[1] != 0){
			cal_lazy(u);
			if(tr[u].l != tr[u].r){
				union_lazy(u,ls);
				union_lazy(u,rs);
			}
			init_lazy(u);
		}
	}
	void update(int u){
		pushdown(ls);
		pushdown(rs);
		tr[u] = tr[ls] + tr[rs];
	}
	void build(int u,int l,int r){
		tr[u].l = l;
		tr[u].r = r;
		init_lazy(u);
		if(l == r){
			tr[u].sum[0] = A[l] % mod;
			tr[u].sum[1] = 0;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls,l,mid);
		build(rs,mid + 1,r);
		update(u);
	}
	void change(int u,int l,int r,ll val,int op){
		pushdown(u);
		if(tr[u].l == l && tr[u].r == r){
			tr[u].lazy[op] = val % mod;
			return;
		}
		int mid = (tr[u].l + tr[u].r) >> 1;
		if(r <= mid) change(ls,l,r,val,op);
		else if(l >= mid + 1) change(rs,l,r,val,op);
		else {
			change(ls,l,mid,val,op);
			change(rs,mid + 1,r,val,op);
		}
		update(u);
	}
	tnode sum(int u,int l,int r){
		pushdown(u);
		if(tr[u].l == l && tr[u].r == r){
			return tr[u];
		}
		int mid = (tr[u].l + tr[u].r) >> 1;
		if(r <= mid) return sum(ls,l,r);
		else if(l >= mid + 1) return sum(rs,l,r);
		else {
			return sum(ls,l,mid) + sum(rs,mid + 1,r);
		}
	}
};

SegTree ST;
int n,m,op,l,r;
ll x;

void solve(){
	cin >> n >> m >> mod;
	for(int i = 1;i <= n;i++) cin >> A[i];
	ST.build(1,1,n);
	for(int i = 1;i <= m;i++){
		cin >> op >> l >> r;
		if(op <= 2){
			cin >> x;
			ST.change(1,l,r,x,2 - op);
		} else {
			cout << ST.sum(1,l,r).sum[1] << '\n';
		}
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}