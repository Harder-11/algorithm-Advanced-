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
给出一个0 <= N <= 1e5点数,0 <= M <= 1e5边数的有向图
输出一个尽可能小的点集,使得从这些点出发能够到达任意一点,如果有多个这样的集合,输出这些集合升序排序后字典序最小的那个

思路:很明显,本题进行SCC缩点之后找入度为0的强联通分量即可
注意:如果有多个分量缩点后的入度为0,那么就都要选,否则这样的分量会互相无法到达
*/

int h[N],to[N],nxt[N],tot;
int dfn[N],low[N],cnt,vis[N],stk[N],top,id[N];
int scc_cnt;
vector<int> res;
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
			low[u] = min(low[u],low[v]);
		} else if(vis[v]){
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(low[u] == dfn[u]){
		scc_cnt++;
		int x;
		do {
			x = stk[top--];
			id[x] = scc_cnt;
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
	for(int i = 1;i <= n;i++) if(!dfn[i]) tarjan(i);
	//由于要最小点集,那么取每个SCC编号最小点即可
	vector<int> mn(scc_cnt + 1,INF),indeg(scc_cnt + 1,0),ans;
	for(int i = 1;i <= n;i++){
		mn[id[i]] = min(mn[id[i]],i);
	}
	for(int u = 1;u <= n;u++){
		for(int i = h[u];i;i = nxt[i]){
			int v = to[i];
			if(id[u] != id[v]){
				indeg[id[v]]++;
			}
		}
	}
	for(int i = 1;i <= scc_cnt;i++){
		if(indeg[i] == 0){
			ans.push_back(mn[i]);
		}
	}
	sort(ans.begin(),ans.end());
	cout << ans.size() << "\n";
	int len = ans.size();
	for(int i = 0;i < len;i++){
		cout << ans[i] << " \n"[i == len - 1];
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