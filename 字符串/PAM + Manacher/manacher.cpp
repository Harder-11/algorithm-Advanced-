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
概念:
1.反转串R(S):一个字符串S = S[1]S[2]...S[n],其反串为R(S) = S[n]S[n - 1]...S[1]
2.回文串:满足S = R(S)的串就是回文串
3.回文中心:奇长度回文串,回文中心为S[(n + 1) / 2]
偶长度回文串,回文中心为S[n / 2],S[n / 2 + 1]的中间
4.回文半径L:回文中心到回文串的左右端点的距离相等,此距离成为回文半径
那么使用二元组<回文中心,回文半径>来表示一个回文串

长度与半径的关系:
1.奇回文串: |S| = 2L - 1
2.偶回文串: |S| = 2L
回文半径的二分性:回文半径-1等价于同时删掉回文串的首尾字母,依然是回文串
回文串和Border:对于回文串S,回文前(后)缀等价于Border(相当于Border也是一个回文串)

求回文半径,回文中心方法:
为了统一奇偶性,将S的,每两个字母中间以及开头结尾插入#,比如S=abcd-->#a#b#c#d#,这样使得字符串一定是奇数长度的
容易发现,|S#| = 2|S| + 1,以及|S| = (|S#| - 1) / 2 = |S#| / 2,容易验证此关系对回文半径依然适用

定义:Len[i]表示以i为回文中心的最大回文半径
最右回文串P:所有已经求得的回文串中,右端点最靠右的一个
那么从左到右求每个位置的回文半径,同时维护最右回文串S[L,R]及其回文中心p
假设1,2,....i - 1位置的len已经被求出,当前需要求Len[i],根据i和[L,R]的关系,总共分为三种情况
1.i > R,以i为回文中心,向左向右暴力扩展,求得回文半径Len[i],同时最右回文串变成p = i,L = i - Len[i] + 1,R = i + Len[i] - 1
2.i <= R,由于回文串的对称性:最右回文串P的左半和右半是对称的,找到i关于p的对称位置j = 2p - i
由于len[j]是已经求到的,根据最右回文串的对称性,Len[i]可以直接继承Len[j]在最右回文串范围内的部分,根据Len[j]是否超出最右回文串的范围分为两种情况
(1)j - Len[j] + 1 > L(没有出范围),那么确定Len[i] = Len[j],且不能再继续拓展
(2)j - Len[j] + 1 <= L,由于超出范围的部分位置未知,一次Len[i]最多继承到最右回文串范围内的Len[j]
由于未知部分不知道能否匹配,那么暴力拓展,最右回文串更新为i

用法:1.求每个位置的回文半径
2.求本质不同回文串:在manacher中,新的回文串一定出现在使得最右串右移的时候,因此本质不同回文串最多有n个,把所有更新最右回文串去重即得到本质不同回文串
*/

char s[N],ss[N << 1];
int d[N],n;

//往s串中间和首尾填上#字符使其变成奇数长度
void add(){
    n = strlen(s) * 2 + 1;
    for(int i = 0,j = 0;i < n;i++){
        ss[i] = (i & 1) == 0 ? '#' : s[j++];
    }
}

void manacher(string s){
    for(int i = 0,c = 0,r = 0,len;i < n;i++){
        len = r > i ? min(r - i,d[2 * c - i]) : 1;
        while(i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]){
            len++;
        }
        if(r < len + i){
            r = len + i;
            c = i;
        }
        d[i] = len;
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