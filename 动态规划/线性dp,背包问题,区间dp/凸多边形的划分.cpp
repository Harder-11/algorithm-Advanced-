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
对边考虑,先处理a1an这条边
那么这条边引出的三角形会将凸多边形分成一个三角形和两个多边形
那么就明显是区间dp了,分为左边dp[i][k]和右边dp[k][j]两个部分
这道题数据纯狗市,s[i]<=1e9要写高精度(__int128都不一定能过)
*/

int n,s[N];
int dp[N][N];



void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> s[i];
    for(int i = n - 2;i >= 1;i--){
        for(int j = i + 2;j <= n;j++){
            dp[i][j] = INF;
            for(int k = i;k < j;k++){
                dp[i][j] = min(dp[i][j],dp[i][k] + dp[k][j] + s[i] * s[j] * s[k]);
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