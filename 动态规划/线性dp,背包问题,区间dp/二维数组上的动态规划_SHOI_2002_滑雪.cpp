#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs = 1331;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
在二维数组中进行动态规划
可以从高的位置向低处滑,可以从任意点开始滑,就是求二维数组中最长的下降序列
加上以(x,y)作为起点,那么就可以看上下左右四个点更矮的点滑,走能滑的最大长度+1
那么定义f[i][j]:从(i,j)滑下的最长路径长度
转移就是f[i][j]=max{f[i-1][j],f[i][j-1],f[i+1][j],f[i][j+1]}+1(只要大于转移的点即可)
本题适合用记忆化搜索,如果强行进行转移,需要排序会相对麻烦
*/

int a[105][105];
int n,m,f[105][105],ans;
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

//记忆化搜索更好写
int dfs(int x,int y){
    if(f[x][y]) return f[x][y];
    f[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[x][y] > a[nx][ny]){
            dfs(nx,ny);
            f[x][y] = max(f[x][y],f[nx][ny] + 1);
        }
    }
    return f[x][y];
}

void solve(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            ans = max(ans,dfs(i,j));
        }
    }
    cout << ans << '\n';
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