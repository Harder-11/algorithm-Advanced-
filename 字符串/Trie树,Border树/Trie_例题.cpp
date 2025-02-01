#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 300005;
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
给出n个不同的字符串s1,s2...sn,你可以任意指定字符之间的大小关系(即重新定义字典序)
求有多少个串可能成为字典序最小的串
n <= 30000,Σ(i=1,n)|Si| <= 300000
思路:只要有别的串作为前缀就一定不行
那么先建出字典树,然后诸葛字符串判定可行性
考虑si在字典树上的每个结点,如果有多余一个后继边,则Si使用的字母必须小于其他字母
等价于判断26个点的有向图上是否有环(指定的最小的那个串每个节点都必须满足字典序小于其他结点)
那么就把字典序小于当做一个有向边,定义边方向是从字典序大的指向字典序小的
那么就跑拓扑排序,如果存在环,那么说明了不等关系形成一个环,那么就不成立

*/

int tr[300005][26],cnt,n,idx; 
bool vis[300005],check[26],cc[26][26];
//这里千万不要开s[N],否则会有一个长度为3e5的链卡空间,导致MLE
vector<string> s;
vector<int> e[26];
vector<string> b; 
int deg[26];

void insert(const string &s,int l){
    int p = 0;
    for(int i = 0;i < l;i++){
        int c = s[i] - 'a';
        if(!tr[p][c]) tr[p][c] = ++cnt;
        p = tr[p][c];
    }
    vis[p] = 1;
}

bool find(const string &s,int l){
    int p = 0;
    for(int i = 0;i < l - 1;i++){
        int c = s[i] - 'a';
        if(vis[tr[p][c]]) return 0;
        p = tr[p][c];
    }
    return 1;
}

void build(const string &s){
    for(int i = 0;i < 26;i++){
        e[i].clear();
        deg[i] = 0;
        check[i] = 0;
    }
    memset(cc,0,sizeof cc);
    int p = 0;
    for(int i = 0;i < s.size();i++){
        int c = s[i] - 'a';
        for(int j = 0;j < 26;j++){
            if(j != c && tr[p][j] && !cc[c][j]){
                cc[c][j] = 1;
                check[j] = check[c] = 1;
                e[j].push_back(c);
                deg[c]++;
            }
        }
        p = tr[p][c];
    }
}

bool topo(){
    queue<int> q;
    for(int i = 0;i < 26;i++){
        if(deg[i] == 0 && check[i]) q.push(i);
    }

    while(q.size()){
        int cur = q.front();
        q.pop();
        for(int x : e[cur]){
            if(--deg[x] == 0){
                q.push(x);
            }
        }
    }
    for(int i = 0;i < 26;i++){
        if(deg[i] && check[i]){
            return 0;
        }
    }
    return 1;
}

void solve(){
    cin >> n;
    int ans = 0;
    for(int i = 0;i < n;i++){
        string t; cin >> t;
        s.push_back(t);
        insert(s[i],s[i].size());
    }
    for(int i = 0;i < n;i++){
        if(find(s[i],s[i].size())){
            build(s[i]);            
            if(topo()){
                ans++;
                b.push_back(s[i]);
            }
        }
    }
    cout << ans << '\n';
    for(auto x : b) cout << x << '\n';
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