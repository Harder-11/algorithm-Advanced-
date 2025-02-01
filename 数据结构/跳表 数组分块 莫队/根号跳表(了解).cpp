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
跳表又称为ST算法,本质是一种倍增算法
倍增是一种二进制待定系数的二分思路,它在一定程度上笔l,r,mid的形式需要考虑的边界问题更少,但是常数更大
倍增比l,r,mid形式更好写,只用一行即可
int x = -1;
for(int i = 16;~i;i--) if(check(x + (1 << i))) x += (1 << i);

显然,对于l,r,mid形式,在连续空间更实用,因为可以用l,r来轻易获取mid
在树上问题就更适合ST表

跳表的优势:预处理时间是NlogN,但是查询是O(1)
那么如果数据量是1e5,查询是1e7并且强制在线,这时候跳表就非常实用

跳表有两种:
1.步长为根号的根号跳表
2.步长而二进制的倍增跳表

根号跳表的实现(类似于BSGS算法)
先开一个叫做ST_small[N][sqrt(N)]的二维数组
ST_small[i][j]表示以i为起点,向后延续j的区间信息
接下来开一个叫做ST_big[N][sqrt(N)]的二维数组
ST_big[i][j]表示以i为起点,向后延伸长度为j * sqrt(N)的区间信息
显然ST_big[i][1] = ST_small[i][sqrt(N)]

比如假设有一个ST_small[100][10],同样ST_big也是100 * 10
ST_small[1][1]表示的1~1的区间极大值,ST_small[1][2]表示1~2的区间极大值.....一直到ST_small[1][10]表示1~10的区间极大值
那么此时只需要遍历N * sqrt(N)次就可以填满ST_small,每次ST_small[i][j] = max(ST_small[i][j - 1],a[j])
此时ST_big[1][1]表示1~10的区间极值,ST_big[1][2]表示1~20的区间极值.....ST_big[1][100]表示区间1~100的区间极值
显然有ST_big[i][1] = ST_small[i][sqrt(N)],那么有
ST_big[1][1] = ST_small[1][10],ST_big[1][2] = ST_big[1][1],ST_small[1 + 10][10]....
那么最后对于任意一段查询max[l,r],就可以转化为
max(ST_big[l][len / sqrt(N)],ST_small[l + len / sqrt(N) * sqrt(N)][len - len / sqrt(N) * sqrt(N)])
实际就是比如要求[1,65],就是求max(ST_big[1][6],ST_small[1 + 60][5]),就是上述式子
根号跳表相比于二进制跳表更实用于区间最大字段和的维护,因为如果用二进制跳表的话,会分为logN块
每两块区间都要进行断点左右部分的相加求和,复杂度有可能不如根号跳表
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