#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1331;
const int hs2 = 998244353;
const int base = 233;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
给出一个正整数数组A,长度不超过100000,以及Q<=100000次查询,问:
子串A[l1,r1]和A[l2,r2]的字典序关系

思路:判定两个串的字典序等价于求解两个串的最长公共前缀(LCP),所以本题要快速求出两个子串的LCP
方法一:本题可以直接用SA(后缀数组求解)时间复杂度O(NlogN)
方法二:LCP满足二分性,那么就二分这个长度,然后Hash判断是否是LCP,时间复杂度O(NlogN)
*/

string s;
ll h[N],n,q;
int l1,r1,l2,r2;

ll power(ll a,ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % hs1;
        a = a * a % hs1;
        b >>= 1;
    }
    return ans;
}

void init(){
    for(int i = 1;i <= n;i++){
        h[i] = ((ll)h[i - 1] * base + s[i]) % hs1;
    }
}

bool check(int mid){
    ll r = (h[l1 + mid - 1] - h[l1 - 1] * power(base,mid) % hs1 + hs1) % hs1;
    ll rr = (h[l2 + mid - 1] - h[l2 - 1] * power(base,mid) % hs1 + hs1) % hs1;
    return r == rr;
}


void solve(){
    cin >> s >> q;
    n = s.size();
    s = " " + s;
    init();
    while(q--){
        cin >> l1 >> r1 >> l2 >> r2;
        int l = 0,ans;
        int r = min(r2 - l2,r1 - l1);
        while(l <= r){
            int mid = (l + r) >> 1;
            if(check(mid)){
                l = mid + 1;
                ans = mid;
            } else r = mid - 1;
        }
        if(s[l1 + ans] > s[l2 + ans]){
            cout << "1" << '\n';
        } else if(s[l1 + ans] < s[l2 + ans]){
            cout << "2" << '\n';
        } else {
            cout << "Equal" << '\n';
        }
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