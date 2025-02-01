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
KMP算法
next数组:
next[i] = prefix[i]的非平凡的最大Border(不是本身的最大Border)
next[1] = 0
考虑prefix[i]的所有(长度>1的)Border,去掉最后一个字符,就会变成prefix[i-1]的Border
那么求next[i]的时候,可以遍历prefix[i-1]的所有Border,即next[i-1],next[next[i-1]]...0
检查后一个字符是否等于S[i],这样就能求到当前i点的最大Border了,就等于此时转以后的next[i-1]+1
如果next[i-1]一直退到0了,并且有后一个字符不等于S[i],那么此时next[i]=0
*/

struct KMP {
    int nxt[N],len;
    char t[N];
    void clear(){
        len = nxt[0] = nxt[1] = 0;
    }
    //init是初始化nxt数组
    //字符串从下标为1开始
    //注意在ss的结尾后面加上'\0'
    void init(char* ss){
        len = strlen(ss + 1);
        memcpy(t,ss,(len + 2) * sizeof(char));
        for(int i = 2;i <= len;i++){
            //nxt[i]先继承nxt[i-1]的Border
            //然后nxt往前跳,并且每次比较ss[i]与ss[nxt[i]+1]的字符是否一样
            //遇到一样的就不跳了,如果nxt[i]已经是0,那么也跳出
            nxt[i] = nxt[i - 1];
            while(nxt[i] && ss[i] != ss[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
            nxt[i] += (ss[i] == ss[nxt[i] + 1]);
        }
    }
};



void solve(){

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