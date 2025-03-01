#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 505;
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
CF 387D
题目大意:给出一个n个结点,m条边的有向图,你可以进行若干次操作,每次操作可以删除图中的一条边
或者添加一条有向边,使得原图变成一个中心图
我们定义一个图是中心图,当前仅当它满足如下条件:
1.图中没有重边
2.存在一个点u,满足对于任意的v∈[1,n],图中都存在边(u,v)和(v,u)
我们称u是中心点,这意味着u本身必须存在一个自环
3.除了中心点以外,其他所有点的入度和出度均为2
你需要保证操作次数尽可能少,求最少的操作次数
2 <= n <= 500,1 <= m <= 1000

思路:首先我们肯定要枚举中心点,然后将中心点和其余的点连边(如果存在边就忽略)
而对于不是中心点的点,我们此时要满足除开与中心点的边外,入度和出度都是1
那么我们将每个点拆为出点和入点分为两个集合,然后作为一个二分图找最大权完美匹配即可
*/

int n,m,cnt[N],lnk[N],f,vis[N];
std::vector<int> e[N],g[N];

int dfs(int x){
	for(int i = 0;i < e[x].size();i++){
		int y = e[x][i];
		if(vis[y] < f){
			vis[y] = f;
			if(lnk[y] == 0 || dfs(lnk[y])){
				lnk[y] = x;
				return 1;
			}
		}
	}
	return 0;
}

void solve(){
	cin >> n >> m;
	int res = INF;
	for(int i = 1,u,v;i <= m;i++){
		cin >> u >> v;
		if(u != v){
			cnt[u]++;
			cnt[v]++;
		} else {
			cnt[u]++;
		}
		g[u].push_back(v);
	}
	for(int i = 1;i <= n;i++){
		int ans = 0,r = 0;
		ans = 2 * n - 1 - cnt[i];
		for(int j = 1;j <= n;j++){
			e[j].clear();
			vis[j] = 0;
			lnk[j] = 0;
		}
		for(int j = 1;j <= n;j++){
			if(i == j) continue;
			for(int k = 0;k < g[j].size();k++){
				if(g[j][k] == i) continue;
				e[j].push_back(g[j][k]);
			}
		}
		f = 0;
		for(int j = 1;j <= n;j++){
			if(i == j) continue;
			f++;
			if(dfs(j)) r++;
		}
		ans += (m - cnt[i] - r) + (n - 1 - r);
		res = min(res,ans);
	}
	cout << res << '\n';
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