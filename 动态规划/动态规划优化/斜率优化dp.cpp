#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs = 1331;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
斜率优化dp
本题题意就是有n个玩具,第i个玩具的价值为ci,要求把这n个玩具排成一排,分成若干段
对于每一段[l,r],代价为(r-l+Σ(i=l,r)ci - L)^2,其中L是一个常量,求分段的最小代价
那么对于朴素的dp做法,令fi表示前i个物品,分若干段的最小代价
状态转移方程就是fi=min(j<i){fj+(i-(j+1)+pre(i)-pre(j)-L)^2} 
其中pre(i)表示前i个数的和,即Σ(j=1,i)cj,时间复杂度是O(n^2)(j遍历和i遍历,所以是O(n^2))

那么考虑简化上述方程式:令si=pre(i)+i,L'=L+1
那么fi=min(j<i){fj+(si-sj-L')^2},将与j无关的移到外面得到以下式子:
fi-(si-L')^2 = min(j<i){fj+sj^2+2sj(L'-si)}
考虑一次函数的斜截式y=kx+b,将其移项得到b=y-kx,我们将与j有关的信息表示为y的形式
把同时与i,j有关的信息表示为kx,把要最小化的信息(与i有关的信息)表示为b,也就是截距
具体的,设xj = sj,yj = fj + sj^2,ki = -2(L'-si),bi = fi - (si - L)^2
那么式子就可以写成bi = min(j<i){yj - kixj},把(xj,yj)看做平面上的点,ki看做斜率
bi表示一条过(xj,yj)的斜率为ki的直线的截距,问题转化为了,选择合适的j(1<=j<i)
最小化直线的截距(因为转化为了bi=min(j<i){yj-kixj})
这里需要用到凸包的知识,容易发现,可能让bi取到最小值的点一定在下凸壳上,因此在寻找p的时候
我们不需要枚举所有的i-1个点,只需要考虑凸包上面的点,而本题中ki随着i的增加而递增
(因为ki=-2(L'-pre(i)+1)=2pre(i)-2L'-2,i越大肯定前缀和越大)
因此用单调队列维护凸包,具体的设K(a,b)表示过(xa,ya)和(xb,yb)的直线斜率
考虑队列ql,ql+1...qr,维护的是下凸壳的点,那么对于l<i<r始终有K(q(i-1),qi)<K(qi,q(i+1))成立
我们维护一个指针e来计算bi的最小值,我们需要找到一个K(q(e-1),qe)<=ki<K(qe,q(e+1))
的e(当e=l或者r需要特别判断),这是就有p=qe,即qe是i的最优决策点
由于ki是单调递增的,那么e的移动次数是均摊O(1)的
在插入一个点(xi,yi)的时候,我们要判断是否K(q(r-1),qr) < K(qr,i)
如果不等式不成立就将qr弹出,直到等式满足,然后将i插入q的队尾
这样就把dp的时间复杂度降到了O(n)
概括一下就是以下三步:
1.将初始状态入队
2.每次使用一条和i相关的直线f(i)去切维护的凸包,找到最优决策,更新dpi
3.加入状态dpi,如果一个状态(即凸包上的一个点)在dpi加入之后不再是凸包上面的点
需要在dpi加入之前将其剔除
*/

int n,L;
double sum[N],dp[N];
int head,tail,Q[N];
double a(int i){
    return sum[i] + i;
}
double b(int i){
    return a(i) + L + 1;
}
double X(int i){
    return b(i);
}
double Y(int i){
    return dp[i] + b(i) * b(i);
}
double slope(int i,int j){
    return (Y(i) - Y(j)) / (X(i) - X(j));
}

void solve(){
    cin >> n >> L;
    for(int i = 1;i <= n;i++){
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    head = tail = 1;
    for(int i = 1;i <= n;i++){
        while(head < tail && slope(Q[head],Q[head + 1]) < 2 * a(i)) head++;
        dp[i] = dp[Q[head]] + (a(i) - b(Q[head])) *(a(i) - b(Q[head]));
        while(head < tail && slope(i,Q[tail - 1]) < slope(Q[tail - 1],Q[tail])) tail--;
        Q[++tail] = i;
    }
    cout << (ll)dp[n];
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