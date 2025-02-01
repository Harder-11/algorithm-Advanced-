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
树上倍增的写法类似于ST表,但是不论维护什么信息,都要维护一个fa数组
fa[i][j]表示树上的第i个结点向上跳跃2^j后的结点是谁
预处理是一个很简单的dp问题,fa[i][j] = fa[fa[i][j - 1]][j - 1];
使用起来就是位运算的二分的写法
*/

//以下是标准的倍增求LCA写法
//需要有dep数组表示结点的深度,fa数组表示某节点的父节点编号
int dep[N],fa[N][21];
//链式前向星建图
int h[N],nxt[N << 1],to[N << 1],cnt;

void add(int u,int v){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	h[u] = cnt;
}

void dfs(int u,int f){
	dep[u] = dep[f] + 1;
	fa[u][0] = f;
	for(int i = 1;i <= 20;i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		dfs(v,u);
	}
}

//倍增求LCA
int lca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	for(int i = 20;i >= 0;i--){
		if(dep[fa[x][i]] > dep[y]){
			x = fa[x][i];
		}
	}
	if(x == y) return x; 
	for(int i = 20;i >= 0;i--){
		if(fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
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