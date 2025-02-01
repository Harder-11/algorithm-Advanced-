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
给定一个字符串S,长度不超过1e6,求一个最长的子串T,满足:
T为S的前缀
T为S的后缀
T在S中至少出现了K次

思路:前两条明显就是找的S的Border(n到根节点的整条链都是S的Border)
而要找T在S中至少出现了K次,那么就是子树大小 >= k
那么建好Border树之后就dfs得到每个结点的子树大小siz即可
*/

string s;
int n,k,siz[N],tr[N][26],nxt[N];
vector<int> e[N];
int ans;
void dfs(int u){
    siz[u] = 1;
    for(auto x : e[u]){
        dfs(x);
        siz[u] += siz[x];
    }
}

void solve(){ 
    cin >> n >> k >> s;
    s = " " + s;
    if(k == 1){
        cout << s.substr(1,n) << '\n';
        return;
    }
    nxt[0] = nxt[1] = 0;
    for(int i = 2;i <= n;i++){
        nxt[i] = nxt[i - 1];
        while(nxt[i] && s[i] != s[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
        nxt[i] += (s[i] == s[nxt[i] + 1]);
    }
    for(int i = 1;i <= n;i++){
        e[nxt[i]].push_back(i);
    }
    dfs(0);
    //注意这里一定是i = n开始遍历,因为当k = 1的时候n也是满足条件的
    //(或者特判1也可以)
    for(int i = nxt[n];i;i = nxt[i]){
        if(siz[i] >= k){
            ans = i;
            break;
        }
    }
    if(ans){
        cout << s.substr(1,ans) << '\n';
    } else cout << -1 << '\n';
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