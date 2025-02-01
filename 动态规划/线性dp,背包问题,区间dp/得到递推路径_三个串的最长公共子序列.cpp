#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 305;
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
给你三个串,求其最长公共子序列,输出最长公共子序列长度及其方案
定义f[i][j][k]:第一个串的前i个字符,第二个串的前j个字符,第三个串的前k个字符组成的LCS
很显然,然后a[i] == b[j] == c[k],那么有转移方程f[i][j][k]=f[i-1][j-1][k-1]+1
否则,那么就是f[i][j][k]=max(f[i-1][j][k],f[i][j-1][k],f[i][j][k-1])三个串有一个串的字符必定没用
难点在:如何输出方案
模版是,在开f[i][j][k]的同时开一个数组lst[i][j][k],表示i,j,k这个状态由哪里转移过来
根据不同情况给lst赋值,以便在dfs的时候知道是从什么地方转移而得
最后从lst[n][m][l]开始往回推,如果lst[n][m][l]=f[n-1][m][l],那么就向(n-1,m,l)递归
*/
string a, b, c;
int dp[N][N][N];
//把lst定义为不同的值来记录转移,3就是代表a[i]==b[j]==c[k]
//1就是从j转移而来,0是由i转移而来,2是由j转移而来
int lst[N][N][N];

void dfs(int i, int j, int k){
    if(i == 0 || j == 0 || k == 0) return;
    if(lst[i][j][k] == 3){
        dfs(i - 1, j - 1, k - 1);
        cout << a[i];
    } else if(lst[i][j][k] == 0){
        dfs(i - 1, j, k);
    } else if(lst[i][j][k] == 1){
        dfs(i, j - 1, k);
    } else { 
        dfs(i, j, k - 1);
    }
}

void solve(){
    cin >> a >> b >> c;
    int n = a.size(), m = b.size(), l = c.size();
    a = " " + a;
    b = " " + b;
    c = " " + c;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= l; k++){
                if(a[i] == b[j] && a[i] == c[k]){
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                    lst[i][j][k] = 3;
                } else {
                    if(dp[i - 1][j][k] >= dp[i][j - 1][k] && dp[i - 1][j][k] >= dp[i][j][k - 1]){
                        dp[i][j][k] = dp[i - 1][j][k];
                        lst[i][j][k] = 0;
                    } else if(dp[i][j - 1][k] >= dp[i - 1][j][k] && dp[i][j - 1][k] >= dp[i][j][k - 1]){
                        dp[i][j][k] = dp[i][j - 1][k];
                        lst[i][j][k] = 1;
                    } else {
                        dp[i][j][k] = dp[i][j][k - 1];
                        lst[i][j][k] = 2;
                    }
                }
            }
        }
    }
    cout << dp[n][m][l] << '\n';
    dfs(n, m, l);
    cout << '\n';
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