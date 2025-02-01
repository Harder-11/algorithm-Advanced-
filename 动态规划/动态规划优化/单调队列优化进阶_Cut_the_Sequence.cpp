#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs = 1331;
const double PI = acos(-1);
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
给定一个长为n的序列,求一种分割方式,使得每部分都满足和不超过M,使得每部分的最大值的
和最小,求这个最小值
0 < n <= 1e5,a[i] >= 0  
那么很明显令f[i]表示前i个数所需要的最小代价
f[i] = min(j=i-1,si-sj<=m)(f[j]+max(k=j+1,i){ak})
其中j是上一个区间的右端点,s为前缀和数组,发现每次转移fi都是O(n)的,总的复杂度就是O(N^2)
那么考虑优化dp
由题目的性质可以看到,f数组是不降的,基于这一点,我们可以在转移的时候
如果有aj <= a(j+1)
那么有max(k=j,i){ak} = max(k=j+1,i){ak}
那么得到f[j-1]+max(k=j,i){ak} <= f[j] + max(k=j+1,i){ak}
那么就可以用单调队列来优化,用multiset来确定最优的状态
*/
ll n,m,a[N],s[N],f[N],l,r,q[N << 2];
set<ll> S;

void solve(){   
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        if(a[i] > m){
            cout << -1 << '\n';
            return;
        }
        s[i] = s[i - 1] + a[i];
    }
    l = 1,r = 0;
    for(int i = 1;i <= n;i++){
        while(l <= r && s[i] - s[q[l]] > m){
            S.erase(f[q[l]] + a[q[l + 1]]);
            l++;
        }
        while(l <= r && a[q[r]] < a[i]){
            S.erase(f[q[r - 1]] + a[q[r]]);
            r--;
        }
        if(l <= r){
            S.insert(f[q[r]] + a[i]);
        }
        q[++r] = i;
        int L = 0,R = i - 1,c;
        while(L <= R){
            int mid = (L + R) >> 1;
            if(s[i] - s[mid] > m){
                L = mid + 1;
            } else {
                c = mid;
                R = mid - 1;
            }
        }
        f[i] = f[c] + a[q[l]];
        if(S.size()){
            f[i] = min(f[i],*S.begin());
        }
    }
    cout << f[n] << '\n';
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