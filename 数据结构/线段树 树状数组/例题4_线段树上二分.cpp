#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 300005;
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
题目:
仓鼠家有n堆鸡蛋,每堆有ai个鸡蛋,仓鼠准备了n个篮子(按1,2,3...n编号),每个篮子最多放m个鸡蛋
仓鼠想要把鸡蛋全部放到篮子里面,但是不能把鸡蛋都放在一个篮子里面,所以它决定每个篮子不能放超过k堆鸡蛋
因为仓鼠很懒,所以它每次都会按照顺序拿起一堆鸡蛋,然后放在编号最小的,可行的篮子里面
现在它想知道,如果按照这样操作,每一堆鸡蛋会放在哪个篮子里面
第一行输入三个整数n,m,k(n <= 3e5,m <= 1e9,k <= 1e6),保证有Σn <= 1e6

思路:m特别大,那么显然会使用二分
我们使用线段树上二分,用线段树维护区间最大的值,当我们进行查询时候,如果该区间的max > a[i]
那么这段区间就肯定存在箱子 > a[i],然后看左子树能否放,左边能放就走左边,否则走右边
然后更新完之后就一路往回更新最大值(类似单点修改)
*/
struct tnode {
	int l,r;
	ll mx;
};

//用cnt记录每个篮子装了多少堆,必须严格 <= k,如果cnt[tr[u].l] == k,直接令为即可
int n,m,k,cnt[N],x;
struct SegTree {
	tnode tr[N << 2];
	void update(int u){
		tr[u].mx = max(tr[ls].mx,tr[rs].mx);
	}
	void build(int u,int l,int r){
		tr[u].l = l;
		tr[u].r = r;
		if(l == r){
			tr[u].mx = m;
			cnt[l] = 0;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls,l,mid);
		build(rs,mid + 1,r);
		update(u);
	}
	int f(int val){
		int u = 1;
		while(tr[u].l != tr[u].r){
			//左边的更大就往左边走,因为要找编号最小的
			if(tr[ls].mx >= val){
				u = ls;
			} else u = rs;
		}
		tr[u].mx -= val;
		cnt[tr[u].l]++;
		int ans = tr[u].l;
		if(cnt[tr[u].l] == k) tr[u].mx = 0;
		u >>= 1;
		while(u){
			update(u);
			u >>= 1;
		}
		return ans;
	}
};

SegTree ST;

void solve(){
	cin >> n >> m >> k;
	ST.build(1,1,n);
	for(int i = 1;i <= n;i++){
		cin >> x;
		if(x > m) cout << "-1\n";
		//本题不可能出现有x <= m并且是-1的情况,因为篮子数量和鸡蛋堆数是一样的
		else cout << ST.f(x) << '\n';
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