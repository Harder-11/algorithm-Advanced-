#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1e9 + 9;
const int hs2 = 998244353;
const int base = 233;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
/*
牛牛有一颗大小为n的神奇Link-Cut数组
数组上的每一个节点都有两种状态，一种为link状态，另一种为cut状态
数组上任意一对处于link状态的无序点对（即(u,v)和(v,u)被认为是同一对）
会产生dis(u,v)的link能量，dis(u,v)为数组上u到v的距离。
我们定义整个数组的Link能量为所有处于link状态的节点产生的link能量之和。
一开始数组上每个节点的状态将由一个长度大小为n的01串给出,'1'表示Link状态，'0'表示Cut状态。
牛牛想要知道整个数组的Link能量,答案对1e9+7取模

思路:题意本质就是01字符串中两两1之间的距离和是多少
我们转化为前面的1对后面的1产生的影响,显然前面1对后续数组的影响是一个等差数列
那么假设1的位置是i,那么i+1的位置就+1,因为他不会对自己做贡献,是在后面一个位置才开始有贡献,然后进行两次前缀和即可
(差分数组代表的影响是可以叠加的,所以可以直接求ans)
*/

int n;
string s;
ll ans,sum[N];

void solve(){
    cin >> n >> s;
    s = " " + s;
    for(int i = 1;i <= n;i++){
        if(s[i] == '1') sum[i + 1]++;
    }
    for(int i = 2;i <= n;i++) sum[i] = (sum[i] + sum[i - 1]) % mod;
    for(int i = 2;i <= n;i++) sum[i] = (sum[i] + sum[i - 1]) % mod;
    for(int i = 2;i <= n;i++){
        if(s[i] == '1'){
            ans = (ans + sum[i]) % mod;
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