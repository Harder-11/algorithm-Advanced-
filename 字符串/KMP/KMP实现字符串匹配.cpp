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
给出两个字符串S和T,求T在S中所有的出现位置
例如:S = abababc,T = aba,那么T在S的所有出现位置为1和3
本题就是Border实现字符串匹配的应用
KMP充分李彤前缀匹配的有效信息,即next数组(Border的性质)进行快速的转移
假设T1是匹配前的遇到不匹配位置,T2是T1转移之后的串
那么显然在S和T进行匹配的时候,如果发现了匹配不上的位置,那么此时T2匹配上
的部分就是T1的Border(因为对于S串匹配上的都是统一部分,此时T2匹配上的是T串的前缀
明显就是T1的Border,也就是T1匹配好的后缀部分)
*/

string s,t;
int nxt1[N],nxt2[N];
vector<int> idx;

void solve(){
    cin >> s >> t;
    int n = s.size(),m = t.size();
    s = " " + s,t = " " + t;
     nxt2[0] = nxt2[1] = 0;
    for(int i = 2;i <= m;i++){
        nxt2[i] = nxt2[i - 1];
        while(nxt2[i] && t[i] != t[nxt2[i] + 1]) nxt2[i] = nxt2[nxt2[i]];
        nxt2[i] += (t[i] == t[nxt2[i] + 1]);
    }
    int p = 0;
    for(int i = 1;i <= n;i++){
        while(p && t[p + 1] != s[i]){
            p = nxt2[p];
        }
        if(t[p + 1] == s[i]){
            p++;
        }
        //注意,即使匹配成功也是用nxt数组回退
        if(p == m){
            cout << i - m + 1 << '\n';
            p = nxt2[p];
        }
    }
    for(int i = 1;i < t.size();i++){
        cout << nxt2[i] << " ";
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