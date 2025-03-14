#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1000005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs1 = 1e9 + 9;
const int hs2 = 998244353;
const int base = 233;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
前置知识:
1.确定性有限状态自动机(DFA)
一个确定性有限状态自动机是一堆零件的集合
DFA是一张图,有一个开始节点,代表空串,有一堆点,各个点并没有实际意义(准确来讲部分自动机,但是不是所有的自动机都要求节点有意义)
点之间有边
和普通的图区别最大的一点就是,DFA的图的边是有意义的,一条边代表了一种字符
一个点必须有且仅有每一个字符的出边(如果某个出边没有意义,那么指向NULL)
那么我们发现,如果从起点出发,走出一段路径(随便走,不要求简单路径),那么这个路径可以代表一个字符串
定义一个字符串可以被一个DFA识别就是我们从初始点出发,走出这个字符串(显然这个路径必须是存在且唯一的,
因为每个节点的某种类型的出边仅有一条)之后,我们到达了某些我们指定的结点上,那么就认为这个节点可以被这个自动机识别

2.子串表示法
我们发现一件事:我们的后缀自动机,顾名思义就是可以识别某个字符串S的所有后缀的自动机,会有这样的性质
我们对这个自动机输入一个任意字符串a,如果这个字符串还在自动机的节点上而没有被打回NULL结点上
那么我们输入的字符串一定是原串的子串(因为此时还有输入一些字符让其变成后缀的可能,如果不是子串了就不可能成为后缀)
那么我们可以假设这样:可以表示一个串的所有子串,子串之间连边,但是这样时空复杂度都是O(N^2),不可取
那么我们可以想到,用一个点的集合right和一个长度len来描述一个子串
这个子串的特点就是,这个长度为len的子串在匹配主串S的时候,如果右端点∈right,那么就可以匹配
否则就不可以匹配,显然这样描述了多个位置不同,但是写起来一模一样的子串
为了节约资源,如果一堆子串的right集合相同,那么我们就将这些子串压到同一个节点上表示
这个节点只记录一个len,代表这个节点表示的所有子串中len的最大值,但是我们在具体实现的时候只记录len但是不记录right

后缀自动机的构建算法:
后缀自动机的构造算法是一个名为增量算法的东西,就是一个一个插入字符,这样我们需要考虑两件事
1.新建几个节点 2.新建的结点连到什么结点上
先考虑新建几个节点,更加准确的说是加入的第i个字符会产生几种新子串
第一种是S的第i个前缀,right集合只有i
第二种是S的第i个前缀的某些后缀,right集合有一堆,不止i
那么我们就新建两个节点np和nq分别代表第一种和第二种子串
问题来了,谁会向他们连边,它又会向谁连边呢?
尽管后缀自动机的节点定义很复杂,但是如果把表示的子串写出来,会发现不过是某一个字符串的一些后缀而已
因此边的转移的意义就是在这个字符串上加了一个字符x之后变成一个新的字符串,而这些后缀长度都增加了1
而个数不变,仅此而已
所以我们找到表示原来的第i-1个前缀的结点,让它连一条标号为x的边到np
但是我们会发现如果别的right集合包含i-1,那么也存在转移的可能,所以必须找到每一个right集合包含i-1的节点,那要怎么找呢?
Parent树
我们发现如果将某个节点的表示的串写出来,是某一个字符串的一些后缀
如果我们在字符串前加一个字符,那么right集合可能会缩小,因为这个串在原串可以匹配的位置就会减小
另外尽管我们只保存了len的最大值,但是len最小值是客观存在的
考虑这个串一个小一点的后缀,比如长度是len的最小值减1,那么这个后缀代表的节点的right集合必然包含原来节点的right集合
因为可以匹配的位置必然会增多,否则这个后缀也可以压缩到节点里面
然后这个right集合的包含关系可以映射为树上的父子关系
所以在后缀自动机中我们令fa[x]表示可以包含节点x的right集合,而且集合元素最小堆点
根据这个父子关系可以构成一个树叫做parent树
有了parent树,就不需要储存right集合了,因为现在我们可以找到这个点子树中所有的叶子节点(显然表示的前缀节点是且仅是叶子节点)
就可以找到这个点的right集合了
那么现在有了parent树之后,问题就好解决多了,我们枚举第i-1个前缀到根的所有节点即可,就是所有的包含i-1的right集合的结点
如果这个路径上的节点没有可以转移到x的出边,意味着原来不存在这样的子串,但现在有了,叫做np
所以直接连接一条标号为x,到np的出边即可
如果我们就这样跑完了整个路径,令fa[p] = start(开始结点)return即可,这种情况nq不存在
另一种比较棘手的情况,路径上出现了可以转移到x的出边,并且指向q
此时我们发现如果两个集合的right集合全等(也就是maxlen(当前结点) + 1 = maxlen(q))
因为如果最长的串right集合都可以转移，那么其他小一点串当然也可以转移)
我们只需要在q的right集合，以及q的祖先的right集合中插入i即可,所以我们只需要让fa[np]=q,就完成了隐性插入的工作(抱歉这种情况nq也不存在)
另一种更加辣手的情况，两个集合的right集合不全等
此时证明q已经过时了，该转移到的应该是nq，因为加了一个字符之后写出来的应该是nq代表的字符串，而right集合比q的多
同时，q转移到的点nq都可以，因为这两个串写出来一膜一样，所以复制一边q的出边到nq上，另外当前节点最长的点都可以转移到nq上
所以nq的len应该等于len[当前节点]+1
此时还没有完，当前结点的祖先如果有连向q的出边，那么都会因为同样的理由过时了，所以全部修改为nq，
最后是parent树的问题，显然nq的right集合是q的right集合∪i(np的right集合)所以令q和np的parent都为nq
同时q的所有祖先还是可以转移的，只是需要加入一个i，同理使用这样的隐性插入法，只需令fa[nq]=fa[q]即可

