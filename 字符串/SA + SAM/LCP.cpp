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
假设有一组已经排序过的字符串A = [A1,A2,A3....An]
如果快速求Ai和Aj的LCP(最长公共前缀)

区间可加性:对于任意的k ∈ [i,j],LCP(Ai,Aj) = LCP(LCP(Ai,Ak),LCP(Ak,Aj))
= min(LCP(Ai,Ak),LCP(Ak,Aj))
进而:LCP(Ai,Aj) = min(LCP(Ai,Ai+1),LCP(Ai+1,Ai+2)....LCP(Aj-1,Aj));

定义Height数组
height[i]为后缀i与排名在他前面一个的后缀的LCP
即:height[i] = LCP(S[i,n],S[sa[rk[i] - 1]],n)
有了height数组之后,任意两个后缀的LCP就成了区间最小值查询
结论:height[i] >= height[i - 1] - 1
那么就可以让height[i] = height[i - 1] - 1,然后暴力拓展
*/

//SA之后O(n)复杂度求height数组实现:

char s[N];
int n,m,rk[N],sa[N],tp[N],a[N],b[N],h[N];

void Rsort(){
    for(int i = 0;i <= m;i++) b[i] = 0;
    for(int i = 1;i <= n;i++) b[rk[i]]++;
    for(int i = 1;i <= m;i++) b[i] += b[i - 1];
    for(int i = 1;i <= n;i++) sa[b[rk[tp[i]]]--] = tp[i];
}

void suffix(){
    for(int i = 1;i <= n;i++){
        tp[i] = i; 
        rk[i] = a[i];
    }
    Rsort();
    for(int k = 1;k <= n;k >>= 1){
        int num = 0;
        for(int i = n - k + 1;i <= n;i++) tp[++num] = i;
        for(int i = 1;i <= n;i++){
            if(sa[i] > k) tp[++num] = sa[i] - k;
        }
        Rsort();
        swap(tp,rk);
        rk[sa[1]] = 1;
        num = 1;
        for(int i = 2;i <= n;i++){
            rk[sa[i]] = (tp[sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i - 1] + k]) ? num : ++num;
        }
        if(num == n) return;
    }
}

void get_h(){
    for(int i = 1,k = 0;i <= n;i++){
        if(rk[i] == 0) continue;
        if(k) --k;
        while(s[i + k] == s[sa[rk[i] - 1] + k]) k++;
        h[rk[i]] = k;
    }
}

void solve(){
    cin >> n >> s;
    for(int i = 0;i < n;i++) a[i + 1] = s[i];
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