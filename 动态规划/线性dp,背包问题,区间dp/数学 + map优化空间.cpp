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
(CF510)
给出N个不同的数,去第i个数的代价为Ci,求取出若干使得其最大公约数为1的最小代价
1 <= n <= 300,ci <= 1e9
显然,定义方程f[i][j]表示前i个数,gcd = j的最小代价,是一个背包问题
那么就是选和不选的问题,如果不选,直接转移f[i][j]=f[i-1][j]
如果选择a[i],那么此时最大公约数会变成j,设原先的最大公约数是k,那么就是gcd(k,a[i])=j
f[i][j] = min(f[i-1][j],f[i-1][k] + c[i]),其中gcd(k,a[i]) = j
但是每个元素的值是1e9,明显会MLE,但是在求若干个数的最大公约数时,得到的数值并不多
那么就用map存即可
*/
int a[N],b[N];
map<int,int> mp;
int n;

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) cin >> b[i];
    for(int i = 1;i <= n;i++){
        for(auto x : mp){
            int now = __gcd(a[i],x.first);
            int val = x.second + b[i];
            //如果不存在当前的gcd值,那么就新开一个(动态开点减小空间复杂度)
            if(mp[now] == 0){
                mp[now] = val;
                //有当前gcd值了就更新为更小的
            } else {
                mp[now] = min(mp[now],val);
            }
        }
        //不要忘记还要把本身加入map当中
        if(mp[a[i]] == 0) mp[a[i]] = b[i];
        else mp[a[i]] = min(mp[a[i]],b[i]);
    }
    if(mp[1] == 0) cout << -1 << '\n';
    //最后输出gcd==1的即可
    else cout << mp[1] << '\n';
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