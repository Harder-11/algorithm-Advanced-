#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1005;
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
石子合并:
每次只能合并相邻的石子,得分就是合并后那一堆石子的个数
求:将N堆石头合并为1堆的最小和最大得分

思路:最后一次合并的本质就是将前若干堆石子合并之后的那一堆和后若干堆石子合并后的那一堆
合并起来,那么最后一次合并的最大值=前i个合并最大值+后j个合并最大值+合并得分
那么f[i][j]:i到j堆的所有石子合并成一堆所得的最大得分
f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+sum[i][j])
sum[i][j]表示i到j的石头的价值和,用前缀和快速求出(pre[j]-pre[i-1])
边界就是f[i][i] = 0;
*/

int n,a[N];
int dp[N][N],pre[N];

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) pre[i] = pre[i - 1] + a[i];
    memset(dp,INF,sizeof dp);
    for(int i = 0;i <= n;i++) dp[i][i] = 0;
    for(int l = 2;l <= n;l++){
        for(int i = 1;i <= n - l + 1;i++){
            int j = i + l - 1;
            for(int k = i;k < j;k++){
                dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j] + pre[j] - pre[i - 1]);
            }
        }
    }
    cout << dp[1][n] << '\n';
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