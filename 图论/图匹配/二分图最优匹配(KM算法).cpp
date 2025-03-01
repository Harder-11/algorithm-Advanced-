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
KM算法
最优匹配是建立在完美匹配的基础上的,如果不存在完美匹配,那么本算法失效
(但是,我们可以人为连一些权值为0的边,甚至加点,使得没有匹配的结点都有一个虚假的匹配)

算法思路:最开始把每个左边结点连的权值最大的边视为有效边,在匹配的过程中如果某个点找不到匹配点的话
则选择一些无效边改成有效边继续去匹配,选择的这些无效边其实其实是换掉的原来的某条有效边
那么晚我们肯定选换掉代价最小的
具体操作:
给每个点预设一个顶标,只有两个端点的顶标加起来等于边权的边,我们才认为是有效边
即L[x] + R[y] == w[x][y]的时候才认为是有效边
最开始的时候左集合的每个点的顶标为它连出去权值最大边的权值,右集合的每个点顶标为0
当匹配失败的时候,我们遍历之前的左集合尝试匹配过的点,在他们的连向右集合未遍历的点的边种找一个
与顶标差值最小的边,即delta=w[x][y]-L[x]-R[y]最小的边(找出一条损失最小的增广路)
找到之后修改顶标:左侧所有遍历过的点减去delta,右边所有遍历过的点加上delta,这样原来的有效边还是有效边
而且新加的边也已经加上了

*/

//代码如下
int lx[N],ly[N],visx[N],visy[N],lnk[N];
int n,m;
int w[N][N];

int dfs(int x){
	visx[x] = 1;
	for(int i = 1;i <= m;i++){
		if(!visy[i] && lx[x] + ly[i] == w[x][i]){
			visy[i] = 1;
			if(lnk[i] == -1 || dfs(lnk[i])){
				lnk[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

void calc(){
	memset(ly,0,sizeof ly);
	memset(lx,0,sizeof lx);
	memset(lnk,-1,sizeof lnk);
	for(int i = 1;i <= n;i++){
		for(int j = 1; j <= n;j++){
			lx[i] = max(w[i][j],lx[i]);
		}
	}
	for(int i = 1;i <= n;i++){
		while(1){
			memset(visx,0,sizeof visx);
			memset(visy,0,sizeof visy);
			if(dfs(i)) break;
			int d = 0x7f7f7f7f;
			for(int j = 1;j <= n;j++){
				if(visx[j]){
					for(int k = 1;k <= m;k++){
						if(!visy[k]){
							d = min(d,lx[j] + ly[k] - w[j][k]);
						}
					}
				}
			}
			if(d == 0x7f7f7f7f){
				cout << "No perfect interaction" << '\n';
				return;
			}
			for(int j = 1;j <= n;j++){
				if(visx[j]) lx[j] -= d; 
			}
			for(int j = 1;j <= m;j++){
				if(visy[j]) ly[j] += d;
			}
		}
	}
}

void solve(){
	cin >> n >> m;
	//假设题目是邻接矩阵给的边权
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> w[i][j];
		}
	}
	calc();
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