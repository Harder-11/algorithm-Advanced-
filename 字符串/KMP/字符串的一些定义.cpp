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
字符串
S:无特殊说明,字符串仅有26个小写字母'a'-'z'组成,并用大写字母表示一个字符串
|S|:表示一个字符串的长度
s[i]:表示字符串S的第i个位置的字母,下标从1开始

子串
S[l,r]表示字符串S从l到r个字母顺次连接而成的新字符串
prefix[i]:表示字符串S的长度为i的前缀,prefix[i]=S[1,i]
suffix[i]:表示字符串S的长度为i的后缀,Suffix[i] = S[|S| - i + 1,|S|]

Border(KMP的核心概念)
如果字符串S的同长度的前缀和后缀完全相同,即prefix[i]=sunfix[i]
那么称次前缀/后缀为一个Border(根据语境,有时候Border也是指的长度)
特殊的,字符串本身也可以是它的Border

周期和循环节
对于字符串S和整数P,如果有S[i]=S[i-p],对于p < i <= |S|
那么称p就是字符串S的一个周期
若字符串S的周期满足p | |S|,那么称p为S的一个循环节,特殊的p = |S|一定是S的循环节

重要性质(Border & 周期)
1.如果p是S的周期 <==> |S| - p是S的Border
由周期的定义知道:S[i-p]=S[i]
又假设q是S的Border,那么就有S[i]=S[i + |S| - q]
那么就有|S| - q = p,即Border = |S| - p
所以字符串的周期性质等价于Border的性质,求周期等同于求Border
注意:Border不具有二分性
2.S的Border的Border也是S的Border(传递性)
证明:假设p是S的Border,那么有prefix[p] == suffix[p]
那么S[1,p] == S[|S| - p + 1,|S|] 
假设q是S[1,p]的Border,那么有prefix(1,p)[q] = suffix(1,p)[q]
S[1,q] == S[p - q + 1,p],那么有S[1,q] == S[|S| - q + 1,|S|]
所以S的Border的Border是S的Border(画图更显然)
那么求S的所有Border等价于求所有前缀的最大Border
假设S的最大Border是p,那么又求p的最大Border即可,以此类推


那么Border对字符串如此重要,怎么求Border呢?
如果是暴力,枚举1 <= i <= |S|,暴力验证prefix[i]=suffix[i],时间复杂度O(n^2)
优雅的暴力:使用Hash验证prefix[i]=suffix[i]
时间复杂度O(N),但是常数很大,容易构造Hash冲突
*/

void solve(){}

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