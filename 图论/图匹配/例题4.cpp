#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 505;
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
ZJOI 2007 https://www.luogu.com.cn/problem/P1129
一个方阵可以选择两行或者两列进行交换,问是否能做到方阵的主对角线全是黑(0代表白色,1是黑色)

显然,每一行和每一列只有一个有效点,那么只要每一行都有点且每一列都有点就满足条件
那么首先我们将每一行变成至少存在一个点,那么此时就只需要满足每列都至少有一个点即可
那么此时我们就可以把行当做二分图的左部,列当做二分图的右部,那么此时就把当前的1的位置(i,j),i向j连边
只要此时二分图的最大匹配为n,那么就满足条件,否则不满足
*/

int a[N][N],n,lnk[N],vis[N];
std::vector<int> e[N];
int res;

int dfs(int x){
	for(int i = 0;i < e[x].size();i++){
		int y = e[x][i];
		if(vis[y]) continue;
		vis[y] = 1;
		if(lnk[y] == 0 || dfs(lnk[y])){
			lnk[y] = x;
			return 1;
		}
	}
	return 0;
}

void solve(){
	cin >> n;
	res = 0;
	memset(lnk,0,sizeof lnk);
	memset(vis,0,sizeof vis);
	for(int i = 0;i < N;i++){
		e[i].clear();
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			cin >> a[i][j];
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			if(a[i][j] == 1){
			    e[i].push_back(j + n);
			 	e[j + n].push_back(i);
			}
		}
	}
	for(int i = 1;i <= n;i++){
		memset(vis,0,sizeof vis);
		res += dfs(i);
	}
	//cout << res << '\n';
	cout << (res == n ? "Yes" : "No") << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}