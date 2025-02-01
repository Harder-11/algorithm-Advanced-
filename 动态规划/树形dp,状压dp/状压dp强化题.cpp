#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 105;
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
在P位置布置炮兵部队(也就是任意两支炮兵部队不能互相攻击)
问最多能布置多少炮兵部队

思路:怎么进行状态压缩?
先对于每一行而言,对于每一行的任意一个1的左右两边都必须是两个0
也就是(x & (x << 1)) == 0 && (x & (x << 2)) == 0 && (x & (x >> 1)) == 0 && (x & (x >> 2)) == 0
对于列上面的情况,要记录上一行和上上行的状态
那么定义f[i][j][k]:表示第i行为状态j,第i-1行为状态k时所用的最大炮兵数
所以转移方程就是f[i][j][k]=max(f[i][j][k],f[i-1][k][q]+num[j])
q代表的i-2行的状态,num[j]是指j状态的炮兵阵地数
其中满足p和q和j不发生冲突即可
由于本题要记录前两行的所有可能状态,直接开数组会MLE,所以就提前把所有满足条件
的状态存下来
最后还要注意用j和地形图做比对,如果出现了H位置放的1那就不合理
可以将H当做1,P当做1,然后j和这一行代表的二进制串做AND操作,如果>0就不合理
*/

int m,n;
//直接把地形图转化为2进制串
int mp[110];
//这里70是估算,因为是先筛选状态,状态数肯定是小于1<<10的个数的
ll f[110][70][70],ans;
vector<int> st,num;

void solve(){
    cin >> n >> m;
    for(int i = 0;i <= (1 << m) - 1;i++){
        if((i & (i << 1)) || (i & (i << 2))) continue;
        st.push_back(i);
        num.push_back(__builtin_popcount(i));
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            char c; cin >> c;
            if(c == 'H') mp[i] |= (1 << (j - 1));
        }
    }
    
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < st.size();j++){
            int cur = st[j];
            //如果发现在山地布置了炮兵部队,那么continue
            if(cur & mp[i]) continue;
            for(int k = 0;k < st.size();k++){
                int lst = st[k];
                if((cur & lst)) continue;
                for(int p = 0;p < st.size();p++){
                    int tmp = st[p];
                    if((cur & tmp) || (cur & lst)) continue;
                    f[i][j][k] = max(f[i][j][k],f[i - 1][k][p] + num[j]);
                    ans = max(ans,f[i][j][k]);
                }
            }
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