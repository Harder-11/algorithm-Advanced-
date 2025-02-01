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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
给定正整数序列a1,a2...an,求有多少组下标的三元组(i,j,k)(i < j < k)
满足ai * aj * ak是所有三个元素乘积中最小的
(3 <= n <= 1e5,1 <= ai <= 1e9)

思路:首先进行排序,乘积最小的一定就是排序后的a1,a2,a3对应的数字
然后进行分类讨论:
如果是a1 <= a2 < a3 = a4 = ... = ak < ak+1 .... <= an,答案就是k - 2个
如果是a1 < a2 = a3 = .... = ak <= ak+1 <= ... <= an,那么答案就是(k - 1) * (k - 2) / 2
如果是a1 = a2 = a3 = ... = ak <= ak + 1 <= ... <= an,那么答案就是k * (k - 1) * (k - 2) / 6
还有一种可能是a1 = a2 < a3 = a4 = ... = ak <= ak + 1 <= ... <= an
*/
int n,a[N];

void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	sort(a + 1,a + n + 1);
	if(a[1] == a[2]){
		ll k = 0;
		for(int i = 1;i <= n;i++){
			if(a[i] == a[1]){
				k++;
			}
		}
		ll r = 0;
		for(int i = 3;i <= n;i++){
			if(a[i] == a[3]){
				r++;
			}
		}
		if(a[2] != a[3]){
			cout << r << '\n';
		} else {
			cout << k * (k - 1) * (k - 2) / 6 << '\n';
		}
	} else if(a[2] == a[3]){
		ll k = 0;
		for(int i = 2;i <= n;i++){
			if(a[i] == a[2]){
				k++;
			}
		}
		cout << k * (k - 1) / 2;
	} else {
		ll k = 0;
		for(int i = 3;i <= n;i++){
			if(a[i] == a[3]){
				k++;
			}
		}
		cout << k << '\n';
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