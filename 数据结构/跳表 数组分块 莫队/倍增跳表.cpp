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
如果是朴素的查询RMQ问题,或者其他可以重复合并的信息,比如说区间gcd
也就是多次重复合并并不影响的情况下,就不要写根号跳表而是写倍增跳表
倍增跳表的定义:首先开一个ST[N][logN]
ST[i][j]表示以i为起点往后延伸1 << j的区间信息,显然存在一个dp的转移方程
ST[i][j] = max(ST[i][j - 1],ST[i + (1 << (j - 1))][j - 1])(比如要求ST[1][2] = max(ST[1][1],ST[3][1]));
在查询区间[l,r]的时候
k = log(2,r - l + 1);
ans = max(ST[l][k],ST[r - (1 << k) + 1][k]);
---建议不要用C++库中的log2函数,一是精度问题,而是常数问题
---可以预处理写成:
LG2[1] = 0;
for(int i = 2;i < N;i++) LG[i] = LG[i / 2] + 1;

*/

int n,q;
int a[N],ST_max[N][16],ST_min[N][16],l,r;
void st_table(){
	//首先初始化ST_max,ST_min,所有的[i][0]位置都是a[i];
	for(int i = 1;i <= n;i++){
		ST_max[i][0] = ST_min[i][0] = a[i];
	}
	for(int j = 1;(1 << j) <= n;j++){
		for(int i = 1;i + (1 << j) - 1 <= n;j++){
			ST_max[i][j] = max(ST_max[i][j - 1],ST_max[i + (1 << (j - 1))][j - 1]);
			ST_min[i][j] = min(ST_min[i][j - 1],ST_min[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int RMQ(int l,int r){
	//不用log2函数,写循环求log
	int k;
	for(k = 0;(1 << (k + 1)) <= (r - l + 1);k++);
	int mx = max(ST_max[l][k],ST_max[r - (1 << k) + 1][k]);
	int mn = min(ST_min[l][k],ST_min[r - (1 << k) + 1][k]);
	return mx - mn;
}

void solve(){
	while(scanf("%d%d",&n,&q) != EOF){
		for(int i = 1;i <= n;i++){
			cin >> a[i];
		}
		st_table();
		while(q--){
			cin >> l >> r;
			printf("%d\n",RMQ(l,r));
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