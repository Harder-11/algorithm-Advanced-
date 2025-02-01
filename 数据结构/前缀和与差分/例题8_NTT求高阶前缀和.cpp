#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 300005;
const int mod = 998244353;
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
我们给定一个长度大小为N的数组a和一个参数k
当k > 0,输出对a做k次前缀和的结果
当k = 0,直接输出a数组
当k < 0,输出对a做k次差分的结果
为了避免数字过大,对998244353取模,也就是输出的数字都在[0,998244353)
其中,1 <= N <= 1e5,-1e18 <= k <= 1e18

首先引入高阶前缀和
对于a[N][N]数组做前缀和,每个格子的值a[i][j] = a[i - 1][j] + a[i][j - 1];
那么显然就是以下的数:
1 1 1 1 1
1 2 3 4 5
1 3 6 10 15.....
对于每一行的数从左到右依次是C(k,0),C(k+1,1),C(k+2,2).....(k=0,1,2...)
那么我们加速运算前缀和,比如要求1 2 3 4 6的二阶前缀和
假设有两个数组a,b
我们定义卷积ck = Σai * bj,其中有i + j = k
那么计算二阶前缀和就是用(1 2 3 4 6) * (1 2 3 4 5)做卷积
那么就能直接得到[1 4 10 20 36],用NTT求卷积,时间复杂度是O(NlogN)
*/

ll wn[55],g = 3,n,a[N],inv[N],ki[N],k;

ll power(ll a,ll b){
    ll res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void ntt(ll *a,int len,int f){
    ll i,j = 0,t,k,w,id;
    for(i = 1;i < len - 1;i++){
        for(t = len;j ^= t >>= 1,~j & t;);
        if(i < j) swap(a[i],a[j]);
    }
    for(i = 1,id = 1;i < len;i <<= 1,id++){
        t = (i << 1);
        for(j = 0;j < len;j += t){
            for(k = 0,w = 1;k < i;k++,w = w * wn[id] % mod){
                ll x = a[j + k],y = w * a[j + k + i] % mod;
                a[j + k] = (x + y) % mod;
                a[j + k + i] = (x - y + mod) % mod;
            }
        }
    }
    if(f){
        for(i = 1,j = len - 1;i < j;i++,j--) swap(a[i],a[j]);
        ll inv = power(len,mod - 2);
        for(int i = 0;i < len;i++) a[i] = a[i] * inv % mod;
    }
}

void mul(ll *a,ll *b,int l1,int l2){
    int len,i;
    for(len = 1;len <= l1 + l2;len <<= 1);
    for(i = l1 + 1;i <= len;i++) a[i] = 0;
    for(i = l2 + 1;i <= len;i++) b[i] = 0;
    ntt(a,len,0),ntt(b,len,0);
    for(i = 0;i < len;i++) a[i] = a[i] * b[i] % mod;
    ntt(a,len,1);
}

void init(ll n){
    inv[0] = inv[1] = 1;
    for(int i = 2;i <= n;i++){
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    }
}

void get_wn(){
    for(int i = 0;i < 25;i++){
        wn[i] = power(g,(mod - 1) / (1ll << i));
    }
}

void get_ki(ll k,int len){
    //这里k能直接对mod取模是因为在模一个质数的前提下,N阶前缀和的循环节长度就是mod
    k = (k % mod + mod) % mod;
    ki[0] = 1;
    for(int i = 1;i < len;i++){
        ki[i] = ki[i - 1] * inv[i] % mod * ((k + i - 1) % mod) % mod;
    }
}

void solve(){
    get_wn();
    init(1e5);
    cin >> n >> k;
    get_ki(k,n);
    for(int i = 0;i < n;i++) cin >> a[i];
    mul(a,ki,n,n);
    for(int i = 0;i < n;i++){
        cout << a[i] << " ";
    }
    cout << "\n";
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