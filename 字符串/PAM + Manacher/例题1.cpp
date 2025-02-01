#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
const int mod = 19930726;
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
给出一个字符串S,|S| <= 1000000,求前k大的奇回文子串长度的乘积,k<=1000000000
用manacher算法处理每个位置的回文半径,于是每个位置代表了一个系列的回文串:长度从X,X - 2,X - 4....1/0
从大到小扫描,边合并边计算乘积即可
*/

char s[N],ss[N * 2];
ll l,n,k,d[N * 2],cnt[N];            

ll power(ll a,ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

void add(){
    l = 2 * strlen(s) + 1;
    for(int i = 0,j = 0;i < l;i++){
        ss[i] = (i & 1) == 0 ? '#' : s[j++];
    }
}

void manacher(){
    for(ll i = 0,r = 0,c = 0,len;i < l;i++){
        len = r > i ? min(d[2 * c - i],r - i) : 1;
        while(len + i < l && i - len >= 0 && ss[len + i] == ss[i - len]){
            len++;
        }
        if(len + i > r){
            r = len + i;
            c = i;
        }
        d[i] = len;
    }
}

//这里处理的是加上#之后的字符串,所以i从1开始,每次+2
ll compute(){
    manacher();
    for(int i = 1;i < l;i += 2){
        //每个回文半径 - 1就是回文串的长度
        cnt[d[i] - 1]++;
    }
    //sum统计当前最大的回文串的个数,处理完每次k - sum
    //ans是统计答案,每次用快速幂计算power(len,min(k,sum))
    ll ans = 1,sum = 0;
    //注意本题要求回文串是奇数,那么如果n为偶数就先-1再计算
    for(ll len = (n & 1) == 1 ? n : (n - 1);k >= 0 && len >= 0;len -= 2){
        sum += cnt[len];
        ans = (ans * power(len,min(k,sum))) % mod;
        k -= sum;
    }
    return k < 0 ? ans : -1;
}


void solve(){
    cin >> n >> k >> s;
    add();
    cout << compute() << '\n';
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