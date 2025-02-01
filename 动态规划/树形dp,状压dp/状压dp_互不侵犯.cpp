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
状态压缩dp(实际是一个轮廓线dp)
在N * N的棋盘内放K个国王,使他们不能互相攻击,问有多少种方案
1 <= N <= 9,0 <= K <= N * N
每放一个国王,都要检查其左侧和上方的国王的状态是否冲突
本题可以通过一行一行地拓展,根据上一行的状态可以得到当前行是否合法
由于每一行的格子小于等于9个,每一个格子又只有两种状态,那么假设放了国王为1
不放国王为0,那么很显然,每一行的一个状态就是01串,显然不会超过111111111
用一个int表示每一行的状态,那么怎样的状态是合法的呢?
---没有两个相邻的1-->(x & (x << 1)) == 0
如果知道上一行的状态是x,当前行的状态是y,xy满足什么条件才是合法的呢?
-->(x & y) == 0 && (x & (y << 1)) == 0 && (x & (y >> 1)) == 0
那么现在就可以确定一个状态:
f[i][j][k]表示第i行的状态为k,并且已经放了j个国王的方案数
确定状态转移方程f[i][j][k]+=f[i-1][j-num[k]][p]
其中有((k & p) == 0 && k & (p << 1) == 0 && k & (p >> 1) == 0)
num[k]表示的是k状态的国王数
对于每一行和上一行的状态就暴力枚举即可(2^(2n))
时间复杂度O(2^n * 2^n * n^3)

*/

int n,k;
ll f[10][100][1 << 10];

void solve(){
    cin >> n >> k;
    f[0][0][0] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= k;j++){
            for(int l = 0;l <= (1 << n) - 1;l++){
                if((l & (l << 1)) != 0) continue;
                for(int lst = 0;lst <= (1 << n) - 1;lst++){
                    if((lst & (lst << 1)) != 0) continue;
                    if((lst & l) == 0 && (lst & (l << 1)) == 0 && (lst & (l >> 1)) == 0 && j >= __builtin_popcount(l)){
                        f[i][j][l] += f[i - 1][j - __builtin_popcount(l)][lst];
                    }
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0;i <= (1 << n) - 1;i++){
        ans += f[n][k][i];
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