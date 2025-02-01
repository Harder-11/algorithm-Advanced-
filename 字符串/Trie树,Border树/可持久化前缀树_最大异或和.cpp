#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 600005;
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
给出一个数组A,长度为n <= 300000,再给出Q <= 300000次操作
1.修改操作:将数字x添加到数组末尾,数组长度n变成n+1
2.查询操作:求区间[l,r]内的p,使得A[p]^A[p+1]^....^A[n]^x最大

思路:仍然是利用异或前缀和,A[p]^A[p+1]...^A[n]^x = sum[n]^sum[p-1]^x
发现sum[n]^x是一个定值,假设值为Y,那么本质就是查询的最大的sum[p-1]^Y
如果没有p的限制,那么利用01-Trie即可
但是本题有区间限制,那么使用持久化01-Trie即可,持久化就类似于前缀和,对于每个区间都建一棵前缀树
直接使用区间v[r] - v[l - 1]可以在O(1)求出状态

如何持久化?使用cnt数组来描述每个结点被多少字符串使用(子树中有多少终止节点)
那么持久化就是对cnt做持久化,先把Trie树构建出来,然后每次添加字符串的时候,新建一个根节点,如果要+1的点就动态开点
不+1的点就直接连上,不动态开点
持久化之后,如何获取某一个区间内的Trie树长什么样呢?
--利用前缀和作差即可,比如要求[3,5]区间的Trie树,直接用cnt_v5 - cnt_v2即可得到cnt的每个点的利用情况
只要不等于0,那么就说明这个区间内的Trie树是有这个节点的,等于0就没有这个节点
每次开的结点最大为logan个,空间复杂度完全可以接受
而每次查询的时间复杂度因为log(an)的,那么总的时间复杂度就是(qlog(an)),可以通过
*/

char op;
int l,r,a[N],s[N],x,n,q;
//rt存放每个版本的根节点
int rt[N],tr[N * 33][2],val[N * 33],cnt;

void insert(int o,int lst,int v){
    for(int i = 28;i >= 0;i--){
        val[o] = val[lst] + 1;
        if((v & (1 << i)) == 0){
            if(!tr[o][0]) tr[o][0] = ++cnt;
            tr[o][1] = tr[lst][1];
            o = tr[o][0];
            lst = tr[lst][0];
        } else {
            if(!tr[o][1]) tr[o][1] = ++cnt;
            tr[o][0] = tr[lst][0];
            o = tr[o][1];
            lst = tr[lst][1];
        }
    }
    val[o] = val[lst] + 1;
}

int query(int o1,int o2,int v){
    int res = 0;
    for(int i = 28;i >= 0;i--){
        int t = ((v & (1 << i)) ? 1 : 0);
        //类似于前缀和,只要减出来val是不等于0的,说明了这个区间范围内前缀树是有这个节点的
        if(val[tr[o1][!t]] - val[tr[o2][!t]]){
            res |= (1 << i);
            o1 = tr[o1][!t];
            o2 = tr[o2][!t];
        } else {
            o1 = tr[o1][t];
            o2 = tr[o2][t];
        }
    }
    return res;
}

void solve(){
    cin >> n >> q;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        s[i] = s[i - 1] ^ a[i];
    }
    for(int i = 1;i <= n;i++){
        //动态开点一个新的前缀树的根
        rt[i] = ++cnt;
        insert(rt[i],rt[i - 1],s[i]);
    }
    while(q--){
        cin >> op;
        if(op == 'A'){
            n++;
            cin >> a[n];
            s[n] = s[n - 1] ^ a[n];
            rt[n] = ++cnt;
            insert(rt[n],rt[n - 1],s[n]);
        } else {
            cin >> l >> r >> x;
            l--,r--;
            if(l == 0){
                cout << max(s[n] ^ x,query(rt[r],rt[0],s[n] ^ x)) << '\n';
            } else {
                cout << query(rt[r],rt[l - 1],s[n] ^ x) << '\n';
            }
        }
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