#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2500005;
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
可持久化线段树
采用动态开点线段树,每次修改的时候动态开一条链(因为每次单点修改一定影响的是一条链)即可,每次开的空间就是logN级别,总空间和时间复杂度都是O(NlogN)
每次都要新开一个新的根节点,用root数组记录下来

特殊的,主席树的建立void build(int &u,int l,int r),这里传入的根节点是实参
递归里面调用的时候,每次都是传的lch[u]和rch[u],那么此时进入递归后,u = ++tot,那么此时就会给现在的lch[u]和rch[u]赋值
当然也可以不用实参,但是变成int build(int l,int r),在主函数里面lch和rch数组接收返回值代表编号
主席树大概开25 * N的大小即可
注意:主席树没有pushdown操作,这样在query里面ans加上lazy[u] * (r - l + 1)即可

主席树的 基础用处:区间K大值查询,每次给L,R,k,询问升序排序的第k个数字是多少
用cnt数组统计每个区间出现元素的个数
那么每次用第r版本 - 第l - 1版本即可得到[l,r]的区间元素出现的次数
那么查第K大,直接在线段树上面二分即可,如果左子树区间的cnt > k就往左子树递归,如果cnt < k往右子树递归,如果cnt == k,直接返回即可
*/
const int M = 100005;
int A[M];

struct SegTree {
	//动态开点,记录每个结点的左右儿子
	//tot用来计数
	int lch[N],rch[N],tot;
	//sum是区间和,lazy是区间的懒标记,由于是动态开点线段树,用编号来表示的线段树节点而不是直接创建数组,所以都是用的sum,lazy数组表示每个节点的信息
	int sum[N],lazy[N];
	void init(){
		tot = 0;
	}
	void cpy(int from,int to){
		lch[to] = lch[from];
		rch[to] = rch[from];
		sum[to] = sum[from];
		lazy[to] = lazy[from];
	}
	void build(int &u,int l,int r){
		u = ++tot;
		lazy[u] = 0;
		if(l == r){
			sum[l] = A[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(lch[u],l,mid);
		build(rch[u],mid + 1,r);
		sum[u] = sum[lch[u]] + sum[rch[u]];
 	}
	//主席树的修改,给[L,R] + val
	//修改操作依然是&u(实参),因为每次仍然需要新开结点,这样才能在递归的时候顺便把lch和rch给填上
	//l,r,v是要修改的[l,r]以及修改的大小val
	//old是原先版本的线段树,此时递归的时候参数old和&u是用一个东西
	//&u是为了为lch和rch数组赋值,而old参数是为了能够cpy
	void change(int &u,int old,int L,int R,int l,int r,ll val){
		u = ++tot;
		cpy(old,u);
		sum[u] += val * (r - l + 1);
		if(l == L && r == R){
			lazy[u] += v;
			return;
		}
		int mid = (L + R) >> 1;
		if(r <= mid) change(lch[u],lch[u],L,mid,l,r,v);
		else if(l >= mid + 1) change(rch[u],rch[u],mid + 1,R,l,r,v);
		else {
			change(lch[u],lch[u],L,mid,l,mid,v);
			change(rch[u],rch[u],mid + 1,R,mid + 1,r,v);
		}
	}
	//查询区间和
	int query(int u,int L,int R,int l,int r){
		if(l == L && r == R){
			return sum[u];
		}
		int ans = lazy[u] * (r - l + 1);
		int mid = (L + R) >> 1;
		if(r <= mid) return ans + query(lch[u],L,mid,l,r);
		else if(l >= mid + 1) return ans + query(rch[u],mid + 1,R,l,r);
		else {
			return ans + query(lch[u],L,mid,l,mid) + query(rch[u],mid + 1,R,mid + 1,r);
		}
	}
};

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