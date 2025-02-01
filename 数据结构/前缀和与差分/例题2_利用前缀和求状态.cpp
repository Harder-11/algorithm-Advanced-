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
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
题意:
牛牛和牛妹有10个球,标号0~9,把n个球按编号为0,1,2,3...然后把10个球用10个杯子罩住
然后牛牛以一定的操作顺序以极快的速度交换这些杯子
换完之后牛牛问牛妹你看清楚从左到右的杯子中的小球的编号了吗?
由于牛妹的实力不好,所以向你求助,你发现牛牛置换杯子是有一定原则的
具体来说,牛牛有一个大小为n的操作序列
操作序列每一行表示一次操作都有两个非负整数a,b表示本次操作将交换从左到右数第a,b个杯子(a和b均从0开始数)
注意是杯子,不是直接交换的a号球和b号球
牛牛和牛妹一共玩了m次猜球游戏,每一轮游戏开始时,他都将杯子中的小球重置到从左往右依次为0,1,2....9的状态
然后在第i轮游戏中牛牛会按照操作序列中的第li个操作开始做,一直做到第ri个操作结束(l和r的编号从1开始计算)
由于你提前知道了牛牛的操作序列以及每一次游戏的l和r,请你帮助牛妹回答牛牛每一轮游戏结束时
从左到右的杯子中小球的编号是多少

思路:要求l到r范围内操作之后求的编号,显然用前缀和快速求区间的变化
*/
int n,m,p[N][15],id[15];

void solve(){
    cin >> n >> m;
    //初始化p数组,最开始是0,1,2,.....9
    for(int i = 0;i <= 9;i++) p[0][i] = i;
    for(int i = 1;i <= n;i++){
        int a,b;
        cin >> a >> b;
        //先把每一行复制到下一行,然后实现交换
        for(int j = 0;j <= 9;j++) p[i][j] = p[i - 1][j];
        swap(p[i][a],p[i][b]);
    }
    while(m--){
        int l,r;
        cin >> l >> r;
        //每次把l-1次时的状态给记录下来,记为初识值0,1,2....n
        //然后最终答案就是id[p[r][i]]
        for(int i = 0;i <= 9;i++){
            id[p[l - 1][i]] = i;
        }
        for(int i = 0;i <= 9;i++){
            cout << id[p[r][i]] << " ";
        }
        cout << '\n';
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