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
网络流基本概念:
若有向G=<V,E>满足下面的条件:
1.有且仅有一个顶点S,它的入度为0,即d-(S)=0,这个顶点S被称为源点
2.有且仅有一个顶点T,它的出度为0,即d+(T)=0,这个顶点T被称为汇点
3.每一条弧都有非负数,叫做该边的容量,边(vi,vj)的容量用cij来表示
则称为网络流图,记作G=<V,E,C>

可行流:
对于网络流G,每一条弧都给定一个非负数fij,这一组数满足下面三条件的时候称为这网络的可行流,用f表示
1.每一条弧(i,j)都有fij <= Cij
2.流量平衡:除开源点和汇点以外的所有点vi,都有:Σ(j)f(ij)=Σ(k)f(jk)(进 = 出)
3.对于源点S和汇点T有,Σi(f(Si)) = Σj(f(jT)) = V(f)(S输出的流量 = T输入的流量)

可改进路(增广路)
给定一个可行流f={fij},若fij=cij,那么称<vi,vj>为饱和弧,否则称<vi,vj>为非饱和弧
若fij=0,则为零流弧,否则称<vi,vj>为非零流弧
定义一条道路P,起点是S,终点是T,把P上所有与P方向一致的弧称为正向弧,正向弧的全体记为P+
把P上所有与P方向相悖的弧定义为反向弧,反向弧的全体定义为P-
给定一个可行流f,P是从S到T的一条道路,如果满足:
fij是非饱和流,并且<i,j>∈P+;fij是非零流,并且<i,j>∈P-
那么称P是f的一条可改进路(增广路),之所以被称为可改进,是因为可改进路上的弧的流量通过一定的规则
修改可以使整个图的流量变大

残留网
剩余的容量 + 反向平衡的容量共同构成了残留网络
对于残留网的定义:在不超过容量c(u,v)的条件下,从u到v之间可以压入的额外网络流量
就是(u,v)的残留容量,公式定义为:cf(u,v)=c(u,v)-f(u,v),而残留网Gf=(V,Ef)

割切
G=<V,E,C>是已知的网络流图,设U是V的一个子集,W=V/U(V对U的补集),满足SU,TW
即U,W把V分为两个不相交的集合,且源点和汇点分属不同的集合
对于弧尾在U,弧头在W的弧所构成的集合叫做割切,用(U,W)表示
把割切中所有弧的容量之和叫做此割切的容量,记错C(U,W)

流量算法基本理论:
1.对于已知的网络流图,设任意一可行流f,任意一个割切为(U,W),必有V(f)<=C(U,W)
2.可行流f是最大流的充分必要条件是:f中不存在增广路
3.整流定理:如果网络流中所有的弧的容量都是整数,则存在整数流的最大流
4.最大流最小割定理:最大流等于最小割,即maxV(f)=minC(U,W)
*/

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