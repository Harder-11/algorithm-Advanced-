#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2000005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs = 1331;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
字符串S长度不超过1e6,求一个最长的子串T,满足:
--T为S的前缀
--T为S的后缀
--T在S中至少出现过三次
思路:T肯定是S的Border,如果T还要在其他位置出现一次
那么利用KMP求出S的所有Border,答案为nxt[n]或者nxt[nxt[n]]
那么先检查最大Border(nxt[n]),那么在中间寻找是否有子串==最大Border
如果没有找到,那么就找nxt[nxt[n]],因为最大Border的Border肯定出现了四次
因为S前缀和后缀字符串他们分别的前缀和后缀都是nxt[nxt[n]],一共有4次
此时就是最长的满足条件的T
*/

string s;
int nxt[N];

void solve(){
    cin >> s;
    int len = s.size();
    s = " " + s;
    nxt[0] = 0;
    nxt[1] = 0;
    for(int i = 2;i <= len;i++){
        nxt[i] = nxt[i - 1];
        while(nxt[i] && s[i] != s[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
        nxt[i] += (s[i] == s[nxt[i] + 1]);
    }
    int r = nxt[len];
    int rr = nxt[nxt[len]];
    //注意r和rr都要特判,先特判r,如果r是0的话,不特判就是进入for输出"";
    if(r == 0){
        cout << "Just a legend" << '\n';
        return;
    }
    for(int i = 2;i <= len - 1;i++){
        if(nxt[i] == r){
            cout << s.substr(1,r) << '\n';
            return;
        }
    }
    if(rr != 0){
        cout << s.substr(1,rr) << '\n';
    } else {
        cout << "Just a legend" << '\n';
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