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
例如给定一个序列,每个元素有两个属性a,b,我们希望计算一个dp式子的值,它的转移方程如下:
dp[i] = 1 + max(j = 1,i - 1)dp[j][aj < ai][bj < bi](本质就是一个二维的最长上升子序列)
即只有j < i,aj < ai,bj < bi的点j可以更新点i的dp值,转移显然是O(N^2)的
但是我们发现dpj转移到dpi这种转移关系也是一种点对间的关系,所以我们利用类似CDQ分治处理点对关系的方式来处理
这个转移过程很套路,加上正在处理的区间为(l,r),算法流程如下:
1.如果l = r,说明dpr的值已经计算好了,直接令dpr++然后返回即可
2.递归使用solve(l,mid)
3.处理所有l <= j <= mid,mid + 1 <= i <= r的转移关系
4.递归使用solve(mid + 1,r)
其中第三步的做法和求三维偏序差不多,处理l <= j <= mid,mid + 1 <= i <= r的转移关系的时候
我们会发现已经不用管j < i这个限制条件了,因此我们依然先将所有的点i和点j按a值进行排序处理
然后用双指针的方式将j点插入到树状数组里面,最后查一下前缀最大值更新一下dpi即可

注意:dp的转移一定是有序的,必须满足两个条件:
1.用来计算的dp[i]的所有dp[j]的值必须是已经计算完毕的,不能存在"半成品"
2.用来计算dp[i]的所有dp[j]的值都必须能更新到dp[i],不能存在没有更新到的dp[j]的值
那么我们用来看中序遍历:
1.第一个结束的函数是solve(1,1),此时dp1的值已经计算完毕了
2.第二个结束的函数是solve(1,2),此时dp2的值转移好了
3.第三个结束的函数是solve(2,2),此时dp2的值被计算完毕
........
如果我们依然利用后续遍历来更新dp值,就会出现违反第一条定律的式子
(因为中序遍历在整个树上,整体看起来就是从左到右依次转移的,而后续遍历会有回退现象,比如先solve(2,2)再solve(1,2))

题目:
某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度、并且能够拦截任意速度的导弹，
但是以后每一发炮弹都不能高于前一发的高度，其拦截的导弹的飞行速度也不能大于前一发。某天，雷达捕捉到敌国的导弹来袭。
由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。
在不能拦截所有的导弹的情况下，我们当然要选择使国家损失最小、也就是拦截导弹的数量最多的方案。
但是拦截导弹数量的最多的方案有可能有多个，如果有多个最优方案，那么我们会随机选取一个作为最终的拦截导弹行动蓝图。
我方间谍已经获取了所有敌军导弹的高度和速度，你的任务是计算出在执行上述决策时，每枚导弹被拦截掉的概率。

思路:一道二维最长上升子序列的题
为了确定一个元素是否在最长上升子序列里面,可以正反跑两边CDQ分治
*/

struct node {
	int h,v,p,ma;
	double ca;
} a[2][N];

int n;
bool tr;

bool cmp1(const node &a,const node &b){
	if(tr){
		return a.h > b.h;
	} else {
		return a.h < b.h;
	}
}

bool cmp2(const node &a,const node &b){
	if(tr){
		return a.v > b.v;
	} else {
		return a.v < b.v;
	}
}

bool cmp3(const node &a,const node &b){
	if(tr){
		return a.p < b.p;
	} else {
		return a.p > b.p;
	}
}

bool cmp4(const node &a,const node &b){
	return a.v == b.v;
}

int lowbit(int x){
	return x & -x;
}

struct treearray {
	int ma[N << 1];
	double ca[N << 1];
	void c(int x,int t,double c){
		while(x <= n){
			if(ma[x] == t){
				ca[x] += c;
			} else if(ma[x] < t){
				ca[x] = c;
				ma[x] = t;
			}
			x += lowbit(x);
		}
	}
	void d(int x){
		while(x <= n){
			ma[x] = 0;
			ca[x] = 0;
			x += lowbit(x);
		}
	}
	void q(int x,int &m,double &c){
		while(x){
			if(ma[x] == m){
				c += ca[x];
			} else if(m < ma[x]){
				c = ca[x];
				m = ma[x];
			}
			x -= lowbit(x);
		}

	}
} ta;

int rk[2][N];

void CDQ(int l,int r,int t){
	if(r - l <= 1) return;
	int mid = (l + r) >> 1;
	CDQ(l,mid,t);
	sort(a[t] + mid + 1,a[t] + r + 1,cmp1);
	int p = l + 1;
	for(int i = mid + 1;i <= r;i++){
		for(;(cmp1(a[t][p],a[t][i]) || a[t][p].h == a[t][i].h) && p <= mid;p++){
			ta.c(a[t][p].v,a[t][p].ma,a[t][p].ca);
		}
		double c = 0;
		int m = 0;
		ta.q(a[t][i].v,m,c);
		if(a[t][i].ma < m + 1){
			a[t][i].ma = m + 1;
			a[t][i].ca = c;
		} else if(a[t][i].ma == m + 1){
			a[t][i].ca += c;
		}
	}
	for(int i = l + 1;i <= mid;i++){
		ta.d(a[t][i].v);
	}
	sort(a[t] + mid,a[t] + r + 1,cmp3);
	CDQ(mid,r,t);
	sort(a[t] + l + 1,a[t] + r + 1,cmp1);
}

void ih(int t){
	sort(a[t] + 1,a[t] + n + 1,cmp2);
	rk[t][1] = 1;
	for(int i = 2;i <= n;i++){
		rk[t][i] = (cmp4(a[t][i],a[t][i - 1])) ? rk[t][i - 1] : i;
	}
	for(int i = 1;i <= n;i++){
		a[t][i].v = rk[t][i];
	}
	sort(a[t] + 1,a[t] + n + 1,cmp3);
	for(int i = 1;i <= n;i++){
		a[t][i].ma = 1;
		a[t][i].ca = 1;
	}
}

int len;
double ans;

void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[0][i].h >> a[0][i].v;
		a[0][i].p = i;
		a[1][i].h = a[0][i].h;
		a[1][i].v = a[0][i].v;
		a[1][i].p = i;
	}
	ih(0);
	CDQ(0,n,0);
	tr = true;
	ih(1);
	CDQ(0,n,1);
	tr = true;
	sort(a[0] + 1,a[0] + n + 1,cmp3);
	sort(a[1] + 1,a[1] + n + 1,cmp3);
	for(int i = 1;i <= n;i++){
		len = max(len,a[0][i].ma);
	}
	cout << len << '\n';
	for(int i = 1;i <= n;i++){
		if(a[0][i].ma == len){
			ans += a[0][i].ca;
		}
	}
	cout << fixed << setprecision(5);
	for(int i = 1;i <= n;i++){
		if(a[0][i].ma + a[1][i].ma - 1 == len){
			cout << (a[0][i].ca * a[1][i].ca) / ans << " ";
		} else {
			cout << "0.00000 ";
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