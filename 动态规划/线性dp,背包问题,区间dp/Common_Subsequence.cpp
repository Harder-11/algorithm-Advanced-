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
最长公共子序列问题
比如输入的字符串分别是:abcfbc abfcab
由于最后一个元素不一样,那么此时一定不会讲两个字符串的最后一个元素都选
那么就是要知道x串的前i个字母和y串的前j个字母的最长公共子序列有多长,用f[i][j]表示
那么如果x[i]=y[j],f[i][j]=f[i-1][j-1]+1
如果x[i]!=y[j],f[i][j]=max(f[i-1][j],f[i][j-1]);
初始化的时候,f[1][1]=(a[1]==b[1]?1:0)
*/

char s[N],t[N];
int dp[N][N];

void solve(){
    cin >> (s + 1) >> (t + 1);
    memset(dp,0,sizeof dp);
    int n = strlen(s + 1);
    int m = strlen(t + 1);
    dp[1][1] = (s[1] == t[1] ? 1 : 0);
    for(int i = 2;i <= n;i++){
        for(int j = 2;j <= m;j++){
             if(s[i] == t[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j],dp[i][j - 1]);
        }
    }
    cout << dp[n][m] << '\n';
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