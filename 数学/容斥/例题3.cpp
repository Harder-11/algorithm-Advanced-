#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 12345678;
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
有一个n行m列的整数矩阵,其中1到nm之间的每个整数恰好出现一次,如果一个格子比所有相邻格子
(相邻是指有公共边或者公共顶点)都小,我们说这个格子是局部极小值
给出所有局部极小值的位置,判断有多少个可能的矩阵,答案模12345678
1 <= n <= 4,1 <= m <= 7

思路:从小到大放数,则一个普通格子只有等它周围的格子都放完数了才能放,在不考虑本题中'.'的
格子不能是蓄水池的条件下,我们可以写出记忆化搜索的状态转移方程:
f[k][s] = sum{f[k-1][s']},其中sum为求和,k为放到了第几个数,s为蓄水池的状态,s'表示由s少放一个蓄水池能达到的状态
最后f[n * m][s全放]记为题解
本题的难点在于"."的格子不能是蓄水池,我们可以用容斥原理来解决
我们假设在原来的基础上有增加了p个蓄水池,若p是奇数,则ans减去f[n*m][s全放],否则加上
*/

int n,m,ans;
int f[1 << 8][30],x[8],y[8],tp;
bool vis[8][8];
char mat[8][8];

bool in(int x,int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}

int calc(){
	tp = 0;
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(mat[i][j] == 'X'){
				x[tp] = i;
				y[tp++] = j;
			}
		}
	}
	memset(f,0,sizeof f);
	f[0][0] = 1;
	for(int s = 0;s < (1 << tp);s++){
		memset(vis,1,sizeof vis);
		for(int i = 0;i < tp;i++){
			if(!(s & (1 << i))){
				for(int dx = -1;dx <= 1;dx++){
					for(int dy = -1;dy <= 1;dy++){
						if(in(x[i] + dx,y[i] + dy)){
							vis[x[i] + dx][y[i] + dy] = 0;
						}
					}
				}
			}
		}
		int cnt = 0;
		for(int i = 0;i < n;i++){
			for(int j = 0;j < m;j++){
				if(vis[i][j]){
					cnt++;
				}
			}
		}
		for(int i = 0;i <= cnt;i++){
			if(f[s][i]){
				f[s][i + 1] = (f[s][i + 1] + f[s][i] * (cnt - i) % mod) % mod;
				for(int j = 0;j < tp;j++){
					if(!(s & (1 << j))){
						f[s | (1 << j)][i + 1] = (f[s | (1 << j)][i + 1] + f[s][i]) % mod;
					}
				}
			}
		}
	}
	return f[(1 << tp) - 1][n * m];
}

void dfs(int x,int y,int k){
	if(x >= n) ans = (ans + k * calc()) % mod;
	else if(y >= m) dfs(x + 1,0,k);
	else {
		dfs(x,y + 1,k);
		bool f = 1;
		//找到此时(x,y)周围有X就进行容斥
		for(int dx = -1;dx <= 1;dx++){
			for(int dy = -1;dy <= 1;dy++){
				if(in(x + dx,y + dy) && mat[x + dx][y + dy] == 'X'){
					f = 0;
				}
			}
		}
		//进行容斥就将此位置置为X,然后dfs(x,y+1,-k)
		if(f){
			mat[x][y] = 'X';
			dfs(x,y + 1,-k);
			mat[x][y] = '.';
		}
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			cin >> mat[i][j];
		}
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(mat[i][j] == 'X'){
				for(int dx = -1;dx <= 1;dx++){
					for(int dy = -1;dy <= 1;dy++){
						if((dx || dy) && in(i + dx,j + dy) && mat[i + dx][j + dy] == 'X'){
							return;
						}
					}
				}
			}
		}
	}
	ans = 0;
	dfs(0,0,1);
	cout << (ans + mod) % mod << '\n';
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