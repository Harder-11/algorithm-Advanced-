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
tarjan算法求割点和桥(割边)
时间戳dfn:第几个搜到这个点
返祖边:搜索树上一个点连续其他祖先结点的边
横插边:搜索树上一个点连向它另一条支链上的点的边---在无向图中不存在
追溯值low:当前点及其子树通过一条返祖边能到达的dfn值最小的点
如果<u,v>是搜索树的边:low[u] = min(low[u],low[v])
如果<u,v>是返祖边:low[u] = min(low[u],dfn[v]);
这样操作以后,只要满足条件:在以该节点某个儿子为根的子树里面不存在跨越它连向上方的点的边
那么该点就是割点,那么我们就看每个儿子的low值是不是都小于当前结点,如果是就说明是割点;
而(u,v)如果是割边,那么就满足以v为根的子树不存在连向u及其u上方的边

那么总结如下:
1.当u是割点,v是u搜索树上的一个儿子:dfn[u] <= low[v],v的子树中没有返祖边能跨越u点
2.如果边是桥,搜索树上v是u的儿子:dfn[u] < low[v]---v的子树中没有返祖边能跨越(u,v)这条边
*/

int dfn[N],low[N],cnt,idx,is_bridge[N];
int h[N],to[N],nxt[N],tot;
int root;
//check是用来记录x是不是割点的
bool check[N];

void add(int u,int v){
	nxt[++tot] = h[u];
	to[tot] = v;
	h[u] = tot;
}

//核心代码(找割点):
void tarjan(int x){
	dfn[x] = low[x] = ++cnt;
	int f = 0;
	for(int i = h[x];i;i = nxt[i]){
		int y = to[i];
		//处理不是返祖边就接着往下搜,因为返祖边要子节点信息才能推出祖先节点的信息
		//所以立马进行递归处理
		if(!dfn[y]){
			tarjan(y);
			low[x] = min(low[x],low[y]);
			//这个判断说明当前儿子的追溯值大于x,那么返祖边就连不上x的上方去
			//那么这个x就是一个割点了
			if(low[y] >= dfn[x]){
				f++;
				//然后我们判断这个节点如果是根节点的情况,如果是根节点就必须有两个儿子
				//这样根节点才会是个割点,满足这里的if后就记录x为割点
				if(x != root || f > 1) check[x] = 1; 
			}
			//处理返祖边情况,就是比较low[x],dfn[y]
		} else {
			low[x] = min(low[x],dfn[y]);
		}
	}
}

//核心代码(求桥)
//此时比求割点更简单,不用判根节点

void tarjan2(int x){
	low[x] = dfn[x] = ++idx;
	for(int i = h[x];i;i = nxt[i]){
		int y = to[i];
		if(!dfn[y]){
			tarjan2(y);
			low[y] = min(low[x],low[y]);
			//注意求桥的时候必须严格大于,否则等于的话相当于子树有返祖边连向x,那么也不会桥
			if(low[y] > dfn[x]){
				is_bridge[y] = 1;
			}
		} else {
			low[x] = min(low[x],dfn[y]);
		}
	}
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