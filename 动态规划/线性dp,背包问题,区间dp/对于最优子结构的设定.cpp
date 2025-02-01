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
例题:
有N个点,从1一直到N依次排序,两两点直接由若干的路径,长度分别是d1,d2...dm
求从1到N的路径长度和 % 4最小

思考:该如何确定最优子结构
加上我们定义f[i]:走到i位置%4的最小路径,此时就不满足定义了
因为从1号点开始,我们就一直选的%4的最小值,但这不一定就满足整个路径%4最小
因为开始某些看起来更劣的路径在加上后续路径之后可能使得余数更小

正确思路:余数不管是几,都对后续有影响,不能以余数作为转移的定义
由于每个余数都有用,又观察到%4,那么可以直接枚举出每个点的余数(只可能是0,1,2,3这四种情况)
那么定义f[i][0,1,2,3]作为从起点走到i,余数可不可能为j
那么可以通过递推依次求到每个点的可以根据上一个点的余数情况,得到当前点的余数有哪些

具体的题目可能出现在图上dp的题目当中

动态规划的使用基本条件:满足无后效性,当前的决策和后续和未来的决定都没有关系
*/

void solve(){}

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