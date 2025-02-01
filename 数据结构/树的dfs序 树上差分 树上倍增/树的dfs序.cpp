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
#define ls u << 1
#define rs u << 1 | 1
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;


/*
在多叉树里面,常用的dfs序有三种:
1.dfs序:类似二叉树的先序遍历
2.扩展dfs序:类似二叉树的先序 + 中序
3.欧拉序:类似二叉树的先序 + 后续

1.dfs序
为什么要构建dfs序?
--树上问题的dfs序构建了树和序列的桥梁
绝大多数的子树操作类问题,树链操作的问题,本质就是利用dfs序列把树结构整理成数组,最后维护数组即可

比如首先看最简单的问题:有根树子树查询类问题
给定一棵树,有q次操作,给某个节点及其子树的所有节点值都+1

定义多叉树的dfs序就是一种类二叉树的先序遍历
定义dfn是dfs遍历的标号计数变量
定义id[x](L)数组是x节点在遍历的过程中被标记的dfn的值
定义idx(mp)[x]数组是dfn为x节点时那个节点
那么我们可以发现,对于一棵多叉树,将其利用dfs序重标号之后,每一刻子树的dfs序都是连续的
之前定义的id数组实际还有一个含义,表示L数组
定义L[x]数组表示dfs遍历的过程中x所覆盖子树的dfn最小值,L数组实际就是id数组
定义R[x]数组表示dfs遍历的过程中x所覆盖子树的dfn最大值,有了LR数组,子树的维护问题就变成了数组的区间维护问题
(注意:id(L),R,idx这三个数组在轻重链剖分,长链剖分和树上启发式合并里面都会用到,事实上所有关于树的dfs序列
都可以预处理出这几个数组)

2.扩展dfs序(了解即可,基本没用)
扩展dfs序是一种类中序的处理
一般来说多叉树是用不到这种类中序的,因为多叉树不想二叉树一样有左右顺序的关系,但是扩展dfs序被巧妙地
运用在了一个黑科技LCA的模版中,该模版支持O(NlogN)时间预处理,O(1)在线查询任意两点的LCA
与之前的dfs序一样,数组的含义没有变化,同样是id(L),R,idx这些
不一样的是,我们要做一个类中序,即在每个子树遍历之前做一个对于当前节点的额外遍历,额外遍历不是真正的初次遍历
不需要维护id(L)数组
在遍历的过程中,维护一个pair类型的ST表,pair<deep,id>ST
扩展dfs序:LCA问题->RMQ问题
笛卡尔树:RMQ问题->LCA问题

3.欧拉序
欧拉序是一种类前后序,原本我们处理LR数组的时候,一般来说只对L进行dfn++的操作
换句话说,就是其实并没有为回溯的时候分配dfn
一般认为只有分配了dfn才能够称得上是一次遍历,不然只不过是在函数调用的过程中路过了一下

欧拉序和dfs的区别在于要不要对R(回溯访问)分配dfn,但是其实不分配也是可以记录回溯时的dfn的,除非有用
一般来说,回溯时分配dfn的作用有两点
一是为了抵消前后的影响,例如树链上莫队,树链求异或和
*/

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