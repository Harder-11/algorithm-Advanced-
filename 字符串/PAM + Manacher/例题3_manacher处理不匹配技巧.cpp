#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 500005;
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
给出一个01串,求最长的反对称子串
反对称串的定义为:将R(T)逐位取反之后等于原串T,则T是一个反对称串,比如010101
其中|S| <= 500000

思路:本题相比于回文串就是把等号变成不等,子串必须是010101类似的串,关于不对称中心都不对称即可
*/

int n,d[N << 1],tot = 1;
ll ans;
char s[N],ss[N << 1],to[N << 1];


void solve(){
    cin >> n >> (s + 1);
    ss[0] = '$',ss[1] = '#';
    for(int i = 1;i <= n;i++){
        ss[++tot] = s[i];
        ss[++tot] = '#';
    }
    //这样用一个to数组同时解决了#要相同,01要不同的问题,将相同和不同统一了
    to['1'] = '0',to['0'] = '1',to['#'] = '#',to['$'] = '$';
    //反对称串只可能是偶数长度,所以i += 2
    for(int i = 1,r = 1,c = 1,len;i <= tot;i += 2){
        d[i] = i < r ? min(r - i,d[2 * c - i]) : 1;
        while(ss[i + d[i]] == to[ss[i - d[i]]]) d[i]++;
        if(d[i] + i > r){
            r = d[i] + i;
            c = i;
        }
        ans += d[i] / 2;
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