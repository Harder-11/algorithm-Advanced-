#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1005;
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

int n;
double a[N][N];

int guass(){
	for(int i = 1;i <= n;i++){
		int r = i;
		for(int k = i;k <= n;k++){
			if(fabs(a[k][i]) > eps){
				r = k;
				break; 
			}
		}
		if(r != i) swap(a[r],a[i]);
		if(fabs(a[i][i]) < eps) return 0;
		for(int k = 1;k <= n;k++){
			if(k == i) continue;
			double t = a[k][i] / a[i][i];
			for(int j = i;j <= n + 1;j++){
				a[k][j] -= t * a[i][j];
			}
		}
	}
	for(int i = 1;i <= n;i++){
		a[i][n + 1] /= a[i][i];
	}
	return 1;
}


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