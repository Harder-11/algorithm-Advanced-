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
CF 741C *2600
有n对情侣(2n个人)围成一圈坐在桌子边上,每个人占据一个位置,要求情侣不能吃一种食物,并且桌子上相邻的
三个人的食物必须有两个人是不同的,只有两种食物(1或者2),求一种可行的分配方式
1 <= n <= 1e5

很显然的一个思想:我们把吃不同食物的两种人分开,那么情侣之间必定会被分开
而且题目要求相邻的三个人里面必须存在两个之间有边存在,我们可以想到把相邻两个点连边即可(也是就2i和2i + 1(i >= 0)连边)
这样不仅满足了相邻三个人里面有两个人之间存在边而且还满足了构成的图是一个二分图,那么就一定满足条件
那么这样进行分类,将情侣和相邻两人连边之后,进行二分图染色即可
*/

int n;
std::vector<int> G[N];
bitset<N> vis;
int u[N],v[N],col[N];


void dfs(int u,int v){
	col[u] = v;
	vis[u] = 1;
	for(int i = 0;i < G[u].size();i++){
		if(!col[G[u][i]]){
			dfs(G[u][i],3 - v);
		}
	}
}

void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> u[i] >> v[i];
		G[u[i]].push_back(v[i]);
		G[v[i]].push_back(u[i]);
	}
	for(int i = 1;i <= n;i++){
		G[i * 2 - 1].push_back(i * 2);
		G[i * 2].push_back(i * 2 - 1);
	}
	for(int i = 1;i <= 2 * n;i++){
		if(!vis[i]) dfs(i,1);
	}
	for(int i = 1;i <= n;i++){
		cout << col[u[i]] << " " << col[v[i]] << '\n';
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