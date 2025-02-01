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