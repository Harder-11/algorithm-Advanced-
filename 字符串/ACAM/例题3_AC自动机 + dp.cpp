#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 6005;
const int mod = 1e4 + 7;
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
给出一个字典,直到包含60个字符串,且字典串的总长度不超过100
求所有长度为M(M <= 100)的串中(共26^M个),有多少个串至少包含一个字典串,结果模10007
由于不好直接求至少包含一个字典串的串,那么稍微容斥一下,那么就是求26^M - 完全不包含字典串的串个数
由于是字符串匹配问题,那么明显就是AC自动机 + dp
设f[len][u]表示长度为len的字符串,当前匹配到了AC自动机的u节点的方案数
那么转移的时候就枚举下一个字符填什么(26个字符依次尝试),然后找到匹配的AC自动机节点v
如果c是一个终止节点,则是一个不合法的转移
先看u这个节点是否有c作为后继边,如果有就直接走过去,否则就在fail链上跳(最坏情况就会跳到根上,时间复杂度O(depth))
非法的点就不转移即可
此时的时间复杂度为O(M * N * N * |Σ|) = 2e7左右,可以AC(时间复杂度比这个小,因为每次找c的时候不一定会回到根)
本题实际上可以通过M=10000的案例,因为在建AC自动机的时候实现了e[tr[u][i]] |= e[tr[fail[u]][i]],这样AC自动机实际变成了一个Trie图,省去了
在fail链上跳的步骤,那就没有了O(depth)的复杂度
*/

int n,m;
int idx,tr[N][26],fail[N],dp[105][N],e[N];
queue<int> q;

void TrieInsert(const string &s){
    int p = 0,cnt = 0,len = s.size();
    for(int i = 0;i < len;i++){
        int c = s[i] - 'A';
        if(!tr[p][c]) tr[p][c] = ++idx;
        p = tr[p][c];
    }
    e[p] = 1;
}

void build(){
    for(int i = 0;i < 26;i++){
        if(tr[0][i]) q.push(tr[0][i]);
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0;i < 26;i++){
            if(tr[u][i]){
                //这里如果后缀是一个完整字符串,那么e[tr[u][i]]也应该被置为1,因为只要含有一个字典串就不符合
                e[tr[u][i]] |= e[tr[fail[u]][i]];
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
} 

void solve(){
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        string t; cin >> t;
        TrieInsert(t);
    }
    build();
    dp[0][0] = 1;
    for(int i = 1;i <= m;i++){
        for(int j = 0;j <= idx;j++){
            for(int k = 0;k < 26;k++){
                if(!e[tr[j][k]]){
                    dp[i][tr[j][k]] = (dp[i][tr[j][k]] + dp[i - 1][j]) % mod;
                }
            }
        }
    }
    int ans = 0,sum = 1;
    for(int i = 0;i <= idx;i++){
        ans = (ans + dp[m][i]) % mod;
    }
    for(int i = 1;i <= m;i++){
        sum = sum * 26 % mod;
    }
    cout << (sum - ans + mod) % mod << '\n';
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