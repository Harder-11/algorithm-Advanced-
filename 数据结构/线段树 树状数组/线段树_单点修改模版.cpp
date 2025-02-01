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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
对于线段树的学习,最好在思想上面向对象,在代码上面按需面向对象或者直接面向过程
线段树中的对象:1.线段树 2.区间(线段) 3.懒标记(lazy tag)

对于一个区间,一般这样定义:
struct tree {
    int l,r;
    DATA(维护的数据)
    LAZY(懒标记)
}tr[N << 2];

线段树的单点修改(使用最多)
单点修改不需要懒标记
*/

int a[N],n;

struct tnode {
    ll sum,lazt;
    int l,r;
};

struct segTree {
    tnode t[N << 2];
    //用mp数组记录叶子节点在线段树中的位置
    //用来快速找到叶子节点并且进行单点修改(利用满二叉树的性质)
    int mp[N];
    void pushup(int u){
        t[u].sum = t[ls].sum + t[rs].sum;
    }
    void build(int u,int l,int r){
        t[u].l = l;
        t[u].r = r;
        if(l == r){
            mp[l] = u;
            t[u].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls,l,mid);
        build(rs,mid + 1,r);
        pushup(u);
    }
    ll sum(int u,int l,int r){
        if(t[u].l == l && t[u].r == r){
            return t[u].sum;
        }
        int mid = (t[u].l + t[u].r) >> 1;
        //如果是r比mid还小,那么直接在左部分查询
        //如果l比mid大,那么直接在右部分查询
        if(r <= mid) return sum(ls,l,r);
        else if(l >= mid + 1) return sum(rs,l,r);
        //如果横跨了整个区间,那么把查询区间也切开
        else return sum(ls,l,mid) + sum(rs,mid + 1,r);
    }
    //单点修改,利用二叉树的性质,父节点的编号一定是x / 2
    void update(int x,int val){
        x = mp[x];
        t[x].sum += val;
        while(x >>= 1) pushup(x);
    }
};

void solve(){

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