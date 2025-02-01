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
给定一个大小长度为n的正整数数组,查询M轮,每次询问一个区间所有元素的连续乘积
由于这个答案可能很大,你需要对1e9 + 7取余

本题很显然就是前缀和思想,只不过把加变成了乘
而此时查询的时候把减变成除,那么现在就要注意除法取模需要乘逆元
那么费马小定理 + 快速幂,logN的复杂度求逆元,可以接受
*/

ll n,m,a[N],pre[N];

ll power(ll a,ll b,ll mod){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

//费马小定理 + 快速幂求逆元
ll inv(ll a){
    return power(a,mod - 2,mod);
}

void solve(){
    cin >> n >> m;
    pre[0] = 1;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        pre[i] = pre[i - 1] * a[i] % mod; 
    }
    while(m--){
        int l,r;
        cin >> l >> r;
        ll c = inv(pre[l - 1]);
        cout << pre[r] * c % mod << '\n'; 
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