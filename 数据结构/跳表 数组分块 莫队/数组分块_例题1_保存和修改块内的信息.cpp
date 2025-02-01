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
两种操作
1.区间[x,y]每个数都加上z
2.查询区间[x,y]内大于等于z的数的个数

思路:这道题一看看上去是线段树,但是每次加z之后无法统计>=z的个数
只能暴力修改会导致复杂度太高超时,所以我们考虑分块操作
我们询问一个块内 >= z的数的个数,所以需要一个t数组来对块内数组排序后用lower_bound即可,
a为原来未排序的数组,对于整块的修改,使用类似于标记永久花的方式,用delta数组记录现在块内整体加上的值
设q为查询和修改的操作总和,那么复杂度就是O(q * sqrt(N) * logN)(每次只对一个块进行排序,所以复杂度是sqrt(N) * log(sqrt(N)),由对数知识去掉log里面的sqrt为1/2,所以
总的复杂度就是O(q * sqrt(N) * log(N)))
*/
const int B = 1005;
int st[B],ed[B],belong[N],t[N],a[N],delta[N],n,q;
int l,r,v,num;

void build(){
	num = sqrt(n);
	for(int i = 1;i <= num;i++){
		st[i] = n / num * (i - 1) + 1;
		ed[i] = n / num * i;
	}
	ed[num] = n;
	for(int i = 1;i <= num;i++){
		for(int j = st[i];j <= ed[i];j++){
			belong[j] = i;
		}
	}
}

void Sort(int k){
	for(int i = st[k];i <= ed[k];i++) t[i] = a[i];
	sort(t + st[k],t + ed[k] + 1);
}

void modify(int l,int r,int c){
	int x = belong[l],y = belong[r];
	if(x == y){
		//在用一个块里面就直接暴力求
		for(int i = l;i <= r;i++) a[i] += c;
		Sort(x);
		return;
	}
	for(int i = l;i <= ed[x];i++) a[i] += c;
	for(int i = st[y];i <= r;i++) a[i] += c;
	//中间的块直接打上标记
	for(int i = x + 1;i < y;i++) delta[i] += c;
	Sort(x);
	Sort(y);
}

int Answer(int l,int r,int c){
	int ans = 0,x = belong[l],y = belong[r];
	if(x == y){
		//x == y,在用一个块里面就暴力处理
		for(int i = l;i <= r;i++){
			if(a[i] + delta[x] >= c) ans++;
		}
		return ans;
	}
	//分别处理头尾两个位置的元素(暴力处理)
	for(int i = l;i <= ed[x];i++){
		if(a[i] + delta[x] >= c) ans++; 
	}
	for(int i = st[y];i <= r;i++){
		if(a[i] + delta[y] >= c) ans++;
	}
	for(int i = x + 1;i < y;i++){
		ans += ed[i] - (lower_bound(t + st[i],t + ed[i] + 1,c - delta[i]) - t) + 1;
	}
	return ans;
}

void solve(){
	cin >> n >> q;
	build();
	for(int i = 1;i <= n;i++) cin >> a[i];
	//注意这里必须提前对每个块都排序,否则会导致有些没有modify的块没有排序然后查询就会出错
	for(int i = 1;i <= num;i++){
		Sort(i);
	}
	while(q--){
		char op;
		cin >> op;
		if(op == 'M'){
			cin >> l >> r >> v;
			modify(l,r,v); 
		} else {
			cin >> l >> r >> v;
			cout << Answer(l,r,v) << '\n';
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