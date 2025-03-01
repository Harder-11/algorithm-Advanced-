#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 500005;
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
把桥删掉,那么每个联通块都是一个边双联通分量---那么标记出桥之后dfs一遍即可
点双联通分量要复杂一些---一个割点可能属于多个双联通分量,步骤如下(其实就是SCC步骤)
1.维护一个栈
2.第一次访问某个结点的时候,将其入栈
3.当割点判断法则中:dfn[x] <= low[y]成立的时候,不断从栈中弹出结点,直到y被弹出,这些被弹出的点和x一起构成一个点双联通分量
*/

//这里用pair是为了去除重边
vector<pair<int,int>> e[N];
int dfn[N],low[N];
//边双联通分量给分类
std::vector<vector<int>> ans;
int n,m,u,v,cnt;
stack<int> stk;

void tarjan(int x,int f){
	low[x] = dfn[x] = ++cnt;
	stk.push(x);
	for(auto i : e[x]){
		//首先判断反向边,我们在建图的时候依次给边编号,然后tarjan传参的时候就传编号
		//f ^ 1就是反向边,这样就可以巧妙去掉重边,因为所有的重边的反向边都是f ^ 1,这样就不会往回走 
		if(i.second == (f ^ 1)) continue;
		if(!dfn[i.first]){
			tarjan(i.first,i.second);
			low[x] = min(low[x],low[i.first]);
		} else {
			low[x] = min(low[x],dfn[i.first]);
		}
	}
	if(dfn[x] == low[x]){
		vector<int> t;
		t.push_back(x);
		while(stk.top() != x){
			t.push_back(stk.top());
			stk.pop();
		}
		stk.pop();
		ans.push_back(t);
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> u >> v;
		e[u].push_back(make_pair(v,i << 1));
		e[v].push_back(make_pair(u,i << 1 | 1));
	}
	for(int i = 1;i <= n;i++){
		if(!dfn[i]) tarjan(i,0);
	}
	cout << ans.size() << '\n';
	for(auto i : ans){
		cout << i.size() << " ";
		for(auto j : i) cout << j << " ";
		cout << '\n';
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