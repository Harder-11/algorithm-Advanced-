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
子树查询类问题:
dsu on tree和长链剖分都是解决子树类静态问题的统计类算法
首先,这类算法首要是子树查询,并且是静态的,也就是不带修改的
注意,某些问题其实不太必要上dsu on tree,比如子树元素和或者子树元素最大值之类的(可以合并区间信息)
可以解决的问题:比如子树的众数,子树元素的种类数

dsu on tree和长链剖分可以解决的场景和线段树合并的场景很多情况是相同的,但是实际上
线段树合并并不难学,在真正使用的时候,dsu on tree和长链剖分的常数更小

dsu on tree这个算法的本质是优雅的暴力,也就是在思想上面更接近于莫队,但是在复杂度的证明上面
又偏向于轻重树链剖分,所以它有"树上启发式合并","轻重树链分治"的别名
既然dsu on tree和莫队思想上相同,那么先复习莫队的思路:
假设有一个数组a,数组里面有若干个元素,然后你已知[l1,r1]这段区间内的区间和,假设[l1,r1]和[l2,r2]
这两段区间有大面积重合,那么就可以直接暴力扩展l1和r1到l2和r2,然后求到[l2,r2]的区间和,这样就节约了求他们公共部分的时间复杂度
那么求任意两个相邻查询之间就能节约出一个公共子问题的复杂度,在子树里面有这种公共子问题吗?
--我们会发现对于子树类查询,当且仅当两个查询的子树根节点x,y存在公共祖先关系的时候(也就是x是y或者y是x的祖先),他们存在重复子问题,并且重复子问题的重复率是100%
因为这样映射到一个数组里面就会变成一个完全包含的关系(其实本身在树上也是完全包含的),并且也就只有这种情况有
覆盖率,否则覆盖率就是0%
我们可以很容易的发现,对于一棵树,我们假设1是4的根节点,此时每次求的是子树的点权和
如果先求1为根的子树,然后求4为根的子树,此时有3步:
dfs(1),init(),dfs(4)
但是如果我们先求4为根的子树,此时就是:
dfs(4),dfs(1),此时求dfs(1)的时候包括了dfs(4),那么相当于求dfs(4)的时候没有占用时间复杂度

那么此时新问题来了:怎么安排顺序使得复杂度最小化?只有两种情况:单链和分叉
--首先考虑单链情况,这种情况最简单,只需要dfs(n),dfs(n - 1)....dfs(1)顺序执行即可
--对于分叉的情况,我们加上又rt节点,rt节点有3个子节点分别是x(size = 8),y(size = 4),z(size = 2)
那么此时dfs(y);init();dfs(z);init;dfs(x);dfs(rt)或者dfs(z);init();dfs(y);init();dfs(x);dfs(rt)都是一样的复杂度
但是注意,此时dfs(rt)前面必须是dfs(x),因为size(x)最大,这样可以省略的计算最多
总结就是:
1.优先处理子树查询,再处理根节点
2.当出现多个子树的时候,优先处理子树尺寸较小的子树,然后init清空,最后处理尺寸最大的子树
最后保留信息处理根节点;也就是优先处理轻儿子,最后处理重儿子然后保留信息,处理根节点

*/

//DSU on tree的实现代码如下:
//代码是实现了:u询问以u为根的子树里一共出现
//给出一棵n个节点以1为节点的树,节点u的颜色为cu,现在对于每个结点了多少种不同的颜色?
//其中n <= 2e5
int n;
vector<int> G[N];
//siz:子树大小,son:重儿子,col:节点的颜色
//L[u]:节点u的dfs序,R[u]:节点u子树中dfs序的最大值
//rnk[i]:dfs为i的结点,ans:存答案
//cnt[i]:颜色为i的结点个数;color:目前出现过的颜色数
int siz[N],son[N],col[N],L[N],R[N],rnk[N],tot;
int ans[N],cnt[N],color;

void add(int u){
	if(cnt[col[u]] == 0) color++;
	cnt[col[u]]++;
}

void del(int u){
	cnt[col[u]]--;
	if(cnt[col[u]] == 0) color--;
}

void dfs1(int u,int f){
	L[u] = ++tot;
	rnk[tot] = u;
	siz[u] = 1;
	for(int v : G[u]){
		if(v == f) continue;
		dfs1(v,u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]){
			son[u] = v;
		}
	}
	R[u] = tot;
}

//dsu on tree的核心代码
//这里的keep参数是看是否进行类似init操作
//如果是重儿子,keep = true,此时不进行del,可以减少时间复杂度
//只要是轻二者就进行del还原
void dfs2(int u,int f,bool keep){
	for(int v : G[u]){
		if(v != f && v != son[u]){
			dfs2(v,u,false);
		}
	}
	if(son[u]){
		dfs2(son[u],u,true);
	}
	//把所有的轻儿子进行add操作
	for(int v : G[u]){
		if(v != f && v != son[u]){
			for(int i = L[v];i = R[v];i++){
				add(rnk[i]);
			}
		}
	}
	//子树也包含u本身,最后不要忘记add(u)
	add(u);
	//填充ans数组
	ans[u] = color;
	if(!keep){
		for(int i = L[u];i <= R[u];i++){
			del(rnk[i]);
		}
	}
}

void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> col[i];
	for(int i = 1;i <= n;i++){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,false);
	for(int i = 1;i <= n;i++){
		cin >> ans[i] >> '\n'[i == n];
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