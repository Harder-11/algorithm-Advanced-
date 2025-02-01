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
动态逆序对:
对于序列a,他的逆序对定义为集合{(i,j)|i < j && ai > aj}中元素的个数
先给出1~n的一个排序,按照某种顺序依次删除m个元素,你的任务的每次删除一个元素之前统计整个序列的逆序对数 
输入:第一行包含两个整数n,m,即初识元素的个数和删除元素的个数
以下n行,每行包含一个1~n之间的正整数,即初始排列
接下来m行,每行一个正整数,一次为每次删除的元素

思路:对于每个被删的元素,消失的逆序对数等于:
在它前面,权值比他大,并且删去时间比他晚的点的个数
在它后面,权值比他小,并且删去时间比他晚的点的个数
那么每个点维护三个属性:位置,权值,删去时间
那么先静态排序,删去一维,就完全变成了三维偏序问题了
*/

int n,m;
int lowbit(int x){
	return x & -x;
}

struct Bit {
	int tr[N];
	void add(int x,int v){
		while(x <= n + 1){
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
}BIT;

struct node {
	//del是时间顺序,val是值大小,ans是与其形成逆序对的数目
	int val,del,ans;
} a[N];

int rv[N];
ll res;

bool cmp1(const node &a,const node &b){
	return a.val < b.val;
}

bool cmp2(const node &a,const node &b){
	return a.del < b.del;
}

void CDQ(int l,int r){
	if(r - l == 1) return;
	int mid = (l + r) >> 1;
	CDQ(l,mid);
	CDQ(mid,r);
	int i = l + 1,j = mid + 1;
	while(i <= mid){
		//保证左边的val > 右边的val
		while(a[i].val > a[j].val && j <= r){
			BIT.add(a[j].del,1);
			j++;
		}
		a[i].ans += BIT.query(m + 1) - BIT.query(a[i].del);
		i++;
	}
	i = l + 1,j = mid + 1;
	while(i <= mid){
		while(a[i].val > a[j].val && j <= r){
			BIT.add(a[j].del,-1);
			j++;
		}
		i++;
	}
	i = mid,j = r;
	while(j > mid){
		while(a[j].val < a[i].val && i > l){
			BIT.add(a[i].del,1);
			i--;
		}
		a[j].ans += BIT.query(m + 1) - BIT.query(a[j].del);
		j--;
	}
	//以下进行回撤操作,把BIT清空
	i = mid,j = r;
	while(j > mid){
		while(a[j].val < a[i].val && i > l){
			BIT.add(a[i].del,-1);
			i--;
		}
		j--;
	}
	sort(a + l + 1,a + r + 1,cmp1);
}

void solve(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> a[i].val;
		rv[a[i].val] = i;
	}
	//del是时间顺序,这里利用permulation的性质进行填写
	for(int i = 1;i <= m;i++){
		int p; cin >> p;
		a[rv[p]].del = i;
	}
	//把不进行删除的数字的del置为m + 1,这样查询的时候就不会出错
	for(int i = 1;i <= n;i++){
		if(a[i].del == 0){
			a[i].del = m + 1;
		}
	}
	//先第一遍求出总的逆序对的个数
	for(int i = 1;i <= n;i++){
		//由于求的是逆序对,要用查询的(n + 1)的值 - 查询(a[i].val)的个数才正确
		//比如1 2 5 4 3,在4位置的时候,1,2,5已经放入了BIT中,此时答案明显是1,那么就要用n + 1(也就是6),求到query(6) = 3
		//然后query(4) = 2,二者相减得到1,也就是对应的5 4这个逆序对
		//这里也解释了为什么在BIT的add操作里面x <= n + 1的原因, <= n是不够的,因为是偏序关系,这样等于n的数字就没有计算进去
		res += BIT.query(n + 1) - BIT.query(a[i].val);
		BIT.add(a[i].val,1);
	}
	//用了树状数组之后记得还原
	for(int i = 1; i <= n;i++){
		BIT.add(a[i].val,-1);
	}
	//然后开始跑CDQ求到每个数对于的与之匹配的逆序对个数
	CDQ(0,n);
	sort(a + 1,a + n + 1,cmp2); 
	for(int i = 1;i <= m;i++){
		cout << res << '\n';
		res -= a[i].ans;
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