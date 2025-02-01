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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
定义f0(n)为p*q=n且gcd(p,q)=1的(p,q)的对数
定义f_(r+1)(n)=Σ(u*v=n)(fr(u)+fr(v))/2
q次询问,每次输出fr(n) mod (1e9 + 7)
1 <= q <= 1e6,0 <= r <= 1e6,1 <= n <= 1e6

思路:我们首先把n进行分解,分解为p1^a1*p2^a2...pk^ak
那么此时p,q的对数就是p1,p2,p3...pk随意分为两堆的分法即2^k,k为质因子的个数
并且f0(n)是一个积性函数
而对于f_(r+1)我们可以写成Σ(d|n)fr(d)
那么f1(n) = Σ(d|n)f0(d),那么f1(n)也是积性函数,那么fr(n)也是积性函数
既然是积性函数那么我们肯定要求的是fr(p^a)类型的而f0(p^a)为固定值2
我们进行递推,f1(p^a)=Σ(i=0,a)f0(p^i)=1+2a(i=0的时候f0(1)=1)
那么对于一般的fr(p^a)=Σ(i=0,a)f_(r-1)(p^i)
那么对于fr(n)=fr(p1^a1)*fr(p2^a2)...fr(pk^ak)

那么我们可以考虑dp递推,dp[i][j]表示fi(p^j),初始化显然就是
dp[i][0]=1,dp[0][j]=2,那么递推式就是dp[i][j]=Σ(x=0,j)dp[i-1][x]
用前缀和优化即可
*/

int minp[N];
//这里sum[0]置为1,因为i=0的时候f0(1)=1
int dp[N][20],sum[20] = {1};
int n,r,q;


void init(){
	for(int i = 2;i < N;i++){
		if(!minp[i]){
			for(int j = i;j < N;j += i){
				minp[j] = i;
			}
		}
	}
	for(int i = 0;i < N;i++) dp[i][0] = 1;
	for(int i = 1;i < 20;i++){
		dp[0][i] = 2;
		sum[i] = sum[i - 1] + dp[0][i];
	}
	for(int i = 1;i < N;i++){
		for(int j = 1;j < 20;j++){
			dp[i][j] = sum[j];
			sum[j] = (sum[j - 1] + dp[i][j]) % mod;
		}
	}
}

void solve(){
	init();
	cin >> q;
	while(q--){
		ll ans = 1;
		cin >> r >> n;
		int cnt,p;
		while(n != 1){
			cnt = 0,p = minp[n];
			while(n % p == 0){
				cnt++;
				n /= p;
			}
			ans = ans * dp[r][cnt] % mod;
		}
		cout << ans << '\n';
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