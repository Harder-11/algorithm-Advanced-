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
有n杯啤酒,其高度分别为a1,a2,...an,一开始柜台为空,q次询问,每次一杯啤酒方上
或者拿下柜台,然后输出柜台上有多少对啤酒(i,j)满足gcd(ai,aj) = 1
1 <= n,q <= 2e5,1 <= ai <= 5e5

思路:对于每个已经放到柜台的啤酒,我们将其高度进行质因数分解,所有数都可以用pi^ki的形式表示
并且一个数的质因数的个数最多有7个,因为2*3*5*7*11*13*17>5e5
然后用容斥求:和x互质的数的个数 = 总个数-和x不互质的个数即可
*/

//lnk[i][0]位置是用来计数的
int n,q,a[N],prime[N << 2],lnk[N][11],tot[N << 2];
bool isprime[N << 2],vis[N];
ll ans;

void init(int n){
	isprime[0] = isprime[1] = 1;
	for(int i = 2;i <= n;i++){
		if(!isprime[i]) prime[++prime[0]] = i;
		for(int j = 1;j <= prime[0] && i * prime[j] <= n;j++){
			isprime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}

void query(int x,int op){
	for(int i = 0;i < (1 << lnk[x][0]);i++){
		int now = 1,cnt = 0;
		for(int j = 1;j <= lnk[x][0];j++){
			if(i & (1 << (j - 1))){
				now *= lnk[x][j];
				cnt++;
			}
		}
		if(cnt & 1) ans -= op * tot[now];
		else ans += op * tot[now];
	}
}

void update(int x,int op){
	for(int i = 0;i < (1 << lnk[x][0]);i++){
		int now = 1;
		for(int j = 1;j <= lnk[x][0];j++){
			if(i & (1 << (j - 1))){
				now *= lnk[x][j];
			}
		}
		tot[now] += op;
	}
}

void solve(){
	cin >> n >> q;
	init(500000);
	for(int i = 1,x;i <= n;i++){
		cin >> x;
		for(int j = 1;j <= prime[0] && prime[j] <= sqrt(x);j++){
			if(x % prime[j] == 0){
				lnk[i][++lnk[i][0]] = prime[j];
				while(x % prime[j] == 0) x /= prime[j];
			}
		}
		if(x > 1) lnk[i][++lnk[i][0]] = x;
	}
	while(q--){
		int x;
		cin >> x;
		if(!vis[x]){
			query(x,1);
			update(x,1);
		} else {
			update(x,-1);
			query(x,-1);
		}
		vis[x] ^= 1;
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