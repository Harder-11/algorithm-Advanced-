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
AC自动机背景:
给出一个字典和若干的询问:多少个字符串在询问串中出现过?
即单串和多串的匹配问题
对于KMP算法:把问题看做每个字典串和询问串的单模式匹配
缺点:字典串形成的孤岛,没有打通链路,形成闭环导致时间复杂度很高
对于Trie:利用字典树进行多模式的匹配
缺点:不能在失配的时候进行合理的跳转,盲目尝试,导致复杂度很高

AC自动机 = Trie + KMP
AC自动机基于Trie,将KMP的Border概念推广到多模式串匹配
AC自动机是一种离线型数据结构,即不支持增量添加新的字符串

广义Border
推广到两个串:对于S和T,相等的p长度的S的后缀和T的前缀称为一个Border
推广到一个字典:对于串S和一个字典D,相等的p长度的S的后缀和任意一个字符串T的前缀称为一个Border
失配指针(fail):对于Trie中的每一个节点(即某个字符串的前缀)它与Trie中所有串的最大Border即为失配指针

类似于KMP求Border,任意结点的Border长度减一一定是父节点的Border
因此可以通过遍历父节点的失配指针链来求解,因此在求失配指针的时候,一定要按照长度由小到大来求(bfs)
那么首先第一层的fail指针都是指向的根节点
从第二层开始的fail指针就看其父节点的fail指针指向的节点的子节点进行匹配是否有对应的字符(形成四边形)
如果匹配失败,就继续沿着fail指针往上跳,直到匹配为止,如果到根节点都没有匹配好,那么该节点fail指针指向根 

例题(P5357)
给出一个文本串S和一个字典,求每个字典串在S中的出现次数
思路:用字典建出一个AC自动机,然后拿S在自动机上去匹配
那么就用S中所有的前缀串去匹配到AC自动机的那个节点,匹配到的节点沿着fail指针一直到根节点都+1
每个字典串的出现次数等于失配树的子树内的标记总量,因此在失配树上自底向上推标记即可
最后统计终止结点的标记量是多少就知道出现了多少次
*/

int tr[N][26],fail[N],tot,n;
//用e数组存终止节点的编号,方便使用
int e[N],sum[N];
vector<int> G[N];
string s,t;

int insert(string s){
    int p = 0;
    for(auto ch : s){
        int c = ch - 'a';
        if(!tr[p][c]) tr[p][c] = ++tot;
        p = tr[p][c];
    }
    return p;
}

//bfs建AC自动机
void bfs(){
    queue<int> q;
    for(int i = 0;i < 26;i++){
        if(tr[0][i]){
            q.push(tr[0][i]);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0;i < 26;i++){
            //有tr[u][i],就找u的fail对应节点的子节点
            if(tr[u][i]){
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
                //没有tr[u][i],直接将u连上fail节点tr[fail[u]][i]
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

//dfs求sum值
//注意这里是本题的关键中的关键,为什么是fail边连成的图进行dfs得到答案?
//因为fail边指向的节点都是最长后缀,那么此时只要是沿着fail边走过的对应的
//都是S中出现的子串,而前面已经把所有的sum[u]++了(那么不用区分是不是字符串结束位置)
//最后dfs一遍即可

void dfs(int x){
    for(auto v : G[x]){
        dfs(v);
        sum[x] += sum[v];
    }
}

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> s;
        e[i] = insert(s);
    }
    bfs();
    //根据fail节点建图,方便dfs统计sum数组
    for(int u = 1;u <= tot;u++){
        G[fail[u]].push_back(u);
    }
    cin >> t;
    int u = 0;
    for(auto ch : t){
        int c = ch - 'a';
        u = tr[u][c];
        sum[u]++;
    }
    dfs(0);
    for(int i = 1;i <= n;i++){
        cout << sum[e[i]] << '\n';
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