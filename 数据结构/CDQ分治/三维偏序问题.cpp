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
三维偏序问题:
有n个元素,第i个元素有ai,bi,ci三个属性,设f(i)满足aj <= ai && bj <= bi && cj <= ci且j != i的j的数量
对于d ∈ [0,n),求f(i) = d的i的数量

思路:题目要求统计序列里面点对的个数,那么可以尝试用CDQ分治
首先将序列按照a排序
假设我们现在写好了solve(l,r)并且通过递归搞定了solve(l,mid)和solve(mid+1,r)
现在我们要统计的是l<=i<=mid和mid+1<=j<=r的点对(i,j)中,有多少点对满足ai<aj,bi<bj,ci<cj
稍微思考一下就知道,ai<aj的限制已经没用了,因为已经按照a排序了,那么ai<aj可以转化为i<j
而归并的时候i<mid,j>mid,那么i一定是小于j,那么此时剩下两个条件bi<bj,ci<cj,根据这个限制条件,我们
就可以枚举,求出有多少个满足条件的i
为了方便枚举,我们把(l,mid)和(mid+1,r)中的点全部按照b的值从小到大排个序,之后我们依次枚举每一个j
把所有bi<bj的点i全部插入到某个数据结构中(我们选择树状数组),此时只需要查询树状数组中有多少个点的c值是小于cj的
我们就求出了对于这个点j,有多少个i可以合法匹配它了
当我们插入一个c值等于x的点的时候,我们就令树状数组的x这个位置单点+1,而查询树状数组里有多少个点小于x的操作实际上是在求前缀和
只要我们事先对所有的c实现离散化,我们的复杂度就是对的
对于每个j,我们都需要将所有bi<bj的点i插入树状数组中,由于所有的i和j都已经事先按照b值排序,这样的话只需要以双指针的方式
在树状数组里插入点,则对树状数组的插入操作从O(N^2)降为O(N)
总的时间复杂度O(N * (logN)^2)
*/

int n,k;
struct node {
	//cnt表示这一个node里面有多少个a,b,c都一样的元素
	int a,b,c;
	int cnt,res;
	//重载不等号,用于后面进行类似离散化操作
	bool operator != (node x) const {
		if(a != x.a) return 1;
		if(b != x.b) return 1;
		if(c != x.c) return 1;
		return 0;
	}
};

int lowbit(int x){
	return x & -x;
}

node e[N],ue[N];
int m,t,res[N];

struct Bit {
	int tr[N];
	void add(int x,int v){
		while(x <= k){
			tr[x] += v;
			x += lowbit(x);
		}
	}
	int query(int x){
		int res = 0;
		while(x){
			res += tr[x];
			x -= lowbit(x);
		}
		return res;
	}
} BIT;

bool cmpA(node x,node y){
	if(x.a != y.a) return x.a < y.a;
	if(x.b != y.b) return x.b < y.b;
	return x.c < y.c;
}

bool cmpB(node x,node y){
	if(x.b != y.b) return x.b < y.b;
	return x.c < y.c; 
}

void CDQ(int l,int r){
	if(l == r) return;
	int mid = (l + r) >> 1;
	CDQ(l,mid);
	CDQ(mid + 1,r);
	sort(ue + l,ue + mid + 1,cmpB);
	sort(ue + mid + 1,ue + r + 1,cmpB);
	int i = l,j = mid + 1;
	//注意这里的条件只是j <= r即可,因为有可能i是没有到达mid的,有可能靠近mid的ue[i].b > ue[j].b
	//这样的i不会参与统计答案,也就不需要对i进行要求
	while(j <= r){
		while(i <= mid && ue[i].b <= ue[j].b){
			BIT.add(ue[i].c,ue[i].cnt);
			i++;
		}
		ue[j].res += BIT.query(ue[j].c);
		j++;
	}
	//每次把BIT清空,每次add一个-ue[k].cnt即可抵消
	for(int k = l;k < i;k++) BIT.add(ue[k].c,-ue[k].cnt);
}

void solve(){
	cin >> n >> k;
	for(int i = 1;i <= n;i++) cin >> e[i].a >> e[i].b >> e[i].c;
	sort(e + 1,e + n + 1,cmpA);
	//这个for循环用来将完全一样的node存放在一个ue里面,用cnt来计数,其中包含几个元素
	for(int i = 1;i <= n;i++){
		t++;
		if(e[i] != e[i + 1]){
			m++;
			ue[m].a = e[i].a;
			ue[m].b = e[i].b;
			ue[m].c = e[i].c;
			ue[m].cnt = t;
			t = 0;
		}
	}
	CDQ(1,m);
	//本题是要求的从d = 0开始一直到n - 1的f(i) = d的数量,所以d = res + cnt - 1(因为包含等于号,所以要加上cnt表示和本身相同的元素
	//但是-1是代表减去自己,因为要求i != j)
	//然后每个i都加上ue[i].cnt,表示这个node包含的相同的元素个数
	for(int i = 1;i <= m;i++){
		res[ue[i].res + ue[i].cnt - 1] += ue[i].cnt;
	}
	for(int i = 0;i < n;i++) cout << res[i] << '\n';
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