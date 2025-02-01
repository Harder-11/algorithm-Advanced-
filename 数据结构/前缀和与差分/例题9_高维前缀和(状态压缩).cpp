#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2000005;
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
有N个物品,第i个物品的权值为ai,对于一个有k个物品的集合U = {ap1,ap2,ap3...apk}
我们定义集合U的价值为ap1 ^ ap2 ^ ap3 ... ^ apk
现在有M个询问,每个问题会给一个k个物品的集合U,想让你求出U所有子集的价值之和
U的所有超集的价值之和,在本问题中,全集的定义是这N个物品组成的集合

思路:高维前缀和(SOSDP)
sum over subsets,子集前缀和
那么使用状态压缩即可,a[1 << 20],代表的每一维是0/1
*/

int n,m,mx,k,x;
//pre用来求子集,suf用来求超集
ll pre[N],suf[N],a[N];

void solve(){
    cin >> n >> m;
    mx = (1 << n);
    for(int i = 0;i < n;i++) cin >> a[i];
    for(int i = 0;i < mx;i++){
        ll sum = 0;
        for(int j = 0;j < n;j++){
            //二进制位包含,说明就是此时集合的价值
            if(i & (1 << j)) sum ^= a[j];
        }
        pre[i] = sum;
        suf[i] = sum;
    }
    for(int i = 0;i < n;i++){
        for(int j = 0; j < mx;j++){
            if(j & (1 << i)) pre[j] += pre[j ^ (1 << i)];
            else suf[j] += suf[j ^ (1 << i)];
        }
    }
    while(m--){
        cin >> k;
        int q = 0;
        for(int i = 0;i < k;i++){
            cin >> x;
            q |= (1 << (x - 1));
        }
        cout << pre[q] << " " << suf[q] << '\n';
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