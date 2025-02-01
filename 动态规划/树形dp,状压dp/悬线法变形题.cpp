#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2005;
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
在01方阵当中找出其中最大的全0子矩阵
悬线法:对于矩形中每个1都有一个向上能到达另一个1的最远距离
对于图里面的每一条悬线都有可能成为矩形的上下界
那么就把每一条悬线都当成可能的上下界计算,那么对于每一条悬线就计算其向左能到多远和向右能到多远
那么假设h[i][j]表示(i,j)悬线长度,那么h[i][j]=h[i-1][j]+1(a[i][j]=0)
否则h[i][j] = 0(a[i][j]=1)
对于能往左往右到的地方,就用悬线上所有的点往左边和右边移动看能到达的最小的距离
先计算每个点(i,j)向左的最远距离l[i][j]
此时l[i][j] = l[i][j-1]+1(a[i][j]=0),否则等于0(a[i][j]=1)
定义L[i][j]:(i,j)这条悬线向左能走多远,那么对于每个点都取决于上方的那个点向左能走多远
这样递推下来即可,l[i][j] = min(l[i][j],l[i-1][j]);
向右也是同理,时间复杂度O(n^2)
*/
int h[N][N],l[N][N],r[N][N],ans1,ans2;
int n,m;
int a[N][N];

void solve(){
    cin >> n >> m;
    memset(a,2,sizeof a);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(a[i][j] != a[i - 1][j]){ 
                h[i][j] = h[i - 1][j] + 1;
            } else {
                //注意本题和其他题不同的点,本题遇到a[i][j] != 之前的数的时候会令为1
                //因为本题不是模版题那样有明确的边界
                h[i][j] = 1;
            }
            if(a[i][j] != a[i][j - 1]) {
                l[i][j] = l[i][j - 1] + 1;
            } else l[i][j] = 1;
        }
        for(int j = m;j >= 1;j--){
            if(a[i][j] != a[i][j + 1]){
                r[i][j] = r[i][j + 1] + 1;
            } else r[i][j] = 1;
        }
    }
    for(int i = 0;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(!i){
                l[i][j] = r[i][j] = INF;
                continue;
            }
            if(h[i][j] > 1){
                r[i][j] = min(r[i - 1][j],r[i][j]);
                l[i][j] = min(l[i - 1][j],l[i][j]);
                int mn = min((r[i][j] + l[i][j] - 1),h[i][j]);
                ans1 = max(ans1,(r[i][j] + l[i][j] - 1) * h[i][j]);
                ans2 = max(ans2,mn * mn);
            }
        }
    }
    cout << ans2 << "\n" << ans1 << '\n';
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