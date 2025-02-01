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
一个N * M的矩阵(N,M <= 15)用1*2和2*1的砖块密铺,问有多少种情况?
那么我们这样定义:如果竖着放,那么该位置为0,否则为1
那么对于当前行状态st,上一行状态st',必须满足有st | st' = (1 << n) - 1
并且如果上一行有0出现,那么本行该位置强制为1,如果上一行有连续1出现,那么本行必须是连续偶数个1
否则就不符合题意(如果是单个1,上一行又是1,那么就出现空位了)
那么怎么判断上一行连续1对于本行有哪些情况呢?假设上一行有01110
那么就是计算A = st' - (~st),如果得到的A有奇数个连续的1,那么就不合法,舍去
当然本题也可以暴力匹配check(int lst,int cur,int m)
注意:最后一行必须全部都是1
那么定义f[i][j]表示前i行全部填完并且第i行的状态为j的情况数
*/

ll n,m,lim;
ll f[15][10010];

//暴力判断是否有奇数个连续1的情况
bool check(int lst,int cur,int m){
    for(int i = 0;i < m;){
        if(!(lst & (1 << i)) && !(cur & (1 << i))) return 0;
        else if((lst & (1 << i)) && (cur & (1 << i))){
            if((lst & (1 << (i + 1))) && (cur & (1 << (i + 1)))){
                i += 2;
                continue;
            } else return 0;
        } else {
            i++;
            continue;
        }
    }
    return 1;
}

ll solve(int n,int m){
    memset(f,0,sizeof f);
    lim = ((1 << m) - 1);
    f[0][lim] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= lim;j++){
            //单独处理第一行,第一行就是全是1(代表全部可以填)
            if(i == 1){
                if(check(lim,j,m)) f[1][j]++;
            } else {
                for(int k = 0;k <= lim;k++){
                    if(check(k,j,m)) f[i][j] += f[i - 1][k];
                }
            }
        }
    }
    return f[n][lim];
}

void solve(){
    while(1){
        cin >> n >> m;
        if(!n && !m) break;
        if((n & 1) && (m & 1)){
            cout << "0\n";
            continue;
        }
        cout << solve(n,m) << '\n';
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