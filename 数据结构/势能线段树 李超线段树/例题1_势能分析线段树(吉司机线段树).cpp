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
关于势能分析:
对于求N个数的gcd,直觉复杂度是O(NlogC)
但是实际是O(N + logC)因为两两求gcd时,gcd的值是一个递减的,不会每次求gcd的复杂度都到O(logC)

势能均摊复杂度:
在N个数求gcd问题,总时间复杂度为O(N + logC),那么势能均摊复杂度就是O(N + logC) / N
求解出来就是O(1),那么我们称gcd函数的势能均摊复杂度就是O(1)
那么用线段树维护gcd的方法的时间复杂度就是O(NlogN)而并非O(N(logN)^2)
因为求gcd的过程被均摊了,时间复杂度为O(1)

在线段树维护区间开平方操作的时候,我们能不能用懒标记把区间的开平方操作给懒掉?
为什么不可以?
可以想一下懒标记的几个关键函数:init_lazy(),push_down(),tag_union(),cal_lazy();
---问题出现在cal_lazy(),虽然有区间和,但是你求不出开平方之后的区间和
因为数字不同开平方之后的结果是不一样的
那么只能把[l,r]所有的数字进行开平方然后加起来,但是如果假设区间的数字都相同,那么就可以进行cal_lazy()
显然,线段树上所有的数字进行开平方之后都会变成1(一开始都是正整数的情况下)
所以我们把线段树当做普通数组来用,暴力开平方,直到所有数字都变成1了再借助lazy_tag,我们可以粗略估计
对于1e9,只要开6次根号并且向下取整,那么开6次方就会变成1,所以线段树每次暴力是不会超过6次
那么我们维护区间的最大值作为势能来用,只要最大值都变成1,其他肯定都变成1了
所以复杂度大约是O(24N),24是因为最多开6次方,然后每个节点都要开方,线段树节点数是4N

如果修改一下本题,还要实现一个给区间[l,r]加上一个x该怎么办呢?
如果此时还是进行暴力区间加,然后再进行暴力开方,那么每次加完后开方的结点数最多会到2N个
那么此时的时间复杂度会退化到O(NM)
我们此时发现:此时区间的max - min的值定义为diff,此时的diff一定是单调递减的
*/

int n,m,l,r,x,A[N],op;

struct tnode {
    ll sum,mx,mn,lazy;
    int l,r;
};

struct SegTree {
    tnode tr[N << 2];
    ll cal_delta(ll x){
        return x - (ll)sqrt(x + 0.5);
    }
    void lazy_union(int fa,int ch){
        if(tr[fa].lazy){
            tr[ch].lazy += tr[fa].lazy;
        }
    }
    void cal_lazy(int u){
        if(tr[u].lazy){
            tr[u].sum += tr[u].lazy * (tr[u].r - tr[u].l + 1);
            tr[u].mx += tr[u].lazy;
            tr[u].mn += tr[u].lazy;
        }
    }
    void init_lazy(int u){
        tr[u].lazy = 0;
    }
    void pushdown(int u){
        if(tr[u].lazy){
            cal_lazy(u);
            if(tr[u].l != tr[u].r){
                lazy_union(u,ls);
                lazy_union(u,rs);
            }
            init_lazy(u);
        }
    }
    void update(int u){
        pushdown(ls);
        pushdown(rs);
        tr[u].sum = tr[ls].sum + tr[rs].sum;
        tr[u].mx = max(tr[ls].mx,tr[rs].mx);
        tr[u].mn = min(tr[ls].mn,tr[rs].mn);
    }
    void build(int u,int l,int r){
        tr[u].l = l;
        tr[u].r = r;
        if(l == r){
            tr[u].sum = A[l];
            tr[u].mn = A[l];
            tr[u].mx = A[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls,l,mid);
        build(rs,mid + 1,r);
        update(u);
    }
    void add(int u,int l,int r,ll val){
        pushdown(u);
        if(l > tr[u].r || r < tr[u].l) return;
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l == tr[u].l && r == tr[u].r){
            tr[u].lazy += val;
            return;
        }
        if(r <= mid) add(ls,l,r,val);
        else if(l >= mid + 1) add(rs,l,r,val);
        else {
            add(ls,l,mid,val);
            add(rs,mid + 1,r,val);
        }
        update(u);
    }
    void do_sqrt(int u,int l,int r){
        pushdown(u);
        if(l > tr[u].r || r < tr[u].l) return;
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l == tr[u].l && r == tr[u].r){
            //这里必须写改变量是一样的
            //否则会有4 3 4 3 .....这种案例使得吉司机线段树复杂度退化到O(mn)
            //因为这个案例的diff开根前后一直都是1,导致势能一直没有变,这样就会每次暴力开根
            if(cal_delta(tr[u].mx) == cal_delta(tr[u].mn)){
                tr[u].lazy -= cal_delta(tr[u].mx);
                return;
            }
            //继续递归到叶子,然后叶子一定会进入上述的开方操作里面,然后向上update
            //这样操作的结点个数就是logN个,最多操作6次,那么可以认为复杂度是(logN)^2
            do_sqrt(ls,l,mid);
            do_sqrt(rs,mid + 1,r);
            update(u);
            return;
        }
        if(r <= mid) do_sqrt(ls,l,r);
        else if(l >= mid + 1) do_sqrt(rs,l,r);
        else {
            do_sqrt(ls,l,mid);
            do_sqrt(rs,mid + 1,r);
        }
        update(u);
    }
    ll sum(int u,int l,int r){
        pushdown(u);
        if(l > tr[u].r || r < tr[u].l) return 0;
        if(tr[u].l == l && tr[u].r == r){
            return tr[u].sum;
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r <= mid) return sum(ls,l,r);
        else if(l >= mid + 1) return sum(rs,l,r);
        else {
            return sum(ls,l,mid) + sum(rs,mid + 1,r);
        }
    }
};

SegTree ST;

void solve(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> A[i];
    ST.build(1,1,n);
    while(m--){
        cin >> op;
        if(op == 1){
            cin >> l >> r;
            ST.do_sqrt(1,l,r);
        } else if(op == 2){
            cin >> l >> r >> x;
            ST.add(1,l,r,x);
        } else {
            cin >> l >> r;
            cout << ST.sum(1,l,r) << '\n';
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

