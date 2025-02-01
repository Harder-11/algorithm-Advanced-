#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200005;

/*
动态树:
树上查询问题指的是,给定一个图论中的树结构,需要对树上的子树或者链进行一系列增删查改的问题
和序列问题中一般常数的动态和静态不一样,动态树问题一般指的是树结构发生变化
注意:一般对于纯换根操作,不视为动态树问题
常见的动态树有三种:LCT;ETT;Top tree

LCT的底层原理叫做:用splay维护动态的链分解
通过树链剖分和dfs序,将一棵结构树分解成若干个单链,然后我们可以用splay维护单链,这里链可以很方便进行拼接和拆分
(也就是merge和split方法,在LCT中被称为link和cnt)

我们把一条树链当做一个点,把轻边(并不包含size或者len,任意一条边都可以是重边)当成树上的边,我们可以得到一棵结构树,这个地方和树链剖分是一样的
事实上,LCT总能在log级的时间内把需要查询的区间构造到同一链中
那么宏观上:根节点一定处于LCT外层结构树的根部,微观上:因为LCT中每个结点都是一棵splay,key是相对深度,根节点是
相对深度最小的节点,所以是中序遍历的第一个点

LCT的基本函数:
access(x):不换根,将根节点到x节点构造到同一条链中(相当于打通x到根节点的通路,并且是最重要的操作,所有的操作都是基于access的)
change/make/set root(x):将节点x设置成整棵树的根
query path(x,y):将x和y构造到同一条链上,并且链的收尾是x,y
link(x,y):将x,y连接到LCT中
cut(x,y)将x,y从LCT中断开
lca(x,y,z):查询以x为根,y和z的lca
findroot():查询x结点所在树结构的树根是谁,类比并查集

1.对于最重要的access方法,涉及到splay的分离和合并,该怎么做呢?
注意!!!!!access方法是为了保证后续方法的高效性,是为了保证复杂度而产生的!!!
我们假设当前访问到x节点,我们先把x延伸到它所在的splay的根,然后断开它的右儿子,因为被访问到的点是没有
重儿子的,这样x所在的splay就是一条从根的方向延伸过来的一条树链(并不完整),然后我们访问x所在树链的路径
父节点,并把它旋转到它所在splay的根,然后断开它的右儿子,并连接到x所在的树链,不断重复这一过程
最后我们就会得到一条从根节点延伸到x的一条树链,代码如下,很简短
int access(int u){
	int tmp = 0;
	//一直处理到u是根节点
	while(u){
		//在splay里面把当前结点旋转到根
		splay(u);
		//右子树断开(第一次是置空,如果不是第一次就是将当前节点的右儿子赋值为
		上一次丢弃的部分)
		tr[u].ch[1] = tmp;
		tmp = u;
		//这里爬的轻边,在splay之间进行转移
		u = tr[u].fa;
	}
	return tmp;
}

2.现在我们实现lca函数,因为我们从根节点画两条通路通向两个点(x,y)的时候,两条通路总会重合一部分
这些重合的部分在我们两次access操作中是不会变的,那么最后一次变化的点就是两点的最近公共祖先
这也就是我们我们在access函数设置了返回值并且返回tmp的原因,tmp就是最后一次变化的点
那么代码就及其简单:
int lca(int u,int v){
	access(u);
	return access(v);
}

3.对于findroot():查询原树的树根,并且LCT的树根,准确来说是寻找LCT中主链deep最小的点
实现:在access(v)之后,根节点一定是v所属的伸展树深度最小的点,我们先把v旋转到它所属的伸展树的根,
再从v开始沿着伸展树向左走,直到不能再向左,这个点就是我们要找的根节点
注意:由于我们使用的是splay作为底层的数据结构,我们还需要对根节点进行splay操作,不然会导致势能均摊失败
代码实现如下:
int findroot(int u){
	access(u);
	splay(u);
	int tmp = u;
	while(tr[tmp].ch[0]){
		tmp = tr[tmp].ch[0];
	}
	//把原本的根节点重新转到根节点位置,防止被卡(因为上面代码可能导致splay变成一条链)
	splay(tmp);
	return tmp;
}

4.change/make root(x):将x切换为树根
因为我们已经实现了access操作,我们可以避免牵扯到多颗splay,所以我们可以先用access操作把原树根和新树根
链接到同一个树链上面,这样变化树根之后对其他的splay都没有任何影响
其实本质就是整个重链发生了一次翻转,splay的翻转,翻转操作直接打懒标记懒着不动即可(同区间翻转)
void makeroot(int u){
	access(u);
	splay(u);
	tr[u].rev ^= 1;
}

5.join / link(合并两棵link cut tree)
这个部分很像并查集,假设两棵树的要练的节点分别是u,v,那么就把u变成第一棵树的树根,然后把u的fa置为v即可
void link(int u,int v){
	makeroot(u);
	tr[u].fa = v;
}

6.cut(拆分)
cut是link的逆操作,但是步骤比link稍微繁琐一点
比如要断开x,y两点,先用makeroot把x变成根节点,然后access(5),然后直接断开即可
void cut(int u,int v){
	makeroot(u);
	access(v);
	//由于不知道u和v是左子树还是右子树关系
	//那么这里我们就干脆将v变成splay的根,然后此时u一定就是左子树上,这样就是tr[v].ch[0]
	splay(v);
	tr[v].ch[0] = tr[u].fa = 0;
}
7.如果现在需要维护树上某两点的路径信息,那么就能直接用access和make root来构建了
void query_path(int u,int v){
	makeroot(u);
	access(y);
	splay(y);
	//在此处进行增删改查,例如tr[v].lazy += 1
}
对于建LCT树,我们就直接用Link函数每次合并两个节点就可以了
!!!!!!!!注意:LCT是如何判断某个splay中的结点有哪些的呢?
--利用的ch[N][2]数组,如果两个相邻的结点不是在一个splay里面,
那么二者只有fa数组有交集,而ch数组是不填充的,所以通过ch数组判断
splay中的终止条件(这样每个splay里的根节点在ch数组里面都是满足is_root的)

*/

