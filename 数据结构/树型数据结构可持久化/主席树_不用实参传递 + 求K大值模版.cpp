#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 3000005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1e9 + 9;
const int hs2 = 998244353;
const int base = 233;
const double PI = acos(-1);
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

int tot,n,m;
//rt[i]:用来存储每个版本线段树的根节点编号
int sum[N],rt[N],ls[N],rs[N];
int a[N],ind[N],len;
int l,r,k;

//离散化
int getid(const int &val){
	return lower_bound(ind + 1,ind + len + 1,val) - ind;
}

int build(int l,int r){
	int u = ++tot;
	if(l == r) return u;
	int mid = (l + r) >> 1;
	ls[u] = build(l,mid);
	rs[u] = build(mid + 1,r);
	return u;
}

//插入操作
int update(int u,int l,int r,int k){
	int dir = ++tot;
	//每次插入新节点就copy一份原来的ls和rs 
	ls[dir] = ls[u];
	rs[dir] = rs[u];
	sum[dir] = sum[u] + 1;
	if(l == r) return dir;
	int mid = (l + r) >> 1;
	if(k <= mid) ls[dir] = update(ls[dir],l,mid,k);
	else rs[dir] = update(k,mid + 1,r,rs[dir]);
	return dir;
}	

//查询第K大元素
int query(int u,int v,int l,int r,int k){
	int mid = (l + r) >> 1;
	//通过区间减法(类似于前缀和)求到左儿子存储的数值个数
	int x = sum[ls[v]] - sum[ls[u]];
	if(l == r) return l;
	if(k <= x) return query(ls[u],ls[v],l,mid,k);
	else return query(rs[u],rs[v],mid + 1,r,k - x);
}

void solve(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++) cin >> a[i];
	memcpy(ind,a,sizeof ind);
	sort(ind + 1,ind + n + 1);
	len = unique(ind + 1,ind + n + 1) - ind - 1;
	//初始化线段树,把初始化的根节点存在rt[0]里面
	rt[0] = build(1,len);
	for(int i = 1;i <= n;i++) rt[i] = update(rt[i - 1],1,len,getid(a[i]));
	while(m--){
		cin >> l >> r >> k;
		cout << ind[query(rt[l - 1],rt[r],1,len,k)] << '\n';
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