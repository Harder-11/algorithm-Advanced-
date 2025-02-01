#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200005;
const int mod = 1e9 + 7;
#define ls u << 1
#define rs u << 1 | 1

int n,m;

//注意这段代码被卡常了,但是无伤大雅

struct M {
	ll a[3][3];
	void clear(){
		memset(a,0,sizeof a);
	}
	void reset(){
		clear();
		a[1][1] = a[2][2] = 1;
	}

};

M operator * (const M &A,const M &B){
	M ans;
	ans.clear();
	for(int i = 1;i <= 2;i++){
		for(int k = 1;k <= 2;k++){
			for(int j = 1;j <= 2;j++){
				ans.a[i][j] = (ans.a[i][j] + A.a[i][k] * B.a[k][j] % mod) % mod;
			}
		}
	}
	return ans;
}
M operator + (const M &A,const M &B){
	M ans;
	ans.clear();
	for(int i = 1;i <= 2;i++){
		for(int j = 1;j <= 2;j++){
			ans.a[i][j] = (A.a[i][j] + B.a[i][j]) % mod;
		}
	}
	return ans;
}

M power(M t,ll k){
	M ans;
	ans.reset();
	while(k){
		if(k & 1) ans = ans * t;
		t = t * t;
		k >>= 1;
	}
	return ans;
}

M b;
ll a[N];

void init(){
	b.clear();
	b.a[1][1] = 1;
	b.a[1][2] = 1;
	b.a[2][1] = 1;
	b.a[2][2] = 0;
}

struct node {
	int l,r;
	ll lazy;
	M mat;
};

struct Segtree {
	node tr[N << 2];
	void pushup(int u){
		tr[u].mat = tr[ls].mat + tr[rs].mat;
	}
	void pushdown(int u){
		ll val = tr[u].lazy;
		if(val){
			tr[ls].lazy += val;
			tr[rs].lazy += val;
			tr[ls].mat = power(b,val) * tr[ls].mat;
			tr[rs].mat = power(b,val) * tr[rs].mat;
			tr[u].lazy = 0;
		}
	}
	void build(int u,int l,int r){
		tr[u].l = l;
		tr[u].r = r;
		tr[u].lazy = 0;
		if(l == r){
			tr[u].mat = power(b,a[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(ls,l,mid);
		build(rs,mid + 1,r);
		pushup(u);
	}
	void update(int u,int l,int r,int L,int R,ll val){
		if(L <= l && r <= R){
			tr[u].lazy += val;
			tr[u].mat = power(b,val) * tr[u].mat;
			return;
		}
		pushdown(u);
		int mid = (l + r) >> 1;
		if(L <= mid) update(ls,l,mid,L,R,val);
		if(R >= mid + 1) update(rs,mid + 1,r,L,R,val);
		pushup(u);
	}
	M query(int u,int l,int r,int L,int R){
		if(L <= l && r <= R){
			return tr[u].mat;
		}
		pushdown(u);
		int mid = (l + r) >> 1;
		M res;
		res.clear();
		if(L <= mid) res = res + query(ls,l,mid,L,R);
		if(R >= mid + 1) res = res + query(rs,mid + 1,r,L,R);
		return res;
	}
} seg;

void solve(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	init();
	seg.build(1,1,n);
	while(m--){
		int op;
		cin >> op;
		if(op == 1){
			int l,r;
			ll x;
			cin >> l >> r >> x;
			seg.update(1,1,n,l,r,x);
		} else {
			int l,r;
			cin >> l >> r;
			M ans = seg.query(1,1,n,l,r);
			cout << ans.a[1][2] % mod << '\n';
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