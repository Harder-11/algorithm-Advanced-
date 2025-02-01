#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 205;
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
要使得队列形成一个凸字型,最少删除的元素
思路其实很好想,因为顶点处是最特殊的点,那么就枚举最高的那个同学
此时该同学的左边就是最长上升子序列,右边就是最长下降子序列
由于此时i必须选,那么就不是单纯的最长上升序列
*/

int n,ans;
int a[N];
//f是看上升部分,g是下降部分
int f[N],g[N];

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++){
        f[i] = g[i] = 1;
    }
    for(int i = n - 1;i >= 1;i--){
        for(int j = i + 1;j <= n;j++){
            if(a[i] > a[j] && f[i] <= f[j] + 1){
                f[i] = f[j] + 1;
            }
        }
    }
    for(int i = 2;i <= n;i++){
        for(int j = 1;j < i;j++){
            if(a[i] > a[j] && g[i] <= g[j] + 1){
                g[i] = g[j] + 1;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        //由于前面和后面都算了一次i位置,所以要-1
        ans = max(ans,f[i] + g[i] - 1);
    }
    //这里求的是出列的人数
    cout << n - ans << '\n';
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