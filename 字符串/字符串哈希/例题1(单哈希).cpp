#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1e9 + 7;
const int hs2 = 998244353;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
给出一个字符串S,|S| <= 100000
一共有Q <= 100000次询问:S[l1,r1]与S[l2,r2]是否相等
思路:使用哈希判断,判断两个子串是否相等,那么就要设计一种数据结构来快速求到区间范围的哈希值
H(S[l,r]) = (S[l]*Base^(r-l) + S[l+1]*Base^(r-l-1) + ....+S[r]) % mod;
那么利用前缀和,令F(i)=H(prefix[i])
F(l-1) = (S[1]*Base^(l-2)+S[2]*Base^(l-3)+....+S[l-1]) % mod;
F(r) = (S[1]*Base^(r-1)+S[2]*Base^(r-2)+...+S[r])%mod
那么[l,r]的区间和就是H(S[l,r]) = (F(r) - F(l - 1) * Base^(r - l + 1) % mod + mod) % mod
双哈希本质是一模一样的,只是要用另一个Hash值再验算一次,两次取交集即可
*/

string s;
int q,l1,r1,l2,r2;
int base = 233;
ll Hash[N];

ll power(ll a,ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = a * ans % hs1;
        a = a * a  % hs1;
        b >>= 1;
    }
    return ans;
}

void init(){
    for(int i = 1;i < s.size();i++){
        Hash[i] = ((ll)Hash[i - 1] * base + s[i]) % hs1;
    }
}

void solve(){

    cin >> s >> q;
    s = " " + s;
    init();
    while(q--){
        cin >> l1 >> r1 >> l2 >> r2;
        ll r = (Hash[r1] - (ll)Hash[l1 - 1] * power(base,r1 - l1 + 1) % hs1 + hs1) % hs1;
        ll rr =  (Hash[r2] - (ll)Hash[l2 - 1] * power(base,r2 - l2 + 1) % hs1 + hs1) % hs1;
        cout << (r == rr ? "YES" : "NO") << '\n';
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