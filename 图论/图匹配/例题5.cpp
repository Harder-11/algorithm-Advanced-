#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 105;

/*
P10943 https://www.luogu.com.cn/problem/P10943
一个二分图最大权完美匹配就结束了,把人和house分为两部
每个人和每个house都连边,找最小权即可(把最大权反过来求,左部-delta,右部+delta)
*/

int n,m;
char mat[N][N];
std::vector<pair<int,int>> house;
int visx[N],visy[N],lnk[N],lx[N],ly[N],cnt,w[N][N]; 
int r;

bool dfs(int x){
	visx[x] = 1;
	for(int i = 1;i <= r;i++){
		if(!visy[i] && lx[x] + ly[i] == w[x][i]){
			visy[i] = 1;
			if(lnk[i] == 0 || dfs(lnk[i])){
				lnk[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

void solve(){
	cin >> n >> m;
	if(n + m == 0) return;
	memset(visx,0,sizeof visx);
	memset(visy,0,sizeof visy);
	memset(ly,0,sizeof ly);
	memset(lnk,0,sizeof lnk);
	memset(w,0,sizeof w);
	house.clear();
	cnt = r = 0;
	memset(lx,INF,sizeof lx);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> mat[i][j];
			if(mat[i][j] == 'H'){
				house.push_back({i,j});
			}
		}
	}
	r = house.size();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(mat[i][j] == 'm'){
				int v = 0;
				cnt++;
				for(auto x : house){
					int dis = abs(x.first - i) + abs(x.second - j);
					lx[cnt] = min(lx[cnt],dis);
					w[cnt][++v] = dis;
				}

			}
		}
	}
	for(int i = 1;i <= cnt;i++){
		while(1){
			memset(visx,0,sizeof visx);
			memset(visy,0,sizeof visy);
			if(dfs(i)) break;
			int d = INF;
			for(int j = 1;j <= cnt;j++){
				if(visx[j]){
					for(int k = 1;k <= r;k++){
						if(!visy[k]){
							d = min(d,w[j][k] - (lx[j] + ly[k]));
						}
					}
				}
			}
			for(int j = 1;j <= cnt;j++){
				if(visx[j]) lx[j] += d;
			}
			for(int k = 1;k <= r;k++){
				if(visy[k]) ly[k] -= d;
			}
		}
	}
	ll ans = 0;
	for(int i = 1;i <= cnt;i++) ans += lx[i];
	for(int i = 1;i <= r;i++) ans += ly[i];
	cout << ans << '\n';
	solve();
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