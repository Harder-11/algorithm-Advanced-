#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 600005;
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
对于01字典树,最大的作用就是给出一个x,然后再给出一堆数字ai,要求x ^ ai的最大值操作
那么可持久化字典树就可以求[l,r]区间上与x的异或最大值,并且支持插入操作

例题:对于一个长度为n的数组a维护下列操作:
1.子啊数组的末尾添加一个数x,数组的长度n自增1
2.给出查询区间[l,r]和一个值k,求当l <= p <= r时,k ^ ap ^ a(p + 1) ^ .... ^ an的最大值
思路:很明显,我们记Sx = a1 ^ a2 ^ a3 ... ^ ax
那么原式等价于S(p - 1) ^ Sn ^ k,很明显,Sn ^ k在查询的时候是固定的,题目的查询变化为查询在区间[l - 1,r - 1]中异或定值(Sn ^ k)的最大值
那么我们建立一棵可持久化字典树,只需要把每一个区间都建一棵Trie,然后查询的时候往当前位不同的地方跳即可得到异或最大值
*/

int n,q,a[N],s[N],l,r,x;
char op;

struct Trie {
	//val数组是用来记录每个编号的节点在当前版本的出现的此时
	//root仍然是记录每个Trie的根节点
	int cnt,rt[N],ch[N << 5][2],val[N << 5];
	void insert(int o,int lst,int v){
		for(int i = 28;i >= 0;i--){
			//在原版本的基础上更新
			//每次当前版本都要比原来版本 + 1
			val[o] = val[lst] + 1;
			//此时v的当前二进制位是0
			if((v & (1 << i)) == 0){
				//如果现在ch往0走的路是是0,那么就新开结点
				if(!ch[o][0]) ch[o][0] = ++cnt;
				//同时更新ch[o][1]为ch[lst][1],因为没有变化就继承上一版本;
				//并且同时更新o和lst结点到下一层
				ch[o][1] = ch[lst][1];
				o = ch[o][0];
				lst = ch[lst][0];
			} else {
				if(!ch[o][1]) ch[o][1] = ++cnt;
				ch[o][0] = ch[lst][0];
				o = ch[o][1];
				lst = ch[lst][1];
			}
		}
		//最后记得还要更新一次val值,o和lst指针跳了之后就退出循环,最后一次没有更新val值
		val[o] = val[lst] + 1;
	}
	int query(int o1,int o2,int v){
		int res = 0;
		for(int i = 28;i >= 0;i--){
			int t = ((v & (1 << i)) ? 1 : 0);
			//如果版本差存在不同结点的就往不同节点处跳即可
			if(val[ch[o1][!t]] - val[ch[o2][!t]]){
				res += (1 << i);
				o1 = ch[o1][!t];
				o2 = ch[o2][!t];
			} else {
				o1 = ch[o1][t];
				o2 = ch[o2][t];
			}
		}
		return res;
	}
} st;

void solve(){
	cin >> n >> q;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		s[i] = s[i - 1] ^ a[i];
	}
	for(int i = 1;i <= n;i++){
		st.rt[i] = ++st.cnt;
		st.insert(st.rt[i],st.rt[i - 1],s[i]);
	}
	while(q--){
		cin >> op;
		if(op == 'A'){
			n++;
			cin >> a[n];
			s[n] = s[n - 1] ^ a[n];
			st.rt[n] = st.cnt++;
			st.insert(st.rt[n],st.rt[n - 1],s[n]);
		}
		if(op == 'Q'){
			cin >> l >> r >> x;
			//由于转化出来的结果是S(p - 1) ^ Sn ^ k,这里是p - 1说明r和l都要--
			//分类讨论是因为防止st.rt[l - 1]出现数组越界
			l--,r--;
			if(l == 0){
				cout << max(s[n] ^ x,st.query(st.rt[r],st.rt[0],s[n] ^ x)) << '\n';
			} else {
				cout << st.query(st.rt[r],st.rt[l - 1],s[n] ^ x) << '\n';
			}
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