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
本题是IOI1994年真题,此时动态规划刚刚被引入算法竞赛,可以被称为动态规划的始祖题
也是最经典的一道题

设有一个三角形的数塔,顶点结点被称为根节点,每个结点可以往左边或者右边走
三角形数塔给出以后,求第一层到最底层的路径最大值

思路:很明显,可以将三角数塔的数字全部往左边移,但是都不改变顺序
这样向左和向右就变成了向下和向右下走,那么就是在数组中(类似杨辉三角的形状)
a[i][j]可以走到a[i+1][j]和a[i+1][j+1]位置
那么对于每个结点f[i][j],是由f[i-1][j]和f[i-1][j-1]转移而得
那么方程就是f[i][j] = max(f[i-1][j],f[i-1][j-1])+a[i][j]
*/

int n,ans;
int a[105][105];
int f[105][105];

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= i;j++){
            cin >> a[i][j];
        }
    }
    f[1][1] = a[1][1];
    for(int i = 2;i <= n;i++){
        f[i][1] = a[i][1] + f[i - 1][1];
        for(int j = 2;j <= i;j++){
            f[i][j] = max(f[i - 1][j],f[i - 1][j - 1]) + a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        ans = max(ans,f[n][i]);
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