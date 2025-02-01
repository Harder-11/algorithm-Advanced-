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
SDOI2008 洞穴探险
一开始有n个独立的点,m次操作,每次操作为以下之一
1.Connect u v:在u,v两点之间建一条边
2.Destroy u v:删除在u,v两点之间的边,保证之前存在这样的一条边
3.Query u v:询问u,v两点是否联通
保证在任何时候图的形态都是一个森林
n <= 1e4,m <= 2e5

思路:LCT的模版题,建好一棵LCT就直接解决了
*/

struct LCT {
	int ch[N][2],fa[N],tag[N];
	void clear(int x){
		ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0;
	}
	//检查x是不是fa[x]的右子树
	int getch(int x){
		return ch[fa[x]][1] == x; 
	}
	int isroot(int x){
		return (ch[fa[x]][0] != x && ch[fa[x]][1] != x);
	}
	//pushdown交换左右儿子是所有LCT必需的操作
	void pushdown(int x){
		if(tag[x]){
			if(ch[x][0]){
				swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
				tag[ch[x][0]] ^= 1;
			}
			if(ch[x][1]){
				swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
				tag[ch[x][1]] ^= 1;
			}
			tag[x] = 0;
		}
	}
	void update(int x){
		if(!isroot(x)) update(fa[x]);
		pushdown(x);
	}
	void rotate(int x){
		int y = fa[x],z = fa[y],chx = getch(x),chy = getch(y);
		fa[x] = z;
		if(!isroot(y)) ch[z][chy] = x;
		ch[y][chx] = ch[x][chx ^ 1];
		fa[ch[x][chx ^ 1]] = y;
		ch[x][chx ^ 1] = y;
		fa[y] = x;
	}
	//要注意splay和access的本质区别,splay的while循环条件是让x到达最顶端的根节点
	//而access的while终止条件是让x到达splay里面的最左边的结点(也就是splay的根节点)
	void splay(int x){
		update(x);
		while(!isroot(x)){
			int y = fa[x];
			if(!isroot(y)){
				rotate(getch(x) == getch(y) ? y : x);
			}
			rotate(x);
		}
	}
	void access(int x){
		int tmp = 0;
		while(x){
			splay(x);
			ch[x][1] = tmp;
			tmp = x;
			x = fa[x]; 
		}
	}
	//根据上述的区别,这里的access实际是让x到达根节点所在的splay中
	//然后调用splay方法到达的结构树的根节点处
	void makeroot(int x){
		access(x);
		splay(x);
		swap(ch[x][0],ch[x][1]);
		tag[x] ^= 1;
	}
	//找root操作,在一个splay里面一直往左儿子找就是root
	int find(int x){
		access(x);
		splay(x);
		while(ch[x][0]) x = ch[x][0];
		splay(x);
		return x;
	}
	void link(int x,int y){
		makeroot(x);
		fa[x] = y;
	}
	void cut(int x,int y){
		makeroot(x);
		access(y);
		splay(y);
		ch[y][0] = fa[x] = 0;
	}
} st;

int n,q,x,y;
string op;

void solve(){
	cin >> n >> q;
	while(q--){
		cin >> op >> x >> y;
		if(op[0] == 'C'){
			st.link(x,y);
		} else if(op[0] == 'D'){
			st.cut(x,y);
		} else {
			if(st.find(x) == st.find(y)){
				cout << "Yes" << '\n';
			} else cout << "No" << '\n';
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