#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 50005;
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
思考:如果现在没有求前缀和,给你一个数组,你知道了a[5]~a[100]的值
那你如何快速求出a[4]~a[102]的值?
我们记之前求得的和为sum,然后l = 5,r = 100,只用while(l > 4) sum += a[--l]
while(r < 102) sum += a[++r],这两个循环跑完了也就求到了4~102的和
现在的时间复杂度是Σ(i=1,M)(|Li - L(i-1)| + |Ri - R(i - 1)|),Li,Ri表示第i次查询的时候的下标左右端点

如果不要求查询的顺序,
莫队安排的顺序就是:按照L / Block分组,然后每组中的R端点单调递增
因为L被分了组,所以L端点的移动的复杂度不会超过Block
对于R端点,因为R端点在每组内的移动都是单调的,所以总的移动次数就是N / Block * N,均摊到M个查询里面就是N / Block * N / M,近似令N = M
那么时间复杂度就是O(N / Block),那么该算法的时间复杂度就是O(max(Block,N / Block))
由均值不等式可以知道当Block = N / Block的时候复杂度最小,最小的复杂度就是O(sqrt(N))

那么对于本题题意:
小Z每天早上都要在一堆五颜六色的袜子里面找出一双来穿,终于有一天,小Z再也无法忍受这种找袜子的过程,于是他决定听天由命
具体来说,小Z把这N只袜子从1到N编号,然后从编号L到R(尽管小Z并不在意两只袜子是不是完整的一双,甚至不在意两只袜子是否一左一右
他却很在意袜子的颜色,毕竟穿两只不同颜色的袜子很尴尬)
你的任务就是告诉小Z他有多大的概率抽到两只相同颜色的袜子,当然小Z希望这个概率尽量高,所以他可能询问多个[L,R]以方便自己选择
输入:第一行输入两个正整数N和M,N代表袜子的数量,M为小Z的提问数量,接下来一行包含N个正整数Ci,其中Ci表示第i只袜子的颜色
相同的颜色用相同的数字表示,再接下来M行,每行两个正整数L,R表示一个询问
输出:包括M行,对于每个询问在一行中输出分数A/B表示从该询问的区间[L,R]中随机抽出两只袜子颜色相同的概率。
若该概率为0则输出0/1，否则输出的A/B必须为最简分数。
对于所有的数据:N,M <= 50000,1 <= L < R <= N,Ci <= N

思路:莫队的很模版的题,设col[i]为当前颜色i出现的次数,ans表示当前有多少次可行的匹配方案
那么如果是增长,就是ans + C(col[k] + 1,2) - C(col[k],2),如果是缩短就是ans - (C(col[k],2) - C(col[k] - 1,2)) 
那么最终查询的答案就是ans / C(r - l + 1,2)
又有优化:C(col[k] + 1,2) - C(col[k],2) = col[k]
最后化简用分子分母同时除以gcd即可,注意特判分子为0的情况,此时分母为1,输出的0/1(题目要求)
*/

int n,m,mx;
int c[N],cnt[N];
ll sum;
//ans1记录分子,ans2记录分母
ll ans1[N],ans2[N];

//莫队核心,利用l / mx进行分组排序,这样让时间复杂度变成O(sqrt(N))
struct query {
	int l,r,id;
	bool operator < (const query &x) const {
		if(l / mx != x.l / mx) return l < x.l;
		else return r < x.r;
	}
} a[N];

void add(int i){
	sum += cnt[i];
	cnt[i]++;
}

void del(int i){
	cnt[i]--;
	sum -= cnt[i];
}

ll gcd(ll a,ll b){
	return b ? gcd(b,a % b) : a;
}

void solve(){
	cin >> n >> m;
	mx = sqrt(n);
	for(int i = 1;i <= n;i++) cin >> c[i];
	for(int i = 0;i < m;i++){
		cin >> a[i].l >> a[i].r;
		a[i].id = i;
	}
	sort(a,a + m);
	for(int i = 0,l = 1,r = 0;i < m;i++){
		if(a[i].l == a[i].r){
			ans1[a[i].id] = 0;
			ans2[a[i].id] = 1;
			continue;
		}
		while(l > a[i].l) add(c[--l]);
		while(r < a[i].r) add(c[++r]);
		while(l < a[i].l) del(c[l++]);
		while(r > a[i].r) del(c[r--]); 
		ans1[a[i].id] = sum;
		//本质就是C(r - l + 1,2)
		ans2[a[i].id] = (ll)(r - l + 1) * (r - l) / 2;
	}
	for(int i = 0;i < m;i++){
		if(ans1[i]){
			ll g = gcd(ans1[i],ans2[i]);
			ans1[i] /= g,ans2[i] /= g;
		} else {
			ans2[i] = 1;
		}
		cout << ans1[i] << "/" << ans2[i] << "\n";
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