//以下代码就是LCT的几个主要的函数(包括了splay树)

//rev表示翻转标记,laz表示权值标记,val是点权
//sum是路径权值和,siz是辅助树上子树的大小
int ch[N][2],fa[N],sum[N],val[N],rev[N],laz[N],siz[N];

bool is_root(int u){
	return ((ch[fa[u]][0] != u) && (ch[fa[u]][1] != u));
}

void pushup(int u){
	siz[u] = siz[ch[u][0]] + siz[ch[u][1]];
}

void pushdown(int u){
	//(维护的信息)
}

void update(int u){
	if(!is_root(u)) update(fa[u]);
	pushdown(u);
}

void rotate(int x){
	int y = fa[x],z = fa[y],k = ch[fa[x]][1] == x;
	//这句话一定要写在最前面,和普通splay的区别在这里,
	if(!is_root(y)) ch[z][ch[z][1] == y] = x;
	ch[y][k] = ch[x][!k];
	fa[ch[x][!k]] = y;
	ch[x][!k] = y;
	fa[y] = x;
	fa[x] = z;
	pushup(y);
	pushup(x);
}

void splay(int x){
	update(x);
	for(int f;f = fa[x],!is_root(x);rotate(x)){
		if(!is_root(f)) rotate((ch[fa[f]][1] == x) ^ (ch[fa[x]][1]) ? x : f);
	}
}

int access(int u){
	int tmp = 0;
	//一直处理到u是根节点
	while(u){
		//在splay里面把当前结点旋转到根
		splay(u);
		//右子树断开(第一次是置空,如果不是第一次就是将当前节点的右儿子赋值为
		//(上一次丢弃的部分)
		ch[u][1] = tmp;
		tmp = u;
		//这里爬的轻边,在splay之间进行转移
		u = fa[u];
	}
	return tmp;
}

int lca(int u,int v){
	access(u);
	return access(v);
}

int findroot(int u){
	access(u);
	splay(u);
	int tmp = u;
	while(ch[tmp][0]){
		tmp = ch[tmp][0];
	}
	//把原本的根节点重新转到根节点位置,防止被卡(因为上面代码可能导致splay变成一条链)
	splay(tmp);
	return tmp;
}

void makeroot(int u){
	access(u);
	splay(u);
	rev[u] ^= 1;
}

void link(int u,int v){
	makeroot(u);
	fa[u] = v;
}

void cut(int u,int v){
	makeroot(u);
	access(v);
	splay(v);
	ch[v][0] = fa[u] = 0;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(t--){
        solve();
    }
    return 0;
}