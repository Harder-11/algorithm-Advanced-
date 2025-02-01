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
在一个n * n矩阵当中找到一个子矩阵,使得该子矩阵的元素和最大
输出最大和即可
n <= 300
显然,n <= 300的情况就不能去暴力枚举左上角点和右下角点再利用二维前缀和求子矩阵
这样的复杂度是O(N^4)(枚举一个点的复杂度是N^2,两个点N^4)

那么如何降低复杂度?思路:枚举行
然后把第i行到第j行全部压缩到一行里面(利用每一列的前缀和即可)
然后压缩为一维数组就可以在O(n)的时间内求到最大的子数组和
而枚举i和j行的时间复杂度是O(n^2),总复杂度就是O(n^3),可以通过
这里的dp[i]仍然是选第i个元素(必选)的最大子数组和
*/
int n,a[N][N],ans;
int pre[N][N];

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            pre[i][j] = pre[i - 1][j] + a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++){
            int cur[n + 1],dp[n + 1];
            for(int k = 1;k <= n;k++){
                cur[k] = pre[j][k] - pre[i - 1][k];
            }
            memset(dp,0,sizeof dp);
            for(int k = 1;k <= n;k++){
                dp[k] = max(dp[k - 1] + cur[k],dp[k]);
            }
            for(int k = 1;k <= n;k++){
                ans = max(ans,dp[k]);
            }
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