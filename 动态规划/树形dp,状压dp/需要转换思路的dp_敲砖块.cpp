#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 55;
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
敲砖块:要想敲掉某一块砖,必须把覆盖它上面的所有砖块敲掉才行
一共有n层砖,要敲掉m块砖,问价值总和最大是多少(墙是倒三角形状)
0 <= n <= 50,1 <= m <= 500

由于本题每块砖是被上一块砖给限制了,那么枚举行就不成立,很难去表示上一行的状态(n=50,状态压缩会超时超空间)
那么定义f[i][j][k]表示在第j列被敲掉的砖块中,以i为最大行编号,并且在这之前总共敲掉k块砖的最大得分
那么对于状态(i,j)所有满足0<=t<=i+1的状态(t,j-1)都可以转移(就是前一列最多可以敲到i+1行去)
那么状态转移方程就是f[i][j][k]=max(f[t][j-1][k-i]+pre[i][j]);
答案为max(f[1][n][m],[0][n][m])(最后一列敲还是不敲)
*/

int n,m;
int a[N][N],pre[N][N];
int f[55][55][3200];

void solve(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n - i + 1;j++){
            cin >> a[i][j];
            pre[i][j] = pre[i - 1][j] + a[i][j];
        }
    }
    for(int j = 1;j <= n;j++){
        for(int i = 0;i <= n;i++){
            for(int k = i;k <= m;k++){
                for(int t = 0;t <= i + 1;t++){
                    f[i][j][k] = max(f[t][j - 1][k - i] + pre[i][j],f[i][j][k]);
                }
            }
        }
    }
    cout << max(f[1][n][m],f[0][n][m]) << '\n';
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