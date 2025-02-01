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
Border树(失配树)与AC自动机联系起来了
定义:对于一个字符串S,n = |S|,他的Border树(next树)一共有n+1个节点(0,1,2,3....n)
0是这棵有向树的根,对于其他节点1<= i <= n,父节点为next[i]
性质:1.每个前缀prefix[i]的所有Border:结点i到根的链
2.哪些前缀有长度为x的Border:x的子树
3.求两个前缀的公共Border等价于求LCA

例题:给出一个字符串S,|S| <= 1000000,有Q <= 100000次询问:
前缀S[1,p]和前缀S[1,q]的最大公共Border长度
思路:直接是利用到了Border的3性质,等价于求LCA
那么使用倍增或者Tarjan都可以
*/

//ST表跑LCA
int fa[N][22],n,m,dep[N];
string s;

void solve(){
    cin >> s >> m;
    n = s.size();
    s = " " + s;
    fa[0][0] = fa[1][0] = 0;
    dep[0] = 0,dep[1] = 1;
    //KMP,但是不用nxt数组求到每个i的父节点j(也就是next[i]的值)
    //顺便可以把dep数组填写完毕
    for(int i = 2,j = 0;i <= n;i++){
        while(j && s[j + 1] != s[i]) j = fa[j][0];
        j += (s[j + 1] == s[i]);
        fa[i][0] = j;
        dep[i] = dep[j] + 1;
    }
    for(int i = 1;i <= 21;i++){
        for(int j = 1;j <= n;j++){
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    while(m--){
        int x,y;
        cin >> x >> y;
        if(dep[x] < dep[y]) swap(x,y);
        for(int i = 21;i >= 0;i--){
            if(dep[fa[x][i]] >= dep[y]){
                x = fa[x][i];
            }
        }
        for(int i = 21;i >= 0;i--){
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i];
                y = fa[y][i];
            }
        }
        cout << fa[x][0] << '\n';
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