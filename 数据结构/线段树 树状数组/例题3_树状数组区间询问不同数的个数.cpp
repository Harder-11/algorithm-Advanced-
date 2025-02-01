#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 2000005;
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
题意:
给出一个长度为N的数组,在给出M个询问,每次询问l..r范围内有多少个不同的数
其中N <= 5e4,M <= 2e5

思路:本题要求区间出现的不同数字的个数
那么我们做预处理,用pre[x]表示x上一次出现的位置,在遍历填pre数组的时候
如果此时pre[x]有值的话,那么我们就把上一个出现的位置置为0,当前位置为i,此时维护pre数组即可

注意本题有细节:不能生成了pre数组之后再进行查询,应该一遍生成pre数组
并且同时进行查询
比如输入的是1 1 1 1,生成完pre数组时候就是0 0 0 1,此时查询[1,3]的结果就是0
但是答案是1,就不满足题意了
这样边修改pre边记录答案的过程:1 1 1 1为例
此时查询存入的是q[3].push_back(1,1);代表把r作为固定的值
然后每次遍历到一个i就对应一个r,然后遍历q[r],找到对应的i和l,修改ans的值
pre数组依次是:
1 0 0 0
0 1 0 0
0 0 1 0,此时i = 3,修改ans值,使得ans[3] = 1,答案正确
相当于每次离线处理r固定的情况
*/

int pre[N],a[N],ans[N];
int n,m;
ll tr[N];

struct node {
	int id,pos;
	node(int x,int y){
		id = x;
		pos = y;
	}
	node() = default;
};

int lowbit(int x){
	return x & -x;
}

void update(int x,int val){
	while(x <= n){
		tr[x] += val;
		x += lowbit(x);
	}
}

ll sum(int x){
	ll res = 0;
	while(x){
		res += tr[x];
		x -= lowbit(x);
	}
	return res;
}

vector<node> q[N];

void solve(){
	cin >> n;
	memset(tr,0,sizeof tr);
	for(int i = 1;i <= n;i++) cin >> a[i];
	cin >> m;
	for(int i = 1,l,r;i <= m;i++){
		cin >> l >> r;
		q[r].push_back(node(i,l));
	}
	for(int i = 1;i <= n;i++){
		if(pre[a[i]]){
			update(pre[a[i]],-1);
		}
		update(i,1);
		pre[a[i]] = i;
		for(auto x : q[i]){
			ans[x.id] = sum(i) - sum(x.pos - 1);
		}
	}
	for(int i = 1;i <= m;i++){
		cout << ans[i] << "\n";
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