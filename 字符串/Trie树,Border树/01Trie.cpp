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

//01Trie即对字符集只有2的字典串构成的Trie,常来解决01二进制串相关的字典序或者计数问题
/*
例题:给出一个正整数数组A,长度不超过100000
定义区间异或和为区间所有异或起来的结果,求最大区间异或和
思路:根据位运算的性质,首先求出异或前缀和
那么此时每个区间的异或和可以表示成两个前缀和的异或,问题转化为了n+1个数字当中选两个
做异或运算的最大值,可以用01Trie来解决
枚举一个数字x,然后寻找与它异或结果最大的另一个数字y
由于相同宽度的两个二进制数字的大小关系等价于字典序关系
从高到低考虑x的每一个二进制位bit:如果y的这一位也是bit,则异或结果的这一位为0
如果y的这一位是!bit,则异或结果的这一位是1,那么就是想尽可能在更高的位置异或为1,那么就
让y的每个二进制位和x的二进制位不一样
那么将所有的异或前缀和的数字插入到01Trie中,枚举x,在01Trie中寻找y:从根出发,如果有!bit边
*/


int n,a[N],pre[N];
int tr[N][2],cnt,ans;

void insert(int r){
    int p = 0;
    for(int i = 30;i >= 0;i--){
        int c = ((r >> i) & 1);
        if(!tr[p][c]) tr[p][c] = ++cnt;
        p = tr[p][c];
    }
}

void query(int r){
    int res = 0,p = 0;
    for(int i = 30;i >= 0;i--){
        int c = ((r >> i) & 1);
        if(tr[p][c ^ 1]){
            p = tr[p][c ^ 1];
            res |= (1 << i);
        } else {
            p = tr[p][c];
        }
    }
}

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        pre[i] = pre[i - 1] ^ a[i];
    }
    for(int i = 0;i <= n;i++) insert(pre[i]);
    for(int i = 0;i <= n;i++) query(pre[i]);
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