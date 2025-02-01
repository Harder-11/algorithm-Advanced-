#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 5005;
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
新年树上有n层灯,第i层有li盏灯,需要满足
1.每层中相邻两盏灯的颜色不同
2.相邻两层使用的颜色集合不同
有m种颜色的灯,求装饰的方案数,对p取模
1 <= n,m <= 1e6,1 <= li <= 5000,L = Σ(i=1,n)li <= 1e7,2 <= p <= 1e9

思路:我们假设从上到下每一层为l1,l2,l3...ln
首先,对于同一层,我们假设一层中用了k种颜色,这一层的方案数我们假设为f(l,k)(其中l为长度,k为颜色数)
那么此时f(l,k)可以用动态规划的方法进行求解
具体来说,有l盏灯,用k种颜色的方案数
如果前面的l-1盏灯只用了k-1种颜色,那么最后一盏灯就要用剩下的那一种颜色
如果前面的l-1盏灯已经使用了k种颜色,那么最后一盏灯只需要不与前面那盏灯颜色相同即可
所以转移方程就是f(l,k) = f(l-1,k-1) + (k-1)*f(l-1,k),复杂度是O(l^2)
然后,我们考虑上下层的关系,我们假设没有限制条件那么此时对于l1层一共就有方案数:
s1 = f(l1,1)*A(m,1)+f(l1,2)*A(m,2)+f(l1,3)*A(m,3)+....+f(l1,l1)*A(m,l1);
我们此时可以用g(i,j)表示当前是第i层,用了j种颜色的方案数
那么此时的转移应该是g(i,j) = f(li,j)*(s(i-1)-g(i-1,j)*j!)
最后si = Σ(j=1,li)g(i,j)*A(m,j),sn就是最后的答案
*/

//f,g利用滚动数组进行递推
ll C[N],fac[N],dp[N][N],f[N],g[N];
ll n,m,p;
ll l[2000005];

ll power(ll a,ll b){
    ll res = 1;
    while(b){
        if(b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

void solve(){
    cin >> n >> m >> p;
    for(int i = 1;i <= n;i++) cin >> l[i];
    C[0] = fac[0] = 1;
    for(int i = 1;i <= 5000;i++){
        C[i] = C[i - 1] * (m - i + 1) % p;
        fac[i] = fac[i - 1] * i % p;
    }
    dp[0][0] = 1;
    for(int i = 1;i <= 5000;i++){
        for(int j = 0;j <= 5000;j++){
            if(j > 1) dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j - 1) % p) % p;
            dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % p;
        }
    }
    f[0] = 1;
    for(int i = 1;i <= n;i++){
        ll sum = 0;
        for(int j = 0;j <= l[i - 1];j++){
            sum = (sum + f[j]) % p;
        }
        for(int j = 0;j <= l[i];j++){
            g[j] = sum * C[j] % p * dp[l[i]][j] % p;
            if(j <= l[i - 1]) g[j] = (g[j] + p - f[j] * fac[j] % p * dp[l[i]][j] % p) % p;
        }
        for(int j = 0;j <= l[i];j++) f[j] = g[j];
    }
    ll ans = 0;
    for(int i = 0;i <= l[n];i++){
        ans = (ans + f[i]) % p;
    }
    cout << ans << '\n';
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