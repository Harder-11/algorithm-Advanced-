#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
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
后缀数组(SA)
定义:
1.后缀S[i]:S[i] = S[i,|S|]
2.字典序:对于两个字符串S和T,从左到右找到第一个不同的字母,谁的字母小,谁的字典序就小
特殊的,如果S为T的前缀,那么认为S < T,即空字符串最小
3.后缀排序:将所有后缀S[i]看做独立的串,放在一起按照字典序升序排序
4.后缀排名:rk[i]:rk[i]表示后缀S[i]在后缀排序中的排名,即他是第几小的后缀
5.后缀数组sa[i]:sa[i]表示排名第i小的后缀,rk[sa[i]] = i

如何求sa和rk呢?
思路:将比较字典序的二分求LCP转化为倍增求LCP
首先等效地认为在字符串的末尾添加无限个空字符
定义S(i,k) = S[i,i + 2^k - 1],即以i位置开头,长度为2^k的子串
后缀S[i]与S[j]的字典序关系等价于S(i,∞)与S(j,∞)的关系
那么只需要将S(i,log(2,n)(向上取整)),i = 1,2,3....n排序即可
比如s = abc,s1 = abcφ,s2 = bcφφ,s3 = cφφφ

于是可以倍增进行排序,假设当前已经得到了S(i,k)的结果,即rk[S(i,k)]和sa[S(i,k)]思考如何排序S(i,k+1)
---由于S(i,k+1)是由S(i,k)和S(i+2^k,k)前后拼接而成,因此比较S(i,k+1)和S(j,k+1)的字典序可以变成先比较S(i,k)和S(j,k)的字典序
然后再比较S(i+2^k,k)和S(j+2^k,k)的字典序,因此可以把S(i,k+1)看成一个两位数,高位是rk[S(i,k)]低位是rk[S(i+2^k,k)]
那么思路就是:
先基数排序,然后一层for,更新第二关键字tp,利用这一轮的第一关键字更新下一轮的 并且 离散第一关键字
当离散出来的计数 = 长度n就结束算法

复习一下基数排序:基数排序是一种反常识的排序,它是先比较的低位再比较高位
先把低位按照标签放入桶中,然后再按照顺序,以高位放入桶中即可排序完成
比如说排序47,23,19,17,31,先按照低位放入桶,此时就是31 23 47 17 19
那么再按照顺序来放高位,那么就是17 19 23 31 47,即得到排序结果
但实际上先排哪一位都是无所谓的,SA是先排的高位
*/

char s[N];
//这里a是暂存数组
//rk(第一关键字)第i位的排名
//tp是第二关键字辅助使用
int a[N],rk[N],sa[N],tp[N],b[N],n,m;

void Rsort(){
    for(int i = 0;i <= m;i++) b[i] = 0;
    //每一个出现的第一关键字++
    //第一轮就相当于统计了每个字符出现的个数
    //假设是tp[i] = 1,rk[1] = a[1] = 第一个字符的ASCII,b[a[1]]++
    //那么实际就是每次b[a[i]]++
    for(int i = 1;i <= n;i++) b[rk[i]]++;
    //b中i现在代表这个数最多能排第几位,b数组前面的代表第一关键字的字典序更小
    //利用前缀和确定了每个数字排名的区间
    for(int i = 1;i <= m;i++) b[i] += b[i - 1];
    //生成这一轮的sa数组
    //第二轮开始因为tp是按照第二关键字进入数组的
    //所以从后往前看第二关键字肯定比前面小
    //所以第一关键字相同的时候,第二关键字越大越靠后,所以先拿到大的值然后--
    for(int i = n;i >= 1;i--) sa[b[rk[tp[i]]]--] = tp[i];
}

void suffix(){
    //第一轮直接用ascii码和位置当做关键字
    for(int i = 1;i <= n;i++){
        rk[i] = a[i];
        tp[i] = i;
    }
    Rsort();
    for(int k = 1;k <= n;k <<= 1){
        int num = 0;
        //从n - k + 1到n位置的第二关键字都是0,所以先存入数组
        //所以设为极小值
        for(int i = n - k + 1;i <= n;i++) tp[++num] = i;
        //sa[i]表示字典序第i小的起始位置,k是当前倍增的步长,
        for(int i = 1;i <= n;i++){
            if(sa[i] > k) tp[++num] = sa[i] - k;
        }
        Rsort();
        //tp存下这一轮的rk
        //下面开始更新下一轮的rk
        swap(rk,tp);
        //由于避免越界问题,先处理rk[sa[1]] = 1(这是个恒等式)
        rk[sa[1]] = 1;
        //此时num用来统计排名
        num = 1;
        for(int i = 2;i <= n;i++){
            //如果此时发现有字典序一模一样的,说明就不是最后一轮,此时num不用++
            //这里tp是存的这一轮的rk,那么可以直接这样比较,然后rk更新为下一轮的rk
            rk[sa[i]] = (tp[sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i - 1] + k]) ? num : ++num;
        }
        //如果有n种排名那就说明已经排序好了
        if(num == n) break;
        //m代表tp的种类(字符串的种类)
        m = num;
    }
}

void solve(){
    cin >> s;
    //按照ASCII码来确定的
    m = 128;
    n = strlen(s);
    for(int i = 0;i < n;i++) a[i + 1] = s[i];
    suffix();
    for(int i = 1;i <= n;i++){
        cout << sa[i] << " ";
    }
    cout << '\n';
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