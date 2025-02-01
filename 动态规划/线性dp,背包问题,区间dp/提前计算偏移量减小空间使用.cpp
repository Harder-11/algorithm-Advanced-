#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 30005;
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
(CF505C)
一共有30001个岛屿,下标为0~30000,有些岛屿有宝藏
你从0往下标大的方向跳,每一步跳的距离为d,如果上一步跳的距离为l
这一步就可以跳l-1或者l+1(距离必须>0),问最多可以拿到多少宝藏

思路:f[i][j]:代表人在i号岛屿,上一步跳的j距离的情况下最多拿到的宝藏
那么转移也很好写,f[i][j] = max(f[i-j][j-1],f[i-j][j+1])+a[i]
但是此时d<=30000,空间会爆,那么必须使用滚动数组优化
而d的偏移量最多不会超过250(每次都+1或者-1或者0的情况),那么就没有必要用j这一维表示跳的距离
而是表示d的偏移量,这样j这一维就可以开的很小了,那么开到f[N][500]就足够了
那么此时的转移方程就变成了f[i][o] = max(f[i-(d+o)][o-1],f[i-(d+o)][o+1],f[i-(d+0)[o]]) + v[i]
*/

int mx = 320;
int n,d,a[N],ans,in;
int f[N][555];

void solve(){
    cin >> n >> d;
    for(int i = 1;i <= n;i++){
        cin >> in;
        a[in]++;
    }
    memset(f,-0x3f,sizeof f);
    ans = f[d][mx] = a[0] + a[d];
    for(int i = d + 1;i <= in;i++){
        for(int j = -mx;j <= mx;j++){
            if(d + j > 0 && d + j <= i){
                f[i][j + mx] = max({f[i][mx + j],f[i - (d + j)][mx + j - 1],f[i - (d + j)][mx + j + 1],f[i - (d + j)][mx + j]}) + a[i];
            }
            ans = max(ans,f[i][mx + j]);
        }
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