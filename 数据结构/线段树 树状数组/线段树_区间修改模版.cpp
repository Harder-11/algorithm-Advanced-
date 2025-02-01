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

线段树区间修改,此时如果把所有的叶节点全部修改然后再向上更新,这样每次都是O(n)复杂度,总复杂度会到O(nq),无法接受
那么引入lazyTag
*/

int a[N],n;

struct tnode {
    ll sum,lazy;
    int l,r;
};

struct segTree {
    tnode t[N << 2];
    void pushdown(int u){
        //当发现t[u].lazy不为0,就把懒标记下传
        if(t[u].lazy){
            t[u].sum += t[u].lazy * (t[u].r - t[u].l + 1);
            //不是叶子节点才往下传,否则没意义了
            if(t[u].l != t[u].r){
                t[ls].lazy += t[u].lazy;
                t[rs].lazy += t[u].lazy;
            }
            //即可把当前节点的懒标记更新为0
            t[u].lazy = 0;
        }
    }
    void pushup(int u){
        pushdown(ls);
        pushdown(rs);
        t[u].sum = t[ls].sum + t[rs].sum;
    }
    void build(int u,int l,int r){
        t[u].l = l;
        t[u].r = r;
        if(l == r){
            t[u].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls,l,mid);
        build(rs,mid + 1,r);
        pushup(u);
    }
    //线段树的区间修改
    void change(int u,int l,int r,ll val){

        //这里要注意,如果对于纯加法修改是没有问题的
        //但是如果存在加法和乘法的混合运算就会出问题,由于时效性
        //如果不加这一段就可能会把加法和乘法搞混,导致下传的数出现偏差
        pushdown(u);
        if(l == t[u].l && r == t[u].r){
            t[u].lazy += val;
            return;
        }
        int mid = (t[u].l + t[u].r) >> 1;
        if(r <= mid) change(ls,l,r,val);
        else if(l >= mid + 1) change(rs,l,r,val);
        else {
            change(ls,l,mid,val);
            change(rs,mid + 1,r,val);
        }
        pushup(u);
    }

    ll sum(int u,int l,int r){
        pushdown(u);
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