#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
const int N = 1000005;
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
李超线段树:李超线段树是用来维护空间一次函数的结构
定义线段树中的一个节点[l,r]所表示的区间为一个空间的"域"的话
定义最优势直线为区间为整个区间自上而下覆盖范围最广的曲线
线段树中存储的信息,实际上是每个空间域内最优势的一次函数

区间[l,r]中存放一个一次函数,f(x) = kx + b,注意:每个节点都只放一个一次函数
放的直线是[l,r]中的最优势直线(最优势直线指的是,假设平面有两条直线,假设交点是mid',[l,r]区间的中点是mid,
看mid'和mid的关系,通过mid < mid',那么左边在上方的直线是优势直线,否则就是右边在上方的直线是优势直线)通俗来说就是在上方的区间更大的就是优势直线
过程是:假设[l,r]是[1,8],先插入y = 0x + 5,那么此时每个根节点是y = 0x + 5
再插入y = x + 2,此时两条直线在x = 3相交,那么此时[1,3]就是y = 0x + 5更大,[4,8]是y = x + 2更大
又因为在李超线段树里面每个区间只有一个线段,那么此时y = x + 2成为了优势线段,那么此时[1,8]这个区间变成y = x + 2
然后y = 0x + 5往下推到[1,4]区间
对于查询:假设查询x = 1,那么此时在根节点遇到一个直线y = x + 2 = 3,然后往左递归遇到y = 0x + 5,此时算出y = 5 > 3
那么此时说明y = 0x + 5更优势
查询x = 4同理,y = 6就是最终答案

李超线段树常用在斜率优化dp里面,如果斜率不单调或者点不单调,此时就需要借助李超线段树或者CDQ分治来解决

题目大意:平面空间中有如干条直线,每条直线可以写成y = ki * x + bi,现在有两个操作
1.插入一条方程为y' = ki * x' + bi的直线
2.给点一个正整数x,x ∈ [1,N],查询现在所有直线中令x = x',y'的最大值和最小值

*/

struct Line {
    ll k,b;
    ll val(ll x){
        return k * x + b;
    }
    Line(ll _k = 0,ll _b = 0){
        k = _k;
        b = _b;
    }
};

double Line_cross(const Line &A,const Line &B){
    return (B.b - A.b) * 1.0 / (A.k - B.k);
}

struct LC_SegTree {
    ll cross_x(const Line &A,const Line &B){
        return (B.b - A.b) / (A.k - B.k);
    }
    struct tree_node {
        int l,r;
        bool vis;
        bool has_line;
        Line lin;
    }tr[N << 2];
    void build(int u,int l,int r){
        tr[u].l = l;
        tr[u].r = r;
        tr[u].vis = false;
        tr[u].has_line = false;
        if(l != r){
            int mid = (l + r) >> 1;
            build(ls,l,mid);
            build(rs,mid + 1,r);
        }
    }
    //李超线段树的核心就是insert方法,每次两两直线进行比较,输的下传,赢的就存储在当前区间
    void insert(int u,int l,int r,Line x){
        tr[u].vis = true;
        //此时是处理左右端点正好对应区间的情况
        if(l == tr[u].l && r == tr[u].r){
            //如果此时区间里面没有直线存在,那么直接把x加入到这段区间里面
            if(!tr[u].has_line){
                tr[u].has_line = 1;
                tr[u].lin = x;
            }
            //如果此时整个区间的val都比x的val更大,那么x就插不进来
            //直接return
            if(tr[u].lin.val(tr[u].l) >= x.val(tr[u].l) && 
                tr[u].lin.val(tr[u].r) >= x.val(tr[u].r)){
                return;
            }
            //如果此时整个区间原本直线的val < x.val,那么直接把当前区间的直线换为x,然后reutrn
            if(tr[u].lin.val(tr[u].l) < x.val(tr[u].l) && tr[u].lin.val(tr[u].r) < x.val(tr[u].r)){
                tr[u].lin = x;
                return;
            }
            //此时的情况就是有部分是x更大,有部分是原本的直线更大的情况
            //那么此时就比较mid和两条直线的交点处谁更大
            int mid = (tr[u].l + tr[u].r) >> 1;
            //如果直线的交点处 <= mid,并且还有x的斜率更小
            //画图可以知道,说明此时的原本的直线是优势直线,那么递归左边(因为交点在mid左边,说明右边全部是原本直线更大,那么不用递归右边)
            if(cross_x(x,tr[u].lin) <= mid){
                if(x.k < tr[u].lin.k) insert(ls,l,mid,x);
                //如果x斜率更大,说明x是优势直线
                //那么此时递归左边,并且把当前区间的优势直线换为x
                //注意这里递归的时候x该为了tr[u].lin(败者)往下递归
                else {
                    insert(ls,l,mid,tr[u].lin);
                    tr[u].lin = x;
                }
                //else和上面的情况是一个道理
            } else {
                if(x.k > tr[u].lin.k) insert(rs,mid + 1,r,x);
                else {
                    insert(rs,mid + 1,r,tr[u].lin);
                    tr[u].lin = x;
                }
            }
            //如果左右端点和区间的左右端点没有对齐,那么就是普通线段树的处理方式
            //递归左右两边即可
        } else {
            int mid = (tr[u].l + tr[u].r) >> 1;
            if(r <= mid) insert(ls,l,r,x);
            else if(l >= mid + 1) insert(rs,l,r,x);
            else {
                insert(ls,l,mid,x);
                insert(rs,mid + 1,r,x);
            }
        }
    }
    void clear(int u){
        tr[u].vis = 0;
        tr[u].has_line = 0;
        if(tr[u].l != tr[u].r){
            if(tr[ls].vis) clear(ls);
            if(tr[rs].vis) clear(rs);
        }
    }
    ll query(int u,int x){
        //if(!tr[u].vis) return -INF;
        ll res;
        if(!tr[u].has_line) res = -INF;
        else res = tr[u].lin.val(x);
        if(tr[u].l == tr[u].r) return res;
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(x <= mid) return max(res,query(ls,x));
        else return max(res,query(rs,x));
    }
}seg_up,seg_down;

int n,m,op,k,b,x;

void solve(){
    cin >> n >> m;
    seg_up.build(1,1,n);
    seg_down.build(1,1,n);
    while(m--){
        cin >> op;
        if(op == 0){
            cin >> k >> b;
            seg_up.insert(1,1,n,Line(k,b));
            seg_down.insert(1,1,n,Line(-k,-b));
        } else {
            cin >> x;
            cout << seg_up.query(1,x) << " " << -seg_down.query(1,x) << '\n';
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