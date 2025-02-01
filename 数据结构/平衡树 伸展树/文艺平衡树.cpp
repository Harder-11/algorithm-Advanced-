#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 500005;
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
文艺平衡树:
是一种数据结构来维护一个有序数列
需要提供以下操作:翻转一个区间[l,r]
比如一个数组是5 4 3 2 1,如果翻转[2,4],那么就变成了[5,2,3,4,1]
输入:第一行为n,m表示初识序列有n个数,依次为1,2,3,4,....n,然后翻转m次
接下来m行每行2个数[l,r],数据保证1 <= l <= r <= n
然后输出操作m次之后的数组

思路:每次翻转都用懒标记去标记,然后每次都更新即可
注意,本题说明了是1...n,没有重复元素就可以去掉cnt这个变量
*/

struct tnode {
	int ch[2],fa,sz;
	int flag,val;
} tr[N];

int root,id = 0;
int n,m;

void pushup(int u){
	tr[u].sz = tr[tr[u].ch[0]].sz + tr[tr[u].ch[1]].sz + 1;
}

void pushdown(int u){
    if(tr[u].flag){
        int lson = tr[u].ch[0];
        int rson = tr[u].ch[1];
        swap(tr[lson].ch[0],tr[lson].ch[1]);
        swap(tr[rson].ch[0],tr[rson].ch[1]);
        tr[lson].flag ^= 1;
        tr[rson].flag ^= 1;
        tr[u].flag = 0;
    }
}


void rotate(int u){
	int fa = tr[u].fa;
	int gfa = tr[fa].fa;
	int t1 = (u != tr[fa].ch[0]);
	int t2 = (fa != tr[gfa].ch[0]);
	int ch = tr[u].ch[t1 ^ 1];
	tr[u].fa = gfa;
	tr[u].ch[t1 ^ 1] = fa;
	tr[fa].ch[t1 ^ 0] = ch;
	tr[fa].fa = u;
	tr[ch].fa = fa;
	tr[gfa].ch[t2 ^ 0] = u;
	pushup(fa),pushup(u);
}

void splay(int u,int k){
	int x = u;
	while(tr[x].fa != k){
		int y = tr[x].fa;
		int z = tr[y].fa;
		if(z != k){
			if((tr[y].ch[1] == x) ^ (tr[z].ch[1] == y)){
				rotate(y);
			} else {
				rotate(x);
			}
		}
		rotate(x);
	}
	if(!k) root = u;
}

void insert(int val){
	int u = root,fa = 0;
	while(u){
		fa = u;
		u = tr[u].ch[val > tr[u].val];
	}
	u = ++id;
	if(fa){
		tr[fa].ch[val > tr[fa].val] = u;
	}
	tr[u].val = val;
	tr[u].fa = fa;
	splay(u,0);
}

int kth(int k){
	int u = root;
	while(1){
		pushdown(u);
		if(tr[tr[u].ch[0]].sz >= k){
			u = tr[u].ch[0];
		} else if(tr[tr[u].ch[0]].sz + 1 == k){
			return u;
		} else {
			k -= tr[tr[u].ch[0]].sz + 1;
			u = tr[u].ch[1];
		}
	}
	return -1;
}

void rev(int l,int r){
	l++,r++;
	int x = kth(l - 1);
	int y = kth(r + 1);
	splay(x,0);
	splay(y,x);
	int o = tr[y].ch[0];
	tr[o].flag ^= 1;
	swap(tr[o].ch[0],tr[o].ch[1]);
}

//根据中序遍历有单调性来打印答案
void print(int u){
	pushdown(u);
	if(tr[u].ch[0]) print(tr[u].ch[0]);
	if(tr[u].val != 0 && tr[u].val != n + 1){
		cout << tr[u].val << " ";
	}
	if(tr[u].ch[1]) print(tr[u].ch[1]);
}

void solve(){
	cin >> n >> m;
	for(int i = 0;i <= n + 1;i++){
		insert(i);
	}
	while(m--){
		int l,r;
		cin >> l >> r;
		rev(l,r);
	}
	print(root);
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