#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 20005;
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
01背包问题:一个容量为V的箱子,放入若干物品(n <= 30)
每个物品有一个体积,要求n个物品选若干个装入箱子,使得箱子的剩余容量最小
很明显,本题不能直接选最大或者最小的元素(类似与%4那道题),大和小都与后面的元素是相关的
那么我们使用动态规划,bool数组f[i][j]表示前i个物品能否放满体积为j的背包
枚举最后一次决策---第i个物品放还是不放
f[i][j] = f[i-1][j] || f[i-1][j-a[i]]
初识值f[i][j]=0,f[0][0]=1(0个物品塞满体积为0的背包初识就是1)
最后再倒序扫一遍dp,遇到不是0的位置直接返回即可

由于本题是每一行的f值只与上一行有关,那么我们就用滚动数组f[2][V]来减小空间使用
注意本题的细节:因为转移方程有一个j - a[i],但是我们不能直接j从v[i]开始遍历到v
因为当j < a[i]的时候,他是直接继承的f[i-1][j]
当然,本题也可以就地滚动,j从v到a[i]遍历即可,因为a[i]前面的是直接继承上一行
那么一维数组就不用管了,自动就是上一行的内容,修改a[i]之后的位置即可
*/ 

int v,n;
int a[35];
int f[2][N];

void solve(){
    cin >> v >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    f[0][0] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= v;j++){
            if(j >= a[i]){
                f[i % 2][j] = f[(i - 1) % 2][j] || f[(i - 1) % 2][j - a[i]];
            } else f[i % 2][j] = f[(i - 1) % 2][j];
        }
    }
    int ans = 0;
    for(int i = v;i >= 0;i--){
        if(f[n % 2][i] == 1){
            ans = i;
            break;
        }
    }
    cout << v - ans << '\n';
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