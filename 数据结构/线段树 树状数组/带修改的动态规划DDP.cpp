#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1ll << 61;
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
有两个层数为N的塔,两座塔的内部有格子有连接到上一层的楼梯(和前缀和那道题的题干基本一样)
但是本题假设第i层塔左侧楼梯,第i层塔右侧楼梯,第i层两座塔之间的楼梯,其高度分别为val(i0),val(i1),val(i2)
楼梯的高度在这个问题中可能随时被更改,同时,塔的结构也可能改变,也就是说,除了顶楼以外,每一层都可能从第一组情况
变成第二种(也就是楼梯方向变化),现在想知道从某座高塔的第hs层到ht层,只能上楼的情况下有多少种情况?
当不存在道路的时候,输出-1表示无解

我们定义一个矩阵,行代表起点,列代表终点,那么就可以看做一个邻接矩阵,那么就是DAG
这个矩阵的平方就是代表的从某个点开始走两步到底另一个点的方案数(离散知识)

*/
ll val[N][3];
char s[N];
struct Mat {
	ll a[2][2];
	Mat(){
		for(int i = 0;i < 2;i++){
			for(int j = 0;j < 2;j++){
				a[i][j] = INF;
			}
		}
		for(int i = 0;i < 2;i++){
			a[i][i] = 0;
		}
	}
	Mat(ll a1,ll a2,ll a3,ll a4){
		a[0][0] = a1;
		a[0][1] = a2;
		a[1][0] = a3;
		a[1][1] = a4;
	}
};

Mat operator * (Mat x,Mat y){
	Mat c;
	for(int i = 0;i < 2;i++){
		for(int j = 0;j < 2;j++){
			c.a[i][j] = INF;
		}
	}
	//类似于Floyd算法,每次求min
	for(int i = 0;i < 2;i++){
		for(int j = 0;j < 2;j++){
			for(int k = 0;k < 2;k++){
				c.a[i][j] = min(c.a[i][j],x.a[i][k] + y.a[k][j]);
			}
		}
	}
	return c;
}

Mat make_dp(int x){
	if(s[x] == '/'){
		return Mat(val[x][0],val[x][2],INF,val[x][1]);
	} else {
		return Mat(val[x][0],INF,val[x][2],val[x][1]);
	}
}

struct tnode {
	Mat mat;
	int l,r;
};

struct SegTree {
	tnode tr[N << 2];
	//为了方便,pos用来记录叶节点,方便进行change操作,一个while就行
	int pos[N];
	void update(int u){
		tr[u].mat = tr[ls].mat * tr[rs].mat; 
	}
	void build(int u,int l,int r){
		tr[u].l = l;
		tr[u].r = r;
		if(l == r){
			tr[u].mat = make_dp(l);
			pos[l] = u;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls,l,mid);
		build(rs,mid + 1,r);
		update(u);
	}
	void change(int x){
		int u = pos[x];
		tr[u].mat = make_dp(x);
		while(u >>= 1) update(u);
	}
	Mat query(int u,int l,int r){
		if(tr[u].l == l && tr[u].r == r){
			return tr[u].mat;
		}
		int mid = (tr[u].l + tr[u].r) >> 1;
		if(r <= mid) return query(ls,l,r);
		else if(l >= mid + 1) return query(rs,l,r);
		else {
			return query(ls,l,mid) * query(rs,mid + 1,r);
		}
	}
};

SegTree ST;
int n,m,hs,ht,ps,pt,op,x;
char c[5];

void solve(){
	scanf("%d%d%s",&n,&m,(s + 1));
	for(int i = 1;i < n;i++){
		scanf("%lld%lld%lld",&val[i][0],&val[i][1],&val[i][2]);
	}
	ST.build(1,1,n - 1);
	while(m--){
		scanf("%d",&op);
		if(op == 2){
			scanf("%d%d%d%d",&hs,&ht,&ps,&pt);
			ll ans = ST.query(1,hs,ht - 1).a[ps][pt];
			if(ans == INF) ans = -1;
			printf("%lld\n",ans);
		} else {
			//修改操作
			if(op == 0){
				scanf("%d%s",&x,c);
				s[x] = *c;
			} else {
				scanf("%d",&x);
				scanf("%lld%lld%lld",&val[x][0],&val[x][1],&val[x][2]);
			}
			ST.change(x);
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