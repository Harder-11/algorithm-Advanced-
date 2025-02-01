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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
题意:给出一个字典,至多包含300000个字符串,且字符串的总长度不超过300000
再给出一个文本串T(|T| <= 300000),问最少使用多少个字典串可以拼接出T
同一个字典串使用多次算多次,拼接时允许重叠,只需要保证重叠部分匹配即可
例如T = abcd,可以使用字典串S = cdxx拼接成T' = abcdxx

首先容易想到使用dp:f[i]表示拼接出T[1,i]的操作次数
转移时,设某字典串Si等于T[1,i]的后缀(这样才可以拼接上),Si的长度是|S|
那么可以由f[i - |S|]...一直到f[i - 1]转移而得,即
f[i] = min(f[i - j]) + 1(1 <= j <= |S|)
由于可能有很多的字典串S都满足上述转移,由于转移的区间是[i - |S|,i - 1] + 1
所以我们只需要找到最大的|S|即可,也就是转移区间是[i - max|S|,i - 1] + 1
很显然这个是用AC自动机即可,然后预处理出每个点的转移区间
而找区间的最小值fi用线段树去维护即可,同时满足单点修改(直接让dp在线段树上修改而不是递推)
一开始如果前i位能被一个模式串直接表示出来,fi = 1,否则fi = INF
最后,如果f(len) > len,说明运算过程有INF参与,即不可能通过已有的模式串表达出来 
*/

//len就是用来找区间的最大的|S|
int n,idx,dep[N],tr[N][26],len[N],fail[N];
//s为文本串,str为模式串
char s[N],str[N];
queue<int> q;
struct node {
    int l,r,mn;
} segTr[N << 2];

void insert(){
    int p = 0;
    for(int i = 0;str[i];i++){
        int u = str[i] - 'a';
        if(!tr[p][u]){
            tr[p][u] = ++idx;
            dep[idx] = dep[p] + 1;
        }
        p = tr[p][u];
    }
    //插入的时候len = dep
    len[p] = dep[p];
}

//bfs建AC自动机
void buildTrie(){
    int hh = 0,tt = -1;
    for(int i = 0;i < 26;i++){
        if(tr[0][i]) q.push(tr[0][i]);
    }
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(int i = 0;i < 26;i++){
            int u = tr[p][i];
            if(!u){
                tr[p][i] = tr[fail[p]][i];
            } else {
                fail[u] = tr[fail[p]][i];
                q.push(u);
            }
        }
        //每次更新,看能不能找到更长的|S|
        len[p] = max(len[fail[p]],len[p]);
    }
}

void pushup(int u){
    segTr[u].mn = min(segTr[ls].mn,segTr[rs].mn);
}

void buildSeg(int u,int l,int r){
    segTr[u] = {l,r,INF};
    if(l != r){
        int mid = (l + r) >> 1;
        buildSeg(ls,l,mid);
        buildSeg(rs,mid + 1,r);
        pushup(u);
    }
}

void modify(int u,int x,int k){
    if(segTr[u].l == segTr[u].r && segTr[u].l == x){
        segTr[u].mn = k;
    } else {
        int mid = segTr[u].l + segTr[u].r >> 1;
        if(x <= mid) modify(ls,x,k);
        else modify(rs,x,k);
        pushup(u);
    }
}

int query(int u,int l,int r){
    if(l <= segTr[u].l && r >= segTr[u].r) return segTr[u].mn;
    int mid = segTr[u].l + segTr[u].r >> 1,res = INF;
    if(l <= mid) res = min(res,query(ls,l,r));
    if(r >= mid + 1) res = min(res,query(rs,l,r));
    return res;
}

void solve(){
    cin >> n >> (s + 1);
    for(int i = 0;i < n;i++){
        cin >> str;
        insert();
    }
    buildTrie();
    buildSeg(1,1,strlen(s + 1));
    for(int i = 1,j = 0;s[i];i++){
        int u = s[i] - 'a';
        j = tr[j][u];
        int t;
        //只要i - len[j] >= 1,那么就询问i - len[j],i - 1范围的后缀即可
        //否则直接领t = 1(剩下的情况只能是i == len[j])
        if(i - len[j] >= 1) t = query(1,i - len[j],i - 1) + 1;
        else if(i == len[j]) t = 1;
        modify(1,i,t);
    }
    //最后答案就在1 ~ len里面找最小值即可,那么调用query就行
    int ans = query(1,strlen(s + 1),strlen(s + 1));
    if(ans > strlen(s + 1)) cout << -1 << '\n';
    else cout << ans << '\n';
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