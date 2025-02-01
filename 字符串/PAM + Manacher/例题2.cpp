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
给出一个字符串S,求最长的双回文子串
双回文子串的定义为:可以从一个位置切开,使得前缀和后缀都是回文串 

思路:题目就是说一个字符串从中间分开成两个字符串,这两个字符串都是回文串
那么枚举拼接位置,把两边独立开来,最大化以该点为左端点和右端点的回文串长度
即等价于最大化左侧回文串长度和右侧回文串长度
*/

char s[N],ss[N << 1];
int n,d[N << 1],l[N << 1],r[N << 1];


void add(){
    n = 2 * strlen(s) + 1;
    for(int i = 0,j = 0;i < n;i++){
        ss[i] = (i & 1) == 0 ? '#' : s[j++];
    }
}

void manacher(){
    add();
    for(int i = 0,c = 0,r = 0,len;i < n;i++){
        len = r > i ? min(r - i,d[2 * c - i]) : 1;
        while(i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]){
            len++;
        }
        if(i + len > r){
            r = i + len;
            c = i;
        }
        d[i] = len;
    }
}


void solve(){
    cin >> s;
    manacher();
    for(int i = 0,j = 0;i < n;i++){
        while(i + d[i] > j){
            l[j] = j - i;
            j += 2;
        }
    }
    for(int i = n - 1,j = n - 1;i >= 0;i--){
        while(i - d[i] < j){
            r[j] = i - j;
            j -= 2;
        }
    }
    int ans = 0;
    //回文串长度必须是1,否则会出错,所以i从1遍历到n - 2
    for(int i = 1;i <= n - 2;i++){
        ans = max(l[i] + r[i],ans);
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
