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
树上差分可以理解为对树上某一路径进行差分操作,这里的路径可以类比一维数组的区间进行理解
例如在对树上的一些路径进行频繁操作,并且询问某条边或者某个点在经过操作以后的值的时候,就可以进行树上差分的思想了
树上差分通常会和LCA一起考察,并且树上差分分为点差分和边差分,在实现上稍有不同

点差分:对于树上的一些路径δ(s1,t1),δ(s2,t2),δ(s3,t3)进行询问,问一条路径上的点被访问的次数
对于一次δ(s,t)的访问,需要找到s和t的LCA,然后对这条路径上的点进行访问(点的权值+1),若采用dfs对每个点进行访问,会TLE,那么进行差分操作:
ds <- ds + 1
d(lca) <- d(lca) - 1
dt <- dt + 1
d(f(lca)) <- d(f(lca)) - 1
其中f(x)表示x的父节点,di表示点权为ai的差分数组

边差分:若是对路径上的边进行访问,就需要进行边差分,使用一下公式:
ds <- ds + 1
dt <- dt + 1
d(lca) <- d(lca) - 2
由于在边上进行差分比较困难,所以将边差分转化为点差分即可

例题:FJ给他的牛棚的N(2 <= N <= 50000)个隔间安装了N - 1根管道,隔间编号为1到N,所有隔间都被管道联通了
FJ有K条运输牛奶的路线,第i条路线从隔间si运输到ti,一条运输路线会给他的两个端点处的隔间以及中间所有隔间带来一个单位的运输压力
你需要计算最大的隔间压力是多少?

思路:需要拥挤每个点经过了多少次,就用树上差分将每一次的路径+1,很快就能得到每个点的经过次数,采用倍增求LCA,最后dfs遍历整棵树
在回溯的时候对差分数组求和即可得到答案
*/

int to[N],nxt[N],h[N],cnt;
int fa[N][31],dep[N],power[N];
int n,k,ans;

void add(int u,int v){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	h[u] = cnt; 
}

void dfs(int u,int f){
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
	for(int i = 1;i <= 30;i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		dfs(v,u);
	}
}

int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int i = 30;i >= 0;i--){
		if(dep[fa[x][i]] >= dep[y]){
			x = fa[x][i];
		}
	}
	if(x == y) return x;
	for(int i = 30;i >= 0;i--){
		if(fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

//dfs求最大压力,回溯时将子树的权值加上
void get_ans(int u,int f){
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		get_ans(v,u);
		power[u] += power[v];
	}
	ans = max(ans,power[u]);
}

void solve(){
	cin >> n >> k;
	int x,y;
	for(int i = 1;i < n;i++){
		cin >> x >> y;
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	int s,t;
	for(int i = 1;i <= k;i++){
		cin >> s >> t;
		int r = lca(s,t);
		power[s]++;
		power[t]++;
		power[r]--;
		power[fa[r][0]]--;
	}
	get_ans(1,0);
	cout << ans << '\n';
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