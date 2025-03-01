#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1005;
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
const int M = 300010;
int n;
int h[N+5], to[M], nxt[M], w[M], cnt;
int q[N+5], dep[N+5];
void add(int u,int v,int c){
    nxt[cnt] = h[u];
    to[cnt] = v;
    w[cnt] = c;
    h[u] = cnt++;
}
void addEdge(int u,int v,int c){
    add(u,v,c);
    add(v,u,0);
}
bool bfs(int s,int t){
    memset(dep,0,sizeof(dep));
    memset(q,0,sizeof(q));
    int l = 0, r = 0;
    dep[s] = 1;
    q[r++] = s;
    while(l < r){
        int u = q[l++];
        if(u == t) return true;
        for(int i = h[u]; ~i; i = nxt[i]){
            int v = to[i];
            if(w[i] && !dep[v]){
                dep[v] = dep[u] + 1;
                q[r++] = v;
            }
        }
    }
    return false;
}
int dfs(int x,int flow,int t){
    if(x == t) return flow;
    int sum = 0;
    for(int i = h[x]; ~i; i = nxt[i]){
        int v = to[i];
        if(w[i] && dep[x] + 1 == dep[v]){
            int tmp = dfs(v, min(w[i], flow - sum), t);
            w[i] -= tmp;
            w[i^1] += tmp;
            sum += tmp;
            if(sum == flow) return sum;
        }
    }
    return sum;
}
int dinic(int s,int t){
    int ans = 0;
    while(bfs(s,t)){
        ans += dfs(s, INF, t);
    }
    return ans;
}
void solve(){
    cin >> n;
    int MAX_M = (N - 1) / 2;
    int s = 0, t = 2 * MAX_M + 1;
    memset(h, -1, sizeof(h));
    cnt = 0;
    int current_flow = 0;
    int id = 0;
    while(true){
        id++;
        addEdge(0, 2 * id - 1, 1);
        addEdge(2 * id - 1, 2 * id, 1);
        addEdge(2 * id, t, 1);
        for(int j = 1; j < id; j++){
            int sum = j + id;
            int sq = int(sqrt(sum));
            if(sq * sq == sum){
                addEdge(2 * j, 2 * id - 1, 1);
            }
        }
        int add_flow = dinic(s, t);
        current_flow += add_flow;
        if(id - current_flow > n){
            id--;
            cout << id << "\n";
            break;
        }
    }
    vector<vector<int>> chains;
    vector<int> nxt_ball(id + 1, 0);
    vector<bool> has_incoming(id + 1, false);
    for(int i = 1; i <= id; i++){
        int out_node = 2 * i;
        for(int i_edge = h[out_node]; ~i_edge; i_edge = nxt[i_edge]){
            int v = to[i_edge];
            if(v % 2 == 1 && v >= 1 && v <= 2 * id - 1){
                if(w[i_edge] == 0){
                    int ball_v = (v + 1) / 2;
                    nxt_ball[i] = ball_v;
                    has_incoming[ball_v] = true;
                    break;
                }
            }
        }
    }
    for(int i = 1; i <= id; i++){
        if(!has_incoming[i]){
            vector<int> chain;
            int cur = i;
            while(cur){
                chain.push_back(cur);
                cur = nxt_ball[cur];
            }
            chains.push_back(chain);
        }
    }
    while(chains.size() < (size_t)n) {
        chains.push_back(vector<int>());
    }
    sort(chains.begin(), chains.end(), [](const vector<int>& a, const vector<int>& b){
        int A = a.empty() ? INT_MAX : a[0];
        int B = b.empty() ? INT_MAX : b[0];
        return A < B;
    });
    for(int i = 0; i < n; i++){
        if(!chains[i].empty()){
            for (int j = 0; j < (int)chains[i].size(); j++){
                cout << chains[i][j] << (j + 1 == chains[i].size() ? "\n" : " ");
            }
        } else {
            cout << "\n";
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while(t--){
        solve();
    }
    return 0;
}
 