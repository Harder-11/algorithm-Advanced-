#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2000005;
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
ZJOI2007 https://www.luogu.com.cn/problem/P2272
思路:很显然本题有dp思想在里面
在我们进行完SCC缩点之后,点的排列顺序是拓扑逆序,在拓扑序下dp即可
对于求极大值:那么我们不妨设f[i]:i及其之前所有的点在选i的情况下最多能有多少个点
f[i] = max(f[i]的前驱) + i强联通分量中点的个数
而求图的个数,仍然是dp求,设为g[i]
显然就有g[i] = Σg[j](j是i的前驱并且f[i] = f[j] + i中强联通分量个数)
*/

int n,m,tot,MOD,top,num,scc,tot1;
int h[N],nxt[N],to[N],dfn[N],low[N],stk[N],id[N],siz[N],vis[N];
int h1[N],nxt1[N],to1[N],f[N],g[N],used[N];//used判重边

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

void add1(int u,int v){
	nxt1[++tot1] = h1[u];
	to1[tot1] = v;
	h1[u] = tot1;
}

void tarjan(int u){
	dfn[u] = low[u] = ++num;
	stk[++top] = u;
	vis[u] = 1;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u],low[v]);
		} else if(vis[v]){
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(dfn[u] == low[u]){
		scc++;
		int x;
		do {
			x = stk[top--];
			siz[scc]++;
			id[x] = scc;
			vis[x] = 0;
		} while(x != u);
	}
}

void solve(){
	cin >> n >> m >> MOD;
	for(int i = 1,u,v;i <= m;i++){
		cin >> u >> v;
		add(u,v);
	}
	for(int i = 1;i <= n;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int u = 1;u <= n;u++){
		f[u] = siz[u];
		g[u] = 1;
		for(int i = h[u];i;i = nxt[i]){
			int v = to[i];
			if(id[u] == id[v]) continue;
			add1(id[u],id[v]);
		}
	}
	for(int u = scc;u >= 1;u--){
		for(int i = h1[u];i;i = nxt1[i]){
			int v = to1[i];
			if(used[v] == u) continue;//处理重边
			used[v] = u;
			if(f[v] < f[u] + siz[v]){
				f[v] = f[u] + siz[v];
				g[v] = g[u];
			} else if(f[v] == f[u] + siz[v]){
				g[v] = (g[u] + g[v]) % MOD;
			}
		}
	}
	int ans = 0,r = 0;
	for(int i = 1;i <= scc;i++){
		if(f[i] > ans){
			ans = f[i];
			r = g[i];
		} else if(f[i] == ans){
			r = (r + g[i]) % MOD;
		}
	}
	cout << ans << "\n" << r << '\n';
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