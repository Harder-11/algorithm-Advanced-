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
https://www.luogu.com.cn/problem/P2341
本题找SCC缩点之后出度为0的点即可
*/

int h[N],nxt[N],to[N],tot;
int low[N],dfn[N],cnt,vis[N],stk[N],top,id[N],idx,siz[N];
int n,m,u,v;

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

void tarjan(int u){
	dfn[u] = low[u] = ++cnt;
	vis[u] = 1;
	stk[++top] = u;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[v],low[u]);
		} else if(vis[v]){
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(dfn[u] == low[u]){
		idx++;
		int x;
		do {
			x = stk[top--];
			id[x] = idx;
			siz[idx]++;
			vis[x] = 0;
		} while(x != u);
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> u >> v;
		add(u,v);
	}
	for(int i = 1;i <= n;i++){
		if(!dfn[i]) tarjan(i);
	}
	vector<int> dout(idx + 1,0);
	for(int u = 1;u <= n;u++){
		for(int i = h[u];i;i = nxt[i]){
			int v = to[i];
			if(id[u] != id[v]){
				dout[id[u]]++;
			}
		}
	}
	int sum = 0,r = 0;
	for(int i = 1;i <= idx;i++){
		if(dout[i] == 0){
			sum = siz[i];
			r++;
		}
	}
	if(r > 1) sum = 0;
	cout << sum << '\n';
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