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
(CF940E)
给你一个长度为n的数列a和一个整数c,你可以把它们分为任意长度的若干段
每一段可以去掉前k/c小的数字(k是这一段的长度),求最后剩下的数的和最小值是多少
1<=n,c<=1e5
一个很明显的贪心:分段的长度只可能是1或者c(即使是c的倍数也不合理)
因为如果取1~c之间的数作为长度那无法去掉元素,无意义
如果取c的倍数比如2c,那么就可能去掉的两个元素都在同一个c长度的区间里面,这样就不如
分开取两个c长度的区间了
那么如果是定义f[i]:前i个数,那么就有
f[i] = f[i-1] + a[i](分段长度为1)
f[i] = f[i-c] + pre[i] - pre[i-c] - min{i-c+1~i}(分段长度为c)
但是这样时间是O(nc)无法通过(可以优化枚举长度为c区间的最小值-->立马想到了定长的滑动窗口问题)
那么使用单调队列优化定长滑动窗口即可优化到O(nlogc)的时间复杂度,可以通过(注意在deque里面同时记录下标,否则存入之后不知道每个数下标是多少)
(当然线段树思维量更小,直接写维护区间最小值的板子即可,但是谁想写这么长的代码)

*/
ll n,c,a[N],pre[N],f[N];
deque<pair<int,int>> q;

void solve(){
    cin >> n >> c;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    for(int i = 1;i <= n;i++){
        if(q.empty()) q.push_back({a[i],i});
        else {
            while(!q.empty() && a[i] < q.back().first){
                q.pop_back();
            }
            q.push_back({a[i],i});
            if(i - q.front().second + 1 > c){
                q.pop_front();
            }
        }
        if(i >= c){
            f[i] = min(f[i - 1] + a[i],f[i - c] + pre[i] - pre[i - c] - q.front().first);
        } else {
            f[i] = f[i - 1] + a[i];
        }
    }
    cout << f[n] << '\n';
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