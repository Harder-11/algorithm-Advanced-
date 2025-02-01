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
给出一个长度为n的序列和m次操作
1 l r:询问区间[l,r]内的元素和
2 l r:询问区间[l,r]内的平方和
3 l r x:将区间[l,r]内的每个元素都乘上x
4 l r x:将区间[l,r]内的每个元素都加上x
所有询问的答案都在long long范围以内

本题由于同时包含了乘法和加法运算,懒标记必须分开处理,所以需要一些辅助函数
其他的query,change函数等保持不变

对于区间来说,维护Σ(l,r)xi Σ(l,r)xi^2
对于lazy标记,x -> a2x + b2(乘法和加法)
如果此时乘上一个a1,那么a = a1 * a2,b = a1 * b2
如果是加上一个b1,那么a = a2,b = b1 + 
那么明显对乘法,如果有b2是不满足的,对加法都满足
*/

ll A[N];

struct tnode {
    int l,r;
    //sum[0]是区间和
    //sum[1]是区间平方和
    //因为有加有乘,我们就表示为ax + b
    //lazy[0]表示a,lazy[1]表示b
    ll sum[2],lazy[2];
};

struct segTree {
    tnode tr[N << 2];
    //新增一个标记初始化的函数
    void init_lazy(int u){
        tr[u].lazy[0] = 1;
        tr[u].lazy[1] = 0;
    }

    void union_lazy(int fa,int ch){
        ll tmp[2];
        //a = a1 * a2
        //b = a1 * b2 + b1
        tmp[0] = tr[fa].lazy[0] * tr[ch].lazy[0];
        tmp[1] = tr[fa].lazy[0] * tr[ch].lazy[1] + tr[fa].lazy[1];
        tr[ch].lazy[0] = tmp[0];
        tr[ch].lazy[1] = tmp[1];
    }

    //处理lazy的难点在于,本层的lazy需要往下推,但是下面一层也存在tag
    //那么该怎么处理?
    //由于求的是Σ(l,r)(axi + b),b都是一样的,那么原式可以化简为
    //(r - l + 1)b + a * Σ(l,r)xi
    //同时维护的是Σ(l,r)(ax + b)^2,展开化简得到
    //(r - l + 1)b^2 + a^2 * Σ(l,r)(xi^2) + 2ab * Σ(l,r)xi
    void cal_lazy(int u){
        tr[u].sum[1] = tr[u].lazy[0] * tr[u].lazy[0] * tr[u].sum[1] +
        tr[u].lazy[1] * tr[u].lazy[1] * (tr[u].r - tr[u].l + 1) + 
        tr[u].lazy[0] * tr[u].lazy[1] * 2 * tr[u].sum[0];
        //sum[0]就是l到r的区间和,就是(r - l + 1) * b,b就是lazy[1]
        //然后a就是lazy[0] * sum[0]
        tr[u].sum[0] = tr[u].lazy[0] * tr[u].sum[0] + tr[u].lazy[1] * (tr[u].r - tr[u].l + 1);
    }

    void pushdown(int u){
        if(tr[u].lazy[0] != 1 || tr[u].lazy[1] != 0){
            cal_lazy(u);
            //这里标记不能直接懒标记往下传,需要union
            if(tr[u].l != tr[u].r){
                union_lazy(u,ls);
                union_lazy(u,rs);
            }
            init_lazy(u);
        }
    }
    void update(int u){
        pushdown(ls);
        pushdown(rs);
        tr[u].sum[0] = tr[ls].sum[0] + tr[rs].sum[0];
        tr[u].sum[1] = tr[ls].sum[1] + tr[rs].sum[1];
    }
    void build(int u,int l,int r){
        tr[u].l = l;
        tr[u].r = r;
        init_lazy(u);
        if(l == r){
            tr[u].sum[0] = A[l];
            tr[u].sum[1] = A[l] * A[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls,l,mid);
        build(rs,mid + 1,r);
        update(u);
    }
    //op是为了将加和乘都写在一个函数里面,op用来识别是哪种操作
    void change(int u,int l,int r,ll val,int op){
        pushdown(u);
        if(l == tr[u].l && r == tr[u].r){
            tr[u].lazy[op] = val;
            return;
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r <= mid) change(ls,l,r,val,op);
        else if(l >= mid + 1) change(rs,l,r,val,op);
        else {
            change(ls,l,mid,val,op);
            change(rs,mid + 1,r,val,op);
        }
        update(u);
    }
    //同样这里op也是用来区分求的平方和还是区间累加和
    //op = 0代表累加和,op = 1代表平方和
    ll sum(int u,int l,int r,int op){
        pushdown(u);
        if(tr[u].l == l && tr[u].r == r){
            return tr[u].sum[op];
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r <= mid) return sum(ls,l,r,op);
        else if(l >= mid + 1) return sum(rs,l,r,op);
        else return sum(ls,l,mid,op) + sum(rs,mid + 1,r,op);
    }
};

segTree ST;
int n,m,op,l,r;
ll x;

void solve(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> A[i];
    ST.build(1,1,n);
    for(int i = 1;i <= m;i++){
        cin >> op >> l >> r;
        if(op >= 3){
            cin >> x;
            ST.change(1,l,r,x,op - 3);
        } else {
            cout << ST.sum(1,l,r,op - 1) << '\n';
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