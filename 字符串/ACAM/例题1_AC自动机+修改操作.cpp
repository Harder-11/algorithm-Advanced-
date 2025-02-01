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
给出一个有N个串的字典,然后进行M次操作
1.修改操作:向字典中新增一个新的字典串S
2.查询操作:查询所有字典串在询问串T中的出现次数,同一个字符串重复出现算多次
1 <= N,M <= 100000,输入总字符串长度 <= 3e6

那么先无视修改操作,只考虑查询:可以建出AC自动机,然后将查询串在AC自动机上运行
匹配到AC自动机的一个结点时,将该节点到根的路径上终止标记的个数计入答案
由于AC自动机是离线型数据结构,即不能支持快速增删字典串,因此考虑到维护操作需要先离线
动态维护终止标记,使用dfs序 + 树状数组快速维护每个点到根路径上的终止标记个数
*/

//a是操作符(op),s是操作的字符串 
struct node {
    int a;
    string s;
} g[N];

int tr[N][26];
queue<int> q;
//lst是终止标记,用于记录每个节点失败时应该回退到的最深的一个节点，用于统计出现次数。
//(lst指向的一定是一个终止节点,用来快速查询,如果没有lst数组,在find函数的while里面会
//很可能循环很多次(n次),导致时间复杂度退化到O(N^2)导致超时)(相当于倍增)
//siz用于记录每个节点的模式串出现次数。
//f记录每次操作(插入操作)中对应的节点(专门用来处理插入操作的)
//f[o]表示第o次操作对应的模式串的终止节点
//e数组是用来记录结点是否为终止节点,e[u]=1代表节点就是终止节点

int siz[N],f[N],fail[N],tot,e[N],lst[N],n,m;
char a[N];

void insert(char *s,int len,int o){
    int p = 1;
    for(int i = 0;i < len;i++){
        int c = s[i] - 'a';
        if(!tr[p][c]) tr[p][c] = ++tot;
        p = tr[p][c];
    }
    e[p] = 1;
    //这里用来分辨是原始串还是新添加的串
    if(o == 0) siz[p]++;
    f[o] = p;
}

void bfs(){
    q.push(1);
    while(q.size()){
        int u = q.front();
        q.pop();
        for(int i = 0;i < 26;i++){
            if(!tr[u][i]) tr[u][i] = tr[fail[u]][i];
            else {
                q.push(tr[u][i]);
                fail[tr[u][i]] = tr[fail[u]][i];
                //如果子节点的fail指针指向的对象是一个终止位置,那么子节点的lst就是他的fail指向的节点
                //否则就是fail指针指向的节点的lst(相当于lst指向的一定是一个终止节点)
                lst[tr[u][i]] = e[fail[tr[u][i]]] ? fail[tr[u][i]] : lst[fail[tr[u][i]]];
            }
        }
    }
}

//find函数,统计字符串s在AC自动机中出现次数
//这里时间复杂度就是O(m)
void find(char *s,int len){
    int p = 1,k,cnt = 0;
    for(int i = 0;i < len;i++){
        int c = s[i] - 'a';
        k = tr[p][c];
        while(k > 1){
            cnt += siz[k];
            k = lst[k];
        }
        p = tr[p][c];
    }
    cout << cnt << '\n';
}

void solve(){
    cin >> n >> m;
    memset(tr,0,sizeof tr);
    memset(fail,0,sizeof fail);
    memset(siz,0,sizeof siz);
    memset(lst,0,sizeof lst);
    memset(e,0,sizeof e);
    for(int i = 0;i < 26;i++) tr[0][i] = 1;
    fail[1] = 0,tot = 1;
    //首先不管是不是原始串,都拿来建AC自动机
    for(int i = 1;i <= n;i++){
        cin >> a;
        int len = strlen(a);
        insert(a,len,0);
    }
    for(int i = 1;i <= m;i++){
        cin >> g[i].a >> g[i].s;
        int len = g[i].s.size();
        for(int j = 0;j < len;j++) a[j] = (char)g[i].s[j];
        if(g[i].a == 1) insert(a,len,i);
    }
    //注意这里的bfs一定是在insert询问串之后再建AC自动机,然后建自动机后就每次把siz[f[i]]++然后每次统计即可
    bfs();
    for(int i = 1;i <= m;i++){
        int len = g[i].s.size();
        for(int j = 0;j < len;j++) a[j] = (char) g[i].s[j];
        //这里每次siz++,防止和原始串搞混
        if(g[i].a == 1) siz[f[i]]++;
        else find(a,len);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}