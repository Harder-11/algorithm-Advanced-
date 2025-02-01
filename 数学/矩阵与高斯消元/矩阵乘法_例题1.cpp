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
求长度为N的01串,满足所有极长的全0子串长度都是M的倍数,求01串的数量(mod 1e9+7)
1 <= N <= 1e18,2 <= M <= 100

思路:我们考虑动态规划,设f[n][2]为长度为n的数量,第二维表示最后一位为0/1
如果第n位为1的话,那么f[n][1]=f[n-1][0]+f[n-1][1],如果n位为0的话,前面m个连续的必须全是0
所以f[n][0]=f[n-m][0]+f[n-m][1]
那么合并起来可以去掉第二维,因为都是一样的,那么就是f[n]=f[n-m]+f[n-1]
但是我们发现N极大,所以不能循环解决,那么我们考虑构造矩阵
[f[n],f[n-1]...f[n-m+1]]=[[1,0,...0,1],[1,0,...,0],[0,1,....,0].....[0,0,....0,1]] 
*[f[n-1],f[n-2].....,f[n-m]]
那么此时矩阵的大小就是m * m,再使用矩阵快速幂,复杂度就变成了O(m^3*logn)
*/

ll n,m,ans,l;
//针对复杂度为O(m^3 * logn)并且对mod取模的代码
struct M {
	ll a[105][105];
	void clear(){
		memset(a,0,sizeof a);
	}
	void reset(){
		clear();
		for(int i = 1;i <= m;i++){
			a[i][i] = 1;
		}
	}
	M friend operator * (const M &A,const M &B){
		M ans;
		ans.clear();
		for(int i = 1;i <= m;i++){
			for(int k = 1;k <= m;k++){
				for(int j = 1;j <= m;j++){
					ans.a[i][j] = (ans.a[i][j] + A.a[i][k] * B.a[k][j] % mod) % mod;
				}
			}
		}
		return ans;
	}
};


M power(M t,ll k){
	M ans;
	ans.reset();
	while(k){
		if(k & 1) ans = ans * t;
		t = t * t;
		k >>= 1;
	}
	return ans;
}

void solve(){
	cin >> n >> m;
	if(n < m) ans = 1;
	else {
		l = m;
		M A;
		A.clear();
		A.a[1][1] = 1;
		A.a[1][m] = 1;
		//构造出的乘的m*m的矩阵
		for(int i = 2;i <= m;i++){
			A.a[i][i - 1] = 1;
		}
		ans = power(A,n).a[1][1];
	}
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