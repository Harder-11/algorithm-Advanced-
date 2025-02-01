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
一共有n个数,第i个数为xi
xi可以取[li,ri]中任意一个值
设S = Σ(xi^2),求S的种类数
1 <= n,li,ri <= 100

思路:可以利用常规的动态规划:
令f[i][j]:前i个数能否恰好等于j,f[i][j]=f[i-1][j-xi^2]
那么此时枚举j就是100^2 * 100 * n^3肯定会MLE还会TLE

此时采取二进制优化dp,由于最大的数可以到1e6(100^2 * 100)
那么就用1e6长度的01串来代替数字,最后统计1的个数即可(1个1就代表可能出现的数字)
因为每次<<(k*k)之后都是添加1个1(相当于就把当前的数字加入了bitset当中)
这样时间复杂度就是n^4/32,可以通过
*/

int n;
bitset<1000005> f[110];

void solve(){
    //0个元素组成0有1种情况
    cin >> n;
    f[0][0] = 1;
    for(int i = 1;i <= n;i++){
        int l,r;
        cin >> l >> r;
        for(int k = l;k <= r;k++){
            f[i] |= f[i - 1] << (k * k);
        }
    }
    //bitset的count(),统计有多少个1
    cout << f[n].count() << '\n';
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