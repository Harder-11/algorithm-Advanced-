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
树链剖分:
树链剖分是为了解决树上链信息维护的问题
利用线段树等结构,可以维护数组中的增删改查问题
树链剖分的作用实际就是将整颗结构树分解成若干段数组,然后使用一个数据结构来维护每条链的信息
(一般平衡链不会使用平衡树,不如直接使用LCT)

从数组到树:
1.如果是数组上的问题,那么直接用线段树去维护区间即可,那么如果把这种思路扩展到树上呢?
--链分解:把一棵树拆成若干个连续的"数组",且每一部分互不包含就称之为一棵树的链分解
2.那么如果任意给出一棵树的链分解呢?
--利用多叉树的dfn序,在dfs的过程中,从当前结点一路向下到叶子节点的过程天然就是一种链分解
我们定义一个top数组,作为链分解的链首,dfs的过程中,对于第一个孩子继承当前结点的top值,否则另起新链
这个代码非常简单,一个dfs就写完了

以下是实现的用dfs进行普通树链剖分的代码,都是默认的以第一个儿子作为链上的点,其他二者另起新链
*/

vector<int> G[N];
//存储每条链的结点,通常其实用不到的,在debug可以用
vector<int> chain[N];
int n,top[N],u,v;

//dfs实现top数组
void dfs(int x,int tp){
	top[x] = tp;
	chain[tp].push_back(x);
	for(int i = 0;i < G[x].size();i++){
		//默认的第一个孩子在链上,其他的就另起一个新链
		//所以如果i = 0,就是第一个孩子,就仍然用tp做为top
		//否则的话就用其孩子作为新链的top,即用G[x][i]作为top
		dfs(G[x][i],i ? G[x][i] : tp);
	}
}

void solve(){
	cin >> n;
	for(int i = 1;i < n;i++){
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,1);
	cout << "top:" << '\n';
	for(int i = 1;i <= n;i++){
		cout << top[i] << '\n';
	}
	cout << '\n';
	for(int i = 1;i <= n;i++){
		if(chain[i].size()){
			cout << "chain: " << i << '\n';
			for(auto &j : chain[i]){
				cout << j << '\n';
			}
			cout <<< '\n';
		}
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