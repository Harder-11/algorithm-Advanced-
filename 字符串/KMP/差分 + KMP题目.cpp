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
给出两个正整数数组A和B,长度分别是n <= m <= 2e5,问A有多少个长度为m的区间A',满足
(A'[1] + B[1]) % k = (A'[2] + B[2]) % k = ......

思路:差分,将满足的条件拆分为以下式子:
(A'[1] + B[1]) % k = (A'[2] + B[2]) % k
(A'[2] + B[2]) % k = (A'[3] + B[3]) % k
.....
(A'[m - 1] + B[m - 1]) % k = (A'[m] + B[m]) % k
我们把和A有关的项移到一边,和B有关的移到一边,得到:
(A'[1] - A'[2]) % k = -(B[1] - B[2]) % k
(A'[2] - A'[3]) % k = -(B[2] - B[3]) % k
......
对A'数组求差分,并且对B'数组求差分,那么问题就转化为了-DiffB数组
在DiffA数组中出现的次数,进而转化为字符串匹配问题,可以使用KMP解决

*/


int n,m,k;
int a[N],b[N];
int diffa[N],diffb[N],nxt[N];
 
void solve(){
    cin >> n >> m >> k;
    int ans = 0;
    // memset(diffa,0,sizeof diffa);
    // memset(diffb,0,sizeof diffb);
    // memset(nxt,0,sizeof nxt); 
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= m;i++) cin >> b[i];
    //防止差分减出负数,每次%k之后+k,否则会一个案例都过不了
    for(int i = 1; i < n; i++) {
        diffa[i] = (a[i] - a[i + 1]) % k;
        if (diffa[i] < 0) diffa[i] += k;
    }
    for(int i = 1; i < m; i++) {
        diffb[i] = -((b[i] - b[i + 1]) % k);
        if (diffb[i] < 0) diffb[i] += k;
    }
    nxt[0] = nxt[1] = 0;
    for(int i = 2;i < m;i++){
        nxt[i] = nxt[i - 1];
        while(nxt[i] && diffb[i] != diffb[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
        nxt[i] += (diffb[i] == diffb[nxt[i] + 1]);
    }
    int r = 0;
    for(int i = 1;i < n;i++){
        while(r && diffa[i] != diffb[r + 1]) r = nxt[r];
        if(diffa[i] == diffb[r + 1]) r++;
        if(r == m - 1){
            ans++;
            r = nxt[r];
        }
    }
    cout << ans << '\n';
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