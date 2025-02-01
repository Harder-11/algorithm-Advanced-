#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
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
给出一个字符串S,求最长的双倍回文子串
若一个串能表示为TR(T)TR(T)的形式,则称为一个双倍回文子串,例如abbaabba,其中|S| <= 500000
由于本质不同的回文串只有n个,因此逐一检查是否是双倍回文即可
由于新的回文串一定发生于更新最右回文串的时候,所以在发生暴力拓展的时候顺便检查这个新的回文串的一半是不是回文串即可,并且要求这个回文串的一半必须是偶数长度
*/

int n,m,d[N << 1],ans;
char s[N],ss[N << 1];

void add(){
    n = 2 * m + 1;
    for(int i = 1,j = 1;i <= n;i++){
        ss[i] = (i & 1) == 1 ? '#' : s[j++];
    }
}

void manacher(){
    add();
    for(int i = 1,r = 0,c = 0;i <= n;i++){
        d[i] = r > i ? min(r - i,d[2 * c - i]) : 1;
        while(i + d[i] <= n && i - d[i] >= 0 && ss[d[i] + i] == ss[i - d[i]]){
            d[i]++;
        }
        if(d[i] + i > r){
            if((i & 1)){
                for(int j = max(i + 4,r);j < i + d[i];j++){
                    if(!((j - i) & 3) && d[i - (j - i) / 2] > (j - i) / 2){
                        ans = max(ans,j - i);
                    }
                }
            }
            r = d[i] + i;
            c = i;
        }  
    }
}

void solve(){
    cin >> m >> (s + 1);
    manacher();
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