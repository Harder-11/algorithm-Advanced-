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

//求树的重心基础(树型dp)
//siz表示这个节点的大小(子树上的节点数+该节点),weight表示这个节点的重量,即所有子树大小的最大值
//cen是记录的树的重心
int siz[N],weight[N],cen[2],n;
int h[N],to[N << 1],nxt[N << 1],cnt;

void add(int u,int v){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	h[u] = cnt;
}

//一遍dfs求重心
void dfs(int u,int f){
	siz[u] = 1;
	weight[u] = 0;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		dfs(v,u);
		siz[u] += siz[v];
		weight[u] = max(weight[u],siz[v]);
	}
	weight[u] = max(weight[u],n - siz[u]);
	//树上重心可能不止一个,但是最多两个
	//如果cen[0] != 0,那么就是0已经存了东西,此时就是给cen[1]赋值cur
	//如果cen[0] = 0,那么就给cen[0]存东西
	if(weight[u] <= n / 2){
		cen[cen[0] != 0] = u;
	}
}

void solve(){}

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