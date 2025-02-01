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
伸展树维护的特长:
1.区间拼接
2.区间翻转
3.区间大段插入
以下代码展示了splay的rotate,insert,kth,split和link操作
*/

struct tnode {
	int ch[2];
	int fa;
	int num,cnt,size,rev;
}tr[N << 2];
int stot;

//rot单旋转操作,同时处理左旋和右旋
//只是了解即可,实际用处极小,而且会被FHQ Treap短小精炼的代码取代
void rot(int u){
	//这里得到u节点的父节点以及父节点的父节点
	int fa = tr[u].fa;
	int gfa = tr[fa].fa;
	//t1来记录当前节点是不是父节点的左子树
	//如果是左子树那么t1置为0,否则就置为1
	int t1 = (u != tr[fa].ch[0]);
	//t2来记录父节点是否为父节点的父节点的左子树
	int t2 = (fa != tr[gfa].ch[0]);
	//ch令为tr[u].ch[t1 ^ 1],那么如果t1 = 1,ch就是u的左子树,如果t1 = 0,那么就是u的右子树
	//那么就说明从u的父节点到u的子节点是折线而不是直线
	int ch = tr[u].ch[t1 ^ 1];
	tr[u].fa = gfa;
	//对于左旋来说,如果t1 = 1,那么说明u是fa的右子树,那么说明当前结点存的值 > fa结点存的值
	//那么旋转之后的fa应该就是u的左子树,正好对于t1 ^ 1 = 0
	//同理如果t1 = 0,此时u是fa的左子树,那么当前存的值 < fa结点存的值
	//那么旋转之后fa应该是u的右子树,对应t1 ^ 1 = 1
	//右旋也是同理,u和fa的位置关系与值大小关系是和左旋一模一样的
	tr[u].ch[t1 ^ 1] = fa;
	//如果是左旋,那么此时此时u.fa的左儿子更新为ch,和下面tr[ch].fa = fa对应
	tr[fa].ch[t1 ^ 0] = ch;
	//显然交换之后u的父节点的.fa换位u
	tr[fa].fa = u;
	//由于u旋转之后(假设是左旋)此时右儿子连上了原本的u.fa
	//那么原本u的右儿子就没地方放了,此时就只能放在旋转后的u.fa的左儿子上面
	tr[ch].fa = fa;
	//这里和t1的处理同理,如果原本u.fa是u.fa.fa的右儿子,那么t2 = 1
	//那么此时说明了u.fa.fa是这些节点里面最小的元素,那么最终u应该是tr[gfa]的右儿子,那么就对应了t2 ^ 0 = 1
	tr[gfa].ch[t2 ^ 0] = u;
}

//splay函数实现双旋,平摊复杂度是logN
//那么总体复杂度就是O(NlogN)
int splay(int u){
	//u.fa存在才进行旋转,否则此时u就是根节点,旋转没有意义
	while(tr[u].fa){
		int fa = tr[u].fa;
		int gfa = tr[fa].fa;
		if(gfa){
			//利用异或操作同时处理左和右两种情况,一字型才进行双旋
			//如果是一字形,那么异或值就是0,那么就旋转父节点然后转u
			//如果是之字形,那么选择u即可(选择了u之后再选择u第二次相当于没转)
			(tr[fa].ch[0] == u) ^ (tr[gfa].ch[0] == fa) ? rot(u) : rot(fa);
		}
		rot(u);
	}
	return u;
}

//插入操作,从根节点开始插入一个值为num的数字
int insert(int u,int num){
	//相当于二分如果num > tr[u].num,那么就是往右子树找,u = tr[u].ch[1]
	//如果num < tr[u].num,那么往左子树找,u = tr[u].ch[0];
	//u会停在某个叶节点上,因为此时tr[u].ch[0] = tr[u].ch[1] = 0,直接退出循环
	while(u && tr[u].num != num && tr[u].ch[num > tr[u].num]){
		u = tr[u].ch[num > tr[u].num];
	}
	if(u && tr[u].num == num){
		//可能有重复的值,所以tr的结构体要有cnt类型
		tr[u].cnt++;
		return splay(u);
	}
	//如果以上条件都不满足,那么就在tr数组新开一个点作为平衡树的新节点
	tr[++stot].num = num;
	tr[stot].cnt = tr[stot].size = 1;
	tr[stot].rev = 0;
	tr[stot].fa = u;
	tr[stot].ch[0] = tr[stot].ch[1] = 0;
	//记得把u的儿子添上
	tr[u].ch[num > tr[u].num] = stot;
	u = stot;
	return splay(u);
}

//kth():找索引的第k大,不计算重复的元素
int kth(int u,int k){
	while(1){
		if(k <= tr[tr[u].ch[0]].size){
			u = tr[u].ch[0];
		} else if(k > tr[tr[u].ch[0].size] + 1){
			k -= tr[tr[u].ch[0]].size + 1;
			u = tr[u].ch[1];
		} else {
			return splay(u);
		}
	}
}

//将两个splay合并
int link(int u1,int u2){
	//如果一棵树是空树,那么返回另一棵树就行,用位运算很简洁
	if(!u1 || !u2) return u1 | u2;
	//访问左边树的最右侧最下方的节点,然后kth()会把该节点转到root
	//那么此时该节点的右边是空的
	//然后直接把该root连上右边树的根节点作为右儿子即可
	u1 = kth(u1,tr[u1].size);
	tr[u1].ch[1] = u2;
	tr[u2].fa = u1;
	return u1;
}

//将一个splay划开,把u切割成u1和u2,切割点是k
void cuts(int u,int k,int &u1,int &u2){
	if(k == 0){
		u1 = 0;
		u2 = u;
		return;
	}
	//还是找k,然后把k节点旋转到root位置
	u1 = kth(u,k);
	u2 = tr[u1].ch[1];
	//最后划开即可
	tr[u1].ch[1] = tr[u2].fa = 0;
}


void solve(){}

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