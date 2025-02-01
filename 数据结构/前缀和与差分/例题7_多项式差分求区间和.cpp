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
差分维护静态多项式
现在有一个长度大小为N的数组,数组中有一些非负整数,请你完成区间加若干次多项式的操作
最后进行若干次区间查询和的操作
具体来说就是会进行M次操作,每次将会给出一个k次多项式f(x) = c0x^k + c1x^(k-1) + .... + c(k-1)x + ck
以及一段需要操作的区间[l,r],然后你需要对al + f(1),a(l+1) + f(2),以此类推
也就是对目标区间的第一个数字 + f(1),第二个数字 + f(2)
在做完这些操作之后,还会进行Q次查询操作,每次查询一段[l,r]的区间元素和
答案对1e9 + 7取模

数学定理:最高次项为n次的n阶多项式做n+1阶差分之后余项为常数
*/

int n,m,q,k;
ll l,r,a[N],ki[N],co1[N],co2[N];

//用cnt来代表加cnt次前缀和/差分
void pre_sum(ll a[],int len,int cnt = 1){
    while(cnt--){
        for(int i = 1;i <= len;i++){
            a[i] = (a[i] + a[i - 1]) % mod;
        }
    }
}

void sub(ll a[],int len,int cnt = 1){
    while(cnt--){
        for(int i = len;i;i--){
            a[i] -= a[i - 1];
            if(a[i] < 0) a[i] += mod;
        }
    }
}

//实现多项式的计算,a就是多项式的系数,k就是最高次
ll f(ll x,ll a[],int k){
    ll res = 0,base = 1;
    for(int i = k;i >= 0;i--){
        res = (res + base * a[i] % mod) % mod;
        base = base * x % mod;
    }
    return res;
}

//g函数是为了消除后续的影响,因为是求到[l,r]的前缀和
//g函数就是为了消除[r + 1,n]这一段的影响
//假设要求的那一段长度是len,那么最后答案减去f(x + len)即可
ll g(ll x,ll a[],int k,ll l,ll r){
    //这里是防止取模到负数,本质是-f + mod然后%mod防止负数的出现
    return (mod - f(x + r - l + 1,a,k)) % mod;
}

void solve(){
    cin >> n >> m >> q;
    //读入的是多项式初始的系数
    for(int i = 1;i <= n;i++) cin >> a[i];
    //k最大是6,那么直接进行6次高阶差分即可,仍然可以得到后缀全是0的差分数组
    sub(a,n,6);
    while(m--){
        cin >> l >> r >> k;
        for(int i = 0;i <= k;i++){
            cin >> ki[i];
        }
        for(int i = 1;i <= 10;i++){
            co1[i] = f(i,ki,k);
            co2[i] = g(i,ki,k,l,r);
        }
        sub(co1,10,6);
        sub(co2,10,6);
        for(int i = 1;i <= 10;i++){
            a[l + i - 1] = (a[l + i - 1] + co1[i]) % mod;
            a[r + i] = (a[r + i] + co2[i]) % mod;
        }
    }
    //做6阶差分之后然后进行7阶前缀和即可
    //类比二次的多项式,做两次差分和三次前缀和得到平方数列
    pre_sum(a,n,7);
    while(q--){
        cin >> l >> r;
        cout << ((a[r] - a[l - 1]) % mod + mod) % mod << '\n';
    }
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