#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1331;
const int hs2 = 998244353;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
给出一个字符串S,每次操作可以删除最末端的一个字符,最少进行多少次操作可以得到一个回文串?
思路:题目等价于求最长的回文前缀,对于回文串,正串和反串是相同的,可以用Hash判定
枚举答案长度进行验证即可
那么就是将R(s)定义为S翻转串,那么就是只要S的前i个字符串哈希和R(s)后i个串的字符串哈希一样
那么就是回文串
*/

int base = 233;
ll h1[N],h2[N],n,ans;
string s,r;

ll power(ll a,ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % hs1;
        a = a * a % hs1;
        b >>= 1;
    }
    return ans;
}

void init(){
    for(int i = 1;i <= n;i++){
        h1[i] = ((ll)h1[i - 1] * base + s[i]) % hs1;
        h2[i] = ((ll)h2[i - 1] * base + r[i]) % hs1;
    }
}

void solve(){
    cin >> s;
    n = s.size();
    string t = s;
    reverse(t.begin(),t.end());
    r = t;
    r = " " + r,s = " " + s;
    init();
    for(int i = n;i >= 1;i--){
        ll r = h1[i] % hs1;
        ll rr = (h2[n] - h2[n - i] * power(base,i) % hs1 + hs1) % hs1;
        if(r == rr){
            ans = n - i;
            break;
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