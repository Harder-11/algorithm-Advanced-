#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1005;
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
在一个无向图中,定义一条边覆盖的点为这条边的两个端点
找到一个边集S包含最多的边,使得这个边集覆盖到的所有顶点中的每个顶点
只被一条边覆盖,S的大小叫做图的最大匹配

算法思路:对于一个男孩子x,如果他喜欢女孩y,而且y还没有舞伴,那么就让他们配对
如果y有了舞伴,x还是会尝试邀请y,如果y返现她的舞伴可以换一个舞伴,y就主动抛弃z(在z确定可以和别人牵手后)
和x成为舞伴(而且是一直往上找)

增广路:路径的起点和终点都是还没有匹配过的点,并且路径经过的连线是一条没被匹配,一条已经被匹配过
再下一条又是没匹配这样交替出现;找到这样的路径之后,显然路径里面没有匹配过的连续比已经匹配了的连线多一条
于是就修改匹配图,把路径里面所有匹配过的连续去掉匹配关系,把没有匹配的连线变成匹配的,这样匹配数就多了一个
*/

//link表示与当前结点连接的结点,a是邻接矩阵存图
int link[N],a[N][N];
int n,vis[N];

//代码利用递归很巧妙地解决问题
int dfs(int x){
	for(int i = 1;i <= n;i++){
		//如果二者根本没有边,或者右侧的点已经被之前的左侧访问过了,那么直接continue
		//注意:主函数里面每次都memset了,那么枚举不同的左侧节点时不会存在vis冲突问题
		//vis主要解决的是递归里面的问题,防止后面的结点抢了前面结点的连线
		if(!a[x][i] || vis[i]) continue;
		vis[i] = 1;
		if(link[i] == 0 || dfs(link[i])){
			link[i] = x;
			return 1;
		}
	}
	return 0;
}

void solve(){
	//枚举左侧结点
	cin >> n;
	for(int i = 1;i <= n;i++){
		memset(vis,0,sizeof vis);
		dfs(i);
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