#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2000005;
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
有一个n * m的字符串二维矩阵A(0 < n * m <= 1000000)
求一个权值和最小的子矩阵B,使得将矩阵B横向纵向无限延伸之后,A是一个子矩阵

思路:本质就是求A的最小二维循环周期
求二维循环周期就是对两个维度分别求周期,方法是完全对称的
那么假设我们要求横向的循环周期,那么必须是每一行的循环周期
因此要对每一行分别求循环周期(KMP),然后求最小公共循环周期即可(|S|-Border就是周期)
本题代码只写了求的最小的子矩阵部分(两次KMP即可)
*/

int n,m;
int nxt[N];
map<int,int> mp1,mp2;
int col,row;

void solve(){
    cin >> n >> m;
    char c[n + 2][m + 2];
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> c[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        nxt[0] = nxt[1] = 0;
        for(int j = 2;j <= m;j++){
            nxt[j] = nxt[j - 1];
            while(nxt[j] && c[i][j] != c[i][nxt[j] + 1]) nxt[j] = nxt[nxt[j]];
            nxt[j] += (c[i][j] == c[i][nxt[j] + 1]);
        }
        mp1[m - nxt[m]]++;
        while(nxt[m] != 0){
            nxt[m] = nxt[nxt[m]];
            mp1[m - nxt[m]]++;
        }
    }
    for(auto [x,y] : mp1){
        if(y == n){
            row = x;
            break;
        }
    }
    for(int i = 1;i <= m;i++){
        nxt[0] = nxt[1] = 0;
        for(int j = 2;j <= n;j++){
            nxt[j] = nxt[j - 1];
            while(nxt[j] && c[j][i] != c[nxt[j] + 1][i]) nxt[j] = nxt[nxt[j]];
            nxt[j] += (c[j][i] == c[nxt[j] + 1][i]);
        }
        mp2[n - nxt[n]]++;
        while(nxt[n] != 0){
            nxt[n] = nxt[nxt[n]];
            mp2[n - nxt[n]]++;
        }
    }
    for(auto [x,y] : mp2){
        if(y == m){
            col = x;
            break;
        }
    }
    cout << row << " " << col << '\n';

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