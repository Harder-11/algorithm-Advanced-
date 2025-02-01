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
区间dp:括号匹配
给出一个括号序列,求其中匹配的括号数
很明显,可以从大范围往小范围转移,首先看最后匹配到的括号
f[i][j]:表示ai...aj的串当中,有多少个已经匹配的括号
每次枚举分割点k即可(i <= k < j)
dp[i][j]=max(dp[i][j],dp[i][k] + dp[k + 1][j]);
每次循环还需判断s[i]和s[j]是否匹配
如果匹配,那么则有dp[i][j]=dp[i+1][j-1]+2,否则就是dp[i][j]=dp[i+1][j-1]
                      
*/

int dp[N][N],n;
string s;

void solve(){
    cin >> n >> s;
    s = " " + s;
    for(int l = 2;l <= n;l++){
        for(int i = 1;i + l - 1 <= n;i++){
            int j = i + l - 1;
            if((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')){
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = dp[i + 1][j - 1];
            }
            for(int k = i;k < j;k++){
                dp[i][j] = max(dp[i][j],dp[i][k] + dp[k + 1][j]);
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