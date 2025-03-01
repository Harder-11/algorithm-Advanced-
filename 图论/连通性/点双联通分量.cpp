#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 500005;
const int M = 4000005;
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

int cnt = 1;
int h[N],nxt[M],to[M];
int stk[M],top,bcc,low[N],dfn[N],idx,n,m,u,v;
vector<int> ans[N];

void add(int u,int v){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	h[u] = cnt;
}

void tarjan(int u,int f){
	int son = 0;
	low[u] = dfn[u] = ++idx;
	stk[++top] = u;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(!dfn[v]){
			son++;
			tarjan(v,u);
			low[u] = min(low[v],low[u]);
			if(low[v] >= dfn[u]){
				bcc++;
				while(stk[top + 1] != v){
					ans[bcc].push_back(stk[top--]);
				}
				ans[bcc].push_back(u);
			}
		} else {
			low[u] = min(low[u],dfn[v]);
		}
	}
	//特判独立点
	if(f == 0 && son == 0) ans[++bcc].push_back(u);
}

void solve(){		
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	for(int i = 1;i <= n;i++){
		if(dfn[i]) continue;
		top = 0;
		tarjan(i,0);
	}
	cout << bcc << '\n';
	for(int i = 1;i <= bcc;i++){
		cout << ans[i].size() << " ";
		for(int j : ans[i]) cout << j << " ";
		cout << '\n';
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