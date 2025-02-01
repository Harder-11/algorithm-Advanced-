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
分块:
我们把数组先切为sqrt(N)段,每段有sqrt(N)个元素
然后创建一下数组:L[BLOCK],R[BLOCK],cnt[BLOCK],belong[BLOCK];
LR表示块的左右分块,cnt表示每一块内的元素,belong[i]表示数组的第i个元素属于第几块

查询的时候,遇到块的时候就直接利用整段信息加速,否则就暴力爬
这样做下来整个的时间复杂度就O(sqrt(N))
*/

const int B = 505;
//st和ed分别代表块的起点和终点,sz[i]为块的大小
//belong代表每个数属于的分块
int st[N],ed[N],sz[N],n,belong[N];

void build(){
	int num = sqrt(n);
	for(int i = 1;i <= num;i++){
		st[i] = n / num * (i - 1) + 1;
		ed[i] = n / num * i;
	}
	//注意这里要更改最后一个块的ed,因为可能n是102这种数
	//102,那么每块就是10长度,最后一个块是91~102
	ed[num] = n;
	//两个for循环在O(N * sqrt(N))的时间同时填好belong数组和sz数组
	for(int i = 1;i <= num;i++){
		for(int j = st[i];j <= ed[i];j++){
			belong[j] = i;
		}
		sz[i] = ed[i] - st[i] + 1;
	}
}


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