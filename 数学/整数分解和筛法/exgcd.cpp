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
扩展欧几里得算法:
在欧几里得算法的基础上回推
设ax1 + by1 = gcd(a,b),bx2 + (a mod b)y2 = gcd(b,a mod b);
又欧几里得算法可以知道gcd(a,b) = gcd(b,a mod b)
所以ax1 + by1 = bx2 + (a mod b)y2
所以ax1 + by1 = bx2 + (a - a / b * b)y2
展开得到ax1 + by1 = ay2 + bx2 - a / b * by2 = ay2 + b(x2 - a / b * y2)
所以x1 = y2,y1 = x2 - a / b * y2;

求出的通解就是x1 + k * (b / gcd(a,b)),y1 - k * (a / gcd(a,b))
*/

//代码实现exgcd,x和y就是ax1 + by1 = gcd(a,b)的一组特解
//所以当b = 0的时候,此时就求出了gcd(a,b) = a,那么y = 0,x = 1,带入ax + by = a,刚好满足题意
//所以b = 0的时候直接给x赋值为1,y赋值为0
int exgcd(int a,int b,int &x,int &y){
	if(b == 0){
		x = 1,y = 0;
		return a;
	}	
	int d = exgcd(b,a % b,x,y);
	int t = x;
	x = y;
	y = t - (a / b) * y;
	return d;
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