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
Hash是一种单射函数,可以将万物单向映射成一个整数值
字符串Hash就是指将一个字符串映射成一个整数值的方法,通常用来快速比较两个字符串是否相等
约定:H(S)表示一个字符串S通过Hash算法(H)映射成的整数值
例如:S = abcde,H(S)=12345,H(S')=54321

性质:必要性:若字符串S = T,那么一定有H(S) = H(T)
非必要性:若H(S) = H(T),不一定有S = T

Hash检测:通过H(S)和H(T)是否相等,来判断S和T是否相等的方法
Hash冲突:H(S) = H(T),但是S!=T,即发生了Hash冲突
Hash检测的时候发生Hash冲突的概率是是衡量Hash算法好坏的重要标准(小于万分之一就基本不会发生)
充分发挥主观能动性,自行发明一些Hash算法,例如定义H(S) = |S| * (S[1]+S[|S|])

多项式Hash:
将字符串看做是某个进制下的数字串,
H(S) = Σ(i=1,i<= |S| = n)S[i] * Base^(1+n-i) = H(S[1,|S| - 1]) * Base + S[|S|];
= S[1] * Base^n + S[2] * Base^(n-1) + .... + S[n] * Base^0
比如十进制,S=abcde,a-->1,b-->2,c-->3,d-->4,e-->5
H(S) = 1 * 10^4 + 2 * 10^3 + 3 * 10^2 + 4 * 10 + 5 = 12345
通常|Σ| = 26,那么进制肯定要大于26
优点:字符串和Hash值一一对应,不会发生Hash冲突
缺点:数字范围过大,难以用原始数据结构存储和比较

多项式取模Hash(模哈)(将H(S)随机映射到[0,mod-1]内的整数当中)
模哈是为了解决多项式Hash的缺点,但是取模之后可能导致两个不相等的数又变成一样,从而形成哈希冲突
那么模哈就是在效率和冲突之间进行折中,将多项式哈希的值对一个较大的质数取模
H'(S) = H(S)%mod 
优点:使得多项式Hash可以用原始数据结构(uint/ull)存储和比较
缺点:会有小概率发生哈希冲突

那么对于优秀的哈希模数需要满足:1.足够大 
2.自然溢出:使用ull保存Hash值,利用硬件特性,使得Hash值自然溢出,即实现模数为2^64,但是容易构造哈希冲突
同时,优秀的Hash模数应该还是一个质数

Hash模数
质数模哈(单模):选取1e9 ~ 1e10范围的大质数作为Hash模数
双模(多模):多次进行不同质数的单模哈希,有效降低哈希冲突概率
在不泄露模数的前提下,没有已知的方法可以构建冲突
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