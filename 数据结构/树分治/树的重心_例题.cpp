#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 300005;
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
给定一棵有根树,求出每一棵子树(有根树意义下且包含整棵树本身)的重心是哪一个节点

思路:对于一棵以u为根的子树,其重心一定在所有以u为根的直接子节点为根的子树的重心到点u的路径上
那么直接dfs求到每棵以u为根的子树,然后求出所有先求出所有以其直接子节点为根的子树的重心（叶子节点的重心是其本身)
然后向上判断路径上的节点是不是重心即可
*/
int n,q;
int h[N],to[N],nxt[N],tot;
int siz[N],weight[N],ans[N],fa[N];

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

void dfs(int u){
	siz[u] = 1;
	ans[u] = u;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		dfs(v);
		siz[u] += siz[v];
		weight[u] = max(weight[u],siz[v]);
	}
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		int p = ans[v];
		while(p != u){
			if(max(weight[p],siz[u] - siz[p]) <= siz[u] / 2){
				ans[u] = p;
				break;
			} else p = fa[p];
		}
	}
}

void solve(){
	cin >> n >> q;
	for(int i = 2;i <= n;i++){
		cin >> fa[i];
		add(fa[i],i);
	}
	dfs(1);
	while(q--){
		int u; cin >> u;
		cout << ans[u] << '\n';
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