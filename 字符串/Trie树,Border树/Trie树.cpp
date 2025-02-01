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
字典:一个字符串的集合称为字典
字典串:在字典中的串叫做字典串
在处理字符串时,常常会遇到这样的问题:给出一个字典,然后大量询问:输入一个字符串,判断它是否在字典当中

定义:Trie是一个有根树,每个点有|Σ|个后继边,每条边上有一个字符,每个点表示一个前缀:从根到这个点的边上的所有字符顺次连接形成的字符串
每个点还有一个终止标记:是否这个点代表的字符串是字典的子串
操作:可以插入,删除串
插入操作很简单,就往下跳,遇到0之后就动态开点即可
删除串要首先判断串是否在字典里面,如果该点不能删(比如同时存在apple和app,删除app的时候),此时把终止标记取消即可

作为一个数据结构,那么可以进行持久化(包括树链剖分,LCA等都支持)
*/

//字典树模版
int tr[N][26],cnt;
bool vis[N];

void insert(char *s,int l){
    int p = 0;
    for(int i = 0;i < l;i++){
        int c = s[i] - 'a';
        if(!tr[p][c]) tr[p][c] = ++cnt;
        p = tr[p][c];
    }
    vis[p] = 1;
}

bool find(char *s,int l){
    int p = 0;
    for(int i = 0;i < l;i++){
        int c = s[i] - 'a';
        if(!tr[p][c]) return 0;
        p = tr[p][c];
    }
    return vis[p];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}