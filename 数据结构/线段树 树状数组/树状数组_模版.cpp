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
数组数组:
定义lowbit(x)表示二进制下的1的最低位
sum[x]是从r开始长度为lowbit(x)的区间和

树状数组的本质是前缀和,所以依赖前缀可减性
树状数组在单点修改具有局限性,比如带修改的前缀max,min问题中,修改必须具有单调性.
*/

int tr[N],n;

//lowbit取二进制下最低位的1(注意这里的1不是代表位置而是最低位1的值,比如4的lowbit就是4)
int lowbit(int x){
    return x & -x;
}

//树状数组查询操作
int query(int x){
    int res = 0;
    while(x){
        res += tr[x];
        x -= lowbit(x);
    }
    return res;
}

//树状数组修改操作
void change(int x,int val){
    while(x <= n){
        tr[x] += val;
        x += lowbit(x);
    }
}

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