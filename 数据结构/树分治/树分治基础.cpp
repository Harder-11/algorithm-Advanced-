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
分治:
分治一般是统计类算法,统计类问题一般指的是不带修改,静态查询类问题,但是不同于静态查询问题,统计类问题一般要求"全查"
,例如枚举所有的子区间,枚举一棵树上所有的链,枚举一棵树上所有的子树

先看数组上的统计类问题
经典例题:
给出一个数组,求所有子数组的gcd之和
这是一个经典问题,首先我们去整个数组的中点mid画一条线,数组中所有的子区间就三种:
1.左右端点全部在mid左侧 2.左右端点全部在mid右侧 3.左右端点横跨mid
我们假设有8个数,分别是1 3 6 12 4 8 3 5,那么先找到mid位置,然后向左和向右颜色分为左半数组和右半数组
这样得到的gcd分别是1 3 6 12 4 4 1 1(左边4个是左半数组元素一直到mid子数组的gcd,右边4个是右半数组到mid子数组的gcd)
由于从mid不管是向左还是向右推,gcd的大小是递减的,而且每次减少必定是小于等于原本的1/2,那么集合去重之后一定是log级别的
那么就用两个map去维护左右两边的gcd出现的次数即可,然后两重循环遍历两个map里面的元素即可,这样复杂度是O((logN)^2)的
时间复杂度大约是O(4N * (logN)^2)

对于树上分治
1.左右端点不过分治中心mid 2.左右端点横跨分治中心mid
用这样的说法可以直接扩展到树上,成为树分治的原理
当然,树分治主要有点分治和边分治,但是主要是点分治,而且边分治可以用点分治代替
在树上做分治,类比于数组分治,那么首先肯定要找到一个中点,很显然,这个中点就是树的重心
我们定义重心:选择重心作为根节点的时候,可以最小化根节点的所有直接子树中尺寸的最大值
树的重心的性质:选择树的重心为根节点的时候,根结点的直接子树尺寸不大于N / 2,N表示整棵树的尺寸
选择重心以后就可以按照数组分治中的思路做就可以了
1.处理跨重心的树链
2.递归处理子树

例题:点分治
给定一棵有n个点的带边权数,m次询问,每次询问给出k,询问树上距离为k的点对是否存在
n <= 1e4,m <= 100,k <= 1e7

思路:我们先任意选择一个节点作为根节点rt,所有完全位于其子树的路径可以分为两种
一种是经过根节点的路径,一种是不经过当前根节点的路径;对于经过当前根节点的路径,又可以分为两种
一种是以根节点为端点的路径,一种是两个端点都不是根节点的路径;后缀又可以由两条属于前者的链合并得到
所以,对于枚举的根节点rt,我们先计算在其子树中且经过该节点的路径对答案的贡献,再递归其子树对不经过
该节点的路径进行求解
在本题中,对于经过根节点rt的路径,我们先枚举其所有子节点ch,以ch为根计算ch子树中所有节点到rt的距离
记节点i到当前根节点rt的距离为dist(i),tf(d)表示之前处理过的子树中是否存在一个结点v使得dist(v) = d
若一个询问的k满足tf(k - dist(i)) = true,则存在一条长度为k的路径,在计算完ch子树中所连的边能否成为答案之后
,我们将这些新的距离加入tf数组中
注意,在清空tf数组的时候不能直接memset,而应将之前占用过的tf位置加入一个队列里面,进行清空
这样才能保证时间复杂度
在点分治的过程中,每一层的所有递归过程合计对每个点处理一次,假设共递归h层
那么时间复杂度为O(hn),n是固定的,但是h可以减小,当我们选择子树重心作为根节点
可以保证递归的层数最小,时间复杂度为O(nlogn)
*/
const int Q = 1e7 + 5;
//q是存当前结点距离的数组,mx是最大的子树的点的个数
int n,m,tmp[Q],judge[Q];
int sz[N],vis[N],h[N],to[N],nxt[N],w[N],que[N],cnt;
int mx[N],tot,rt,dis[N],q[Q],ynn[N];

void add(int u,int v,int c){
	nxt[++cnt] = h[u];
	to[cnt] = v;
	w[cnt] = c;
	h[u] = cnt;
}

void dfs(int u,int f){
	sz[u] = 1;
	mx[u] = 0;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(v == f || vis[v]) continue;
		dfs(v,u);
		sz[u] += sz[v];
		mx[u] = max(mx[u],sz[v]);
	}
	mx[u] = max(mx[u],tot - sz[u]);
	if(mx[u] < mx[rt]) rt = u;
}

void getdis(int u,int f){
	tmp[++tmp[0]] = dis[u];
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		int c = w[i];
		if(vis[v] || v == f) continue;
		dis[v] = dis[u] + c;
		getdis(v,u);
	}
}

void calc(int u){
	int p = 0;
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		int c = w[i];
		if(vis[v]) continue;
		tmp[0] = 0;
		dis[v] = c;
		getdis(v,u);
		for(int k = tmp[0];k;k--){
			for(int l = 1;l <= m;l++){
				if(que[l] >= tmp[k]){
					ynn[l] |= judge[que[l] - tmp[k]];
				}
			}
		} 
		for(int k = tmp[0];k;k--){
			q[++p] = tmp[k];
			judge[tmp[k]] = 1;
		}
	}
	for(int i = p;i;i--){
		judge[q[i]] = 0;
	}
}

void f(int u){
	vis[u] = judge[0] = 1;
	calc(u);
	for(int i = h[u];i;i = nxt[i]){
		int v = to[i];
		if(vis[v]) continue;
		tot = sz[v];
		rt = 0;
		mx[rt] = n;
		dfs(v,0);
		f(rt);
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 1,u,v,c;i < n;i++){
		cin >> u >> v >> c;
		add(u,v,c);
		add(v,u,c);
	}
	for(int i = 1;i <= m;i++){
		cin >> que[i];
	}
	rt = 0;
	mx[rt] = n;
	tot = n;
	dfs(1,0);
	f(rt);
	for(int i = 1;i <= m;i++){
		if(ynn[i]) cout << "AYE" << '\n';
		else cout << "NAY" << '\n';
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