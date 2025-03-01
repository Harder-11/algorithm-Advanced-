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
带有费用的网络流图:G=(V,E,C,W)
V:顶点;E:弧;C:弧的容量;W:单位流量的费用
保证s到t最大的前提下,所需费用最小,这就是是最小费用最大流的问题

基本思路:
把弧<i,j>的单位费用w[i,j]当做弧<i,j>的路径长度,每次找从源点s到汇点t长度最短(费用最小)
的可增广的路径进行增广
1.最小费用可增广路
2.路径s到t的长度即单位流量的费用
本质就是把EK算法的广搜改为SPFA(因为残留网会存在负权边,不能用Dij)
*/

int n;
//cap:弧容量,flow:弧已经流过的流量,cost:边的费用
struct node {
    int to,nxt,cost,cap,flow;
} e[N];
int h[N],cnt;
//注意这里的pre记录的是与节点相邻的反边,而不是记录的上一个节点
int dis[N],vis[N],pre[N];

bool spfa(int s,int t){
    queue<int> q;
    for(int i = 0;i < n;i++){
        dis[i] = INF;
        vis[i] = 0;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for(int i = h[u];i != -1;i = e[i].nxt){
            int v = e[i].to;
            if(e[i].cap > e[i].flow && dis[v] > dis[u] + e[i].cost){
                dis[v] = dis[u] + e[i].cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1) return 0;
    return 1;
}

int mincostMaxflow(int s,int t,int &cost){
    int flow = 0;
    cost = 0;
    while(spfa(s,t)){
        int mn = INF;
        for(int i = pre[t];i != -1;i = pre[e[i ^ 1].to]){
            if(mn > e[i].cap - e[i].flow){
                mn = e[i].cap - e[i].flow;
            }
        }
        for(int i = pre[t];i != -1;i = pre[e[i ^ 1].to]){
            e[i].flow += mn;
            e[i ^ 1].flow -= mn;
            cost += e[i].cost * mn;
        }
        flow += mn;
    }
    return flow;
}

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