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
差分的一般应用:
给定一个长度大小为N的数组,数组元素为整数,首先进行M次修改操作
每次给l~r区间范围的元素同时加上一个数字x,M次操作之后输出整个数组

差分数组的定义:
对于原数组a,我们定义si = Σ(j=1,i)aj,di = ai - a(i-1)
则s为数组a的前缀和数组,d数组为原数组的差分数组
*/

/*
题意:搭建一座宽度为n的大厦,大厦可以看做由n块宽度为1的积木组成,第i块的积木的最终高度是hi
搭建开始之前,没有任何积木(可以看出n块高度为0的积木),接下来每次操作,小朋友们可以选择一段
连续的区间[l,r],然后将第l块到第r块的所有积木的高度分别加1
问操作的最少次数

思路:直接求h数组的差分数组a,此时a中的元素 > 0的直接加上, <= 0的看做0
全部累加起来即可,因为差分代表的就是[l,r]的累加和
因为相当于每次h[l] +1,h[r+1] -1,那么差分数组的正数和和负数和绝对值是一样的
答案就是这个和
*/

int n,h[N],a[N];

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> h[i];
        a[i] = h[i] - h[i - 1];
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans += max(0,a[i]);
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