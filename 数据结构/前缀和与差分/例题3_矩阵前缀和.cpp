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
题意:在某个地方有两座层数为N的高塔,两座高塔的内部各自有链接到上一层的楼梯
即每座塔的第i层可以直接上楼到第i+1层
此时在两座高塔之间还会出现一些链接两座高塔的楼梯,具体来说,除了顶层还会出现:
1.左侧高塔的i层有楼梯链接到右侧高塔的i+1层
2.右侧高塔的i层有楼梯链接到左侧高塔的i+1层
我们有字符'/'表示第1种情况,'\'表示第二种情况,现在想知道从某做高塔的第hs层移动到ht层(hs < ht)
在只能沿楼梯上楼的情况下,有多少种不同的移动方案?
答案对1e9 + 7取模

加入说我们没有限制,直接求到某个位置的方案数,显然就是一个dp
其中dp[i][0/1]表示来到的层数和左/右塔
但是本题有起点的要求,不能直接用dp来求方案数
我们可以使用一个二维矩阵来求方案数,A[i][j]就代表的从i到j的方案数
其中i和j都代表的0/1,代表的左边/右边的塔
我们能看出,对于'/'类型的楼梯,可以用矩阵[[1,1],[0,1]]来表示
对于'\'类型的楼梯,可以用矩阵[[1,0],[1,1]]来转移
那么从下到上,我们遇到'/'就乘上[[1,1],[0,1]],否则乘上[[1,0],[1,1]]
然后对于询问从l层到r层,就是sum[r]和sum[l - 1]来求解
那么就是sum[r] * (sum[l - 1]^(-1)),就把l以下楼层给抵消了
那么要求sum[l - 1]矩阵的逆矩阵
*/

struct Mat {
    ll a[2][2];
    Mat(){
        for(int i = 0;i < 2;i++){
            for(int j = 0;j < 2;j++){
                a[i][j] = 0;
            }
        }
        for(int i = 0;i < 2;i++) a[i][i] = 1;
    }
    Mat(ll a1,ll a2,ll a3,ll a4){
        a[0][0] = a1,a[0][1] = a2;
        a[1][0] = a3,a[1][1] = a4;
    }
};

//要求逆矩阵,所以是增广矩阵
ll A[2][4];

ll power(ll x,ll y,ll mod){
    ll ans = 1;
    while(y){
        if(y & 1) ans = ans * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

ll get_inv(ll x){
    return power(x,mod - 2,mod);
}

void row_minus(int a,int b,ll k){
    for(int i = 0;i < 4;i++){
        A[a][i] = (A[a][i] - A[b][i] * k % mod + mod) % mod;
    }
}

void row_mul(int a,ll k){
    for(int i = 0;i < 4;i++){
        A[a][i] = (A[a][i] * k) % mod;
    }
}

void row_swap(int a,int b){
    for(int i = 0;i < 4;i++){
        swap(A[a][i],A[b][i]);
    }
}

//高斯约旦消元求逆
Mat getinv(Mat x){
    memset(A,0,sizeof A);
    for(int i = 0;i < 2;i++){
        for(int j = 0;j < 2;j++){
            A[i][j] = x.a[i][j];
            //增广矩阵初识为单位矩阵
            A[i][2 + j] = (i == j);
        }
    }
    for(int i = 0;i < 2;i++){
        if(!A[i][i]){
            for(int j = i + 1;j < 2;j++){
                if(A[j][i]){
                    row_swap(i,j);
                    break;
                }
            }
        }
        //直接去乘上乘法逆元,这样就巧妙地避免了除法的出现
        //可以防止误差导致错误
        row_mul(i,get_inv(A[i][i]));
        for(int j = i + 1;j < 2;j++){
            row_minus(j,i,A[j][i]);
        }
    }
    for(int i = 1;i >= 0;i--){
        for(int j = i - 1;j >= 0;j--){
            row_minus(j,i,A[j][i]);
        }
    }
    Mat res;
    for(int i = 0;i < 2;i++){
        for(int j = 0;j < 2;j++){
            res.a[i][j] = A[i][j + 2];
        }
    }
    return res;
}

const Mat tA(1,1,0,1);
const Mat tB(1,0,1,1);

Mat operator * (Mat x,Mat y){
    Mat c;
    for(int i = 0;i < 2;i++){
        for(int j = 0;j < 2;j++){
            c.a[i][j] = 0;
        }
    }
    for(int i = 0;i < 2;i++){
        for(int j = 0;j < 2;j++){
            for(int k = 0;k < 2;k++){
                c.a[i][j] = (c.a[i][j] + x.a[i][k] * y.a[k][j] % mod) % mod;
            }
        }
    }
    return c;
}

Mat pre[N];
char s[N];
int n,m,hs,ht,ps,pt;

void solve(){
    cin >> n >> m >> (s + 1);
    pre[0] = Mat(1,0,0,1);
    for(int i = 1;i < n;i++){
        if(s[i] == '/') pre[i] = pre[i - 1] * tA;
        else pre[i] = pre[i - 1] * tB;
    }
    while(m--){
        cin >> hs >> ht >> ps >> pt;
        //注意这里pre计算的只有n-1层,所以是pre[ht-1]
        Mat ans = getinv(pre[hs - 1]) * pre[ht - 1];
        cout << ans.a[ps][pt] << '\n';
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