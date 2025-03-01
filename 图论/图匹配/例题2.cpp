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
CF 1139E *2400
在一所学校里面有n名学生和m个社团,社团被编号为1~m,第i个学生有一个能量值pi
且属于社团ci(每个学生恰好属于一个社团)
学校要举行为期d天的活动,每天学校要进行一场程序设计比赛,校长将从每个社团里面选出一个人
(如果某个社团没有人就不选)组成一个队,令队里面的学生的能力值的集合为S,则给队的总能力值为mex(S)
但是由于学业繁忙,第i天的时候,第ki个学生会离开社团(校长选这一天参加笔袋的学生之前)
校长希望知道对于活动的每一天,他可能选出的队伍的总能力值最大是多少?

思路:这道题是二分图匹配匈牙利算法的巧妙运用
我们考虑倒序回答,那么删除就变成了增加
然后我们把能力值作为二分图的左部,社团作为右部
对于每个当前存在的关系就连一条无向边
每次回答相当于从小到大对每一个左部图点进行匹配,直到无法匹配,此时无法匹配的即为当前的答案
之后每添加一条边在上次匹配的图上继续匹配即可
*/

std::vector<int> e[N];
int n,m,d,a[N],b[N],c[N],ans[N],vis[N],w[N],f[N];

int dfs(int x){
	for(int i = 0;i < e[x].size();i++){
		int y = e[x][i];
		if(vis[y]) continue;
		vis[y] = 1;
		if(f[y] == -1 || dfs(f[y])){
			f[y] = x;
			return 1;
		}
	}
	return 0;
}

void solve(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) cin >> b[i];
	cin >> d;
	for(int i = 1;i <= d;i++) cin >> c[i];
	for(int i = 1;i <= d;i++) w[c[i]] = 1;
	for(int i = 1;i <= n;i++){
		if(!w[i]){
			if(a[i] > m) continue;
			e[a[i]].push_back(b[i] + m);
			e[b[i] + m].push_back(a[i]);
		}
	}
	memset(f,-1,sizeof f);
	for(int i = d;i;i--){
		for(int j = ans[i + 1];j <= m;j++){
			memset(vis,0,sizeof vis);
			if(!dfs(j)){
				ans[i] = j;
				break;
			}
		}
		if(a[c[i]] > m) continue;
		e[a[c[i]]].push_back(b[c[i]] + m);
		e[b[c[i]] + m].push_back(a[c[i]]);
	}
	for(int i = 1;i <= d;i++){
		cout << ans[i] << '\n';
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