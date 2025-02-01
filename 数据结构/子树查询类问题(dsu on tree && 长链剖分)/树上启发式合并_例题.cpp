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
题目大意:树的节点有颜色,一种颜色占领了一个子树,当前仅当没有其他颜色在这个子树中出现的次数比他多
求:占领每个子树的颜色之和

思路:如果求cnt?
--很容易想到用map保存,mp[u][color]表示点u的子树,颜色color的出现次数
那么如何进行优化?
--在合并两棵子树的时候,将小的合并到大的上面,我们可以粗略进行估算时间复杂度:
map在合并的时候是O(logN)的,那么总时间就是O(N(logN)^2),可以通过
在计算答案的时候,只需要对每个点记录mx[i](最大的出现次数)和ans[i](此次数对于的答案)
在合并中维护即可
*/

int h[N],to[N],nxt[N],tot;
ll ans[N];
int col[N],son[N],siz[N],fa[N],cnt[N];
ll sum,mx,n;

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

//change的参数p相当于是唯一的不能走的那个点,也就是重儿子
//所以在for循环里面不能直接是v == son[u],这样就会导致更下层节点的重儿子仍然不能走
//但是要求的是除开u重儿子的所有节点的,所以就要这样传参
void change(int u,int val,int p){
	cnt[col[u]] += val;
	if(cnt[col[u]] > mx){
		mx = cnt[col[u]];
		sum = col[u];
	} else if(cnt[col[u]] == mx){
		sum += col[u];
	}
	for(int i = h[u];i;i = nxt[i]){
		//重儿子的信息没有删除,已经统计过所以不能再次计算
		int v = to[i];
		if(v == fa[u] || v == p) continue;
		change(v,val,p);
	}
}

void dfs1(int u,int f){
	siz[u] = 1;
	fa[u] = f;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f) continue;
		dfs1(v,u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]){
			son[u] = v;
		}
	}
}

void dfs2(int u,int op){
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v,0);
	}
	if(son[u]){
		dfs2(son[u],1);
	}
	change(u,1,son[u]);
	ans[u] = sum;
	//记得如果走的轻儿子就每次重置sum = mx = 0
	//并且把cnt数组给还原
	//注意,此时轻儿子还原操作就没有限制了,那么p参数传0即可
	if(!op){
		change(u,-1,0);
		sum = mx = 0;
	}
}

void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> col[i];
	for(int i = 1,u,v;i < n;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	for(int i = 1;i <= n;i++) cout << ans[i] << " ";
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