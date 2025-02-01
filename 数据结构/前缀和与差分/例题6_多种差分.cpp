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
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
有三种操作,第一种是从位置pos开始依次往右给每个数+1
第二种是从位置pos开始依次往右给每个数+1,2,3....n
第三种是从pos位置开始依次往右给每个数+1,4,9....n^2

显然第一种和第二种分别是普通差分和等差数列差分,那么只需要对数组进行1次/2次前缀和操作即可
对于第三种操作就是平方差分,能发现对于平方数1,4,9,16....n^2
它的差分数组就是1,3,5,7,.....变成了一个等差数列,那么本质就是求1,1,0,0,0,0,0,0,....的三次前缀和即可
*/
ll n,m,d1[N],d2[N],d3[N];

void pre_sum(ll a[]){
    for(int i = 1;i <= n;i++){
        a[i] = (a[i] + a[i - 1]) % mod;
    }
}

void solve(){
    memset(d1,0,sizeof d1);
    memset(d2,0,sizeof d2);
    memset(d3,0,sizeof d3);
    cin >> n >> m;
    int op,pos;
    while(m--){
        cin >> op >> pos;
        if(op == 1){
            d1[pos]++;
        } else if(op == 2){
            d2[pos]++;
        } else {
            d3[pos]++;
            d3[pos + 1]++;
        }
    }
    pre_sum(d1);
    pre_sum(d2);
    pre_sum(d2);
    pre_sum(d3);
    pre_sum(d3);
    pre_sum(d3);
    for(int i = 1;i <= n;i++){
        cout << (d1[i] + d2[i] + d3[i]) % mod << " ";
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}