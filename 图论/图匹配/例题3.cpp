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
ZJOI2009 https://www.luogu.com.cn/problem/P2055
非常明显的一个二分图问题,我们把学生当做左集合,床当做右集合
那么连边就是把学生和其所有认识的人的床都连边即可
*/

int e[105][105];
int lnk[N],vis[N],rn[N],ho[N];
int ans,n;

bool dfs(int x){
	for(int i = 1;i <= n;i++){
		if(vis[i] == 0 && rn[i] == 1 && e[x][i] == 1){
			vis[i] = 1;
			if(lnk[i] == 0 || dfs(lnk[i])){
				lnk[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

void solve(){
	cin >> n;
	ans = 0;
	memset(vis,0,sizeof vis);
	memset(lnk,0,sizeof lnk);
	memset(rn,0,sizeof rn);
	memset(ho,0,sizeof ho);
	memset(e,0,sizeof e);
	for(int i = 1;i <= n;i++){
		cin >> rn[i];
	}
	for(int i = 1;i <= n;i++){
		cin >> ho[i];
		if(rn[i] == 0){
			ho[i] = 1;
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			cin >> e[i][j];
		}
		if(rn[i] == 1){
			e[i][i] = 1;
		}
	}
	for(int i = 1;i <= n;i++){
		memset(vis,0,sizeof vis);
		if((rn[i] == 0 || ho[i] == 0) && (!dfs(i))){
			cout << "T_T" << '\n';
			return;
		}
	}
	cout << "^_^" << '\n';
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