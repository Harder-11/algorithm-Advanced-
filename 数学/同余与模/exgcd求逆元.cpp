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
逆元的定义:
如果a,b∈Zm,满足ab = 1,则称b是a的逆元,记作a^(-1)
问题来了:如何判定在Zm里,a是否有逆元,如果有如何求a^(-1)
比如m = 4的时候,逆元就是a * a^(-1) 在mod 4的情况下与1同余
a = 0,此时没有逆元,a = 1,逆元为1,a = 2没有逆元.....

我们根据定义可知,如果有逆元的话,ab = km + 1,我们把a和m看做固定的数
移项得到ab - km = 1,其中b和k是待求的,那么此时我们就可以用exgcd来尝试求出b和k
由扩展欧几里得算法可以知道:ax + by  = gcd(a,b)有解,那么此时的ab - km = 1有解
那么一定就是gcd(a,m) = 1,也就是a和m互质
所以:a在Zm内有逆元,当且仅当gcd(a,m) = 1
如果m为质数,则任意0 < a < m,a ∈ Zm有逆
那么求逆元也很简单,就是用exgcd求,因为是求的ab - km = 1的一组解即可,也就是求的b
*/
void exgcd(int a,int b,int &x,int &y){
	if(b == 0){
		x = 1,y = 0;
		return;
	}
	//注意这里传参是y,x说明已经令x = y,最后计算y = x - (a / b) * y
	//x已经变成y,y已经变成x,那么就变成了y -= (a / b) * x
	exgcd(b,a % b,y,x);
	y -= a / b * x;
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