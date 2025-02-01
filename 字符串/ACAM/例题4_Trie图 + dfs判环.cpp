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
题意:给出N <= 2000个01串,他们每一个表示一段病毒序列,病毒代码总长度不超过30000
求是否存在无限长度的01串,不包含任意病毒序列作为子串,如果存在,输出"TAK",否则输出"NIE"

思路:本题的本质就是问Trie图上(去掉所有终止节点),是否存在无限长度的路径,即判断是否有环的存在
那么用topo排序或者直接dfs判环即可,注意:这个环必须是root节点可以到达的.那么从根节点开始dfs进行染色,在染色部分看是否有环存在
*/
int tr[N][2],fail[N],e[N];
int n,idx,ins[N],used[N];
bool vis[N],flag;
queue<int> q;

void insert(const string &s){
    int p = 0,len = s.size();
    for(int i = 0;i < len;i++){
        int c = s[i] - '0';
        if(!tr[p][c]) tr[p][c] = ++idx;
        p = tr[p][c];
    }
    e[p] = 1;
}

void build(){
    for(int i = 0;i <= 1;i++){
        if(tr[0][i]) q.push(tr[0][i]);
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0;i <= 1;i++){
            if(tr[u][i]){
                fail[tr[u][i]] = tr[fail[u]][i];
                //后缀都是病毒了那么本身肯定也是病毒,只要含有病毒序列就是病毒(后缀就是一个病毒序列了)
                e[tr[u][i]] |= e[fail[tr[u][i]]];
                q.push(tr[u][i]);
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

//dfs判环
bool dfs(int x){
    ins[x] = 1;
    for(int i = 0;i <= 1;i++){
        int v = tr[x][i];
        if(ins[v]) return 1;
        if(used[v] || e[v]) continue;
        used[v] = 1;
        if(dfs(v)) return 1;
    }
    ins[x] = 0;
    return 0;
}


void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        string t; cin >> t;
        insert(t);
    }
    build();
    cout << (dfs(0) ? "TAK" : "NIE") << '\n';
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