1.我们定义:
转移边:类似于AC自动机,转移边就是每次动态开出来的边
比如aababa,对于1号节点a,转移边可能是b或者a,因为存在有ab的子串也存在aa的子串
从根节点沿转移边所走的路径对应一个子串,根节点代表空串,其他节点表示同类子串的集合
其中,同类子串指的是结束位置相同的串
2.动态构建SAM,要维护三个数组
ch[x][c]:存节点x的转移边的终点
fa[x]:存节点x的链接边的终点
len[x]:存节点x的最长串的长度
3.抽离出图中的链接边,构建SAM
树上节点表示同类子串及其结束位置的结合
合法性:子节点的最短串的最长后缀 = 父节点的最长串

关键流程:
1.若ch[p][c]不存在,就从p向np建转移边(和AC自动机一样)
2.退出for循环时,p = 0,说明c是一个新字符
3.退出for循环时,p > 0,说明ch[p][c]存在,令q = ch[p][c]
(1)若p与q的距离 = 1,则从np向q建链接边
(2)若p和q的距离 > 1,则从np向nq建链接边
*/

ll cnt[N << 1],ans;
//tot是节点编号的,np总是指向最后创建的那个点
int tot = 1,np = 1;
//fa:链接边的终点,ch:转移边的终点,len最长串的长度
int fa[N << 1],ch[N << 1][26],len[N << 1];
vector<int> e[N << 1];

//传入的是字符的偏移量(0~25) 
void SAM(int c){
    //p:回跳指针,np:新点,q:链接点,nq:新链接点
    int p = np;
    np = ++tot;
    len[np] = len[p] + 1;
    //子串的出现次数
    cnt[np] = 1;
    //p沿着链接边回跳,从旧点向新点建转移边
    for(;p && !ch[p][c];p = fa[p]) ch[p][c] = np;
    //1.如果c是新字符,从新点向根节点建链接边(根节点是1)
    if(p == 0) fa[np] = 1;
    //如果c是旧字符
    else {
        //q是链接点
        int q = ch[p][c];
        //2.如果链接点合法,那么从新点向q建链接边
        //从np到q建树,从上往下dfs更方便
        if(len[q] == len[p] + 1) fa[np] = q;
        //3.如果链接点不合法,则裂开p点,重建两类边
        else {
            //nq是新链接点
            int nq = ++tot;
            len[nq] = len[p] + 1;
            //重建nq,q和np的链接边
            fa[nq] = fa[q];
            //q的链接边指向nq
            fa[q] = nq;
            //np向nq建链接边
            fa[np] = nq;
            //指向q的转移边改为指向nq,所以判断条件是ch[p][c] = q
            //注意这里是修改操作,是沿着SAM建好的树一路往上走
            for(;p && ch[p][c] == q;p = fa[p]) ch[p][c] = nq;
            //把从q发出的转移边复制给nq
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
        }
    }
}

void dfs(int u){
    for(auto v : e[u]){
        dfs(v);
        cnt[u] += cnt[v];

    }
    if(cnt[u] > 1) ans = max(ans,1ll * cnt[u] * len[u]);
}

void solve(){
    string s;
    cin >> s;
    for(int i = 0;s[i];i++){
        SAM(s[i] - 'a');
    }
    for(int i = 2;i <= tot;i++) e[fa[i]].push_back(i);
    dfs(1);
    cout << ans << '\n';
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