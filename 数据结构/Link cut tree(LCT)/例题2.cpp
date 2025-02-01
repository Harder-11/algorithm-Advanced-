#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int MAXN = 200005;
const int mod = 51061;
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
给出一棵有n个节点的树,每个点的初识权值为1,q次操作,每次操作均为以下四种之一
1.- u1 v1 u2 v2:将树上u1,v1之间的边删去,连接u2,v2两点
2.+ u v c:将树上u,v两点之间的路径上的点权 + c
3.* u v c:将树上u,v两点之间的路径上的点权 * c
4./ u v:输出树上u,v两点之间的路径上的点权之和,并且对51061取模
1 <= n,q <= 1e5,0 <= c <= 1e4;

注意下传标记的时候先下传乘法标记,再下传加法标记即可,其他和LCT一样
*/

ll n,q,u,v,c;
char op;

struct Splay {
  long long ch[MAXN][2], fa[MAXN], siz[MAXN], val[MAXN], sum[MAXN], rev[MAXN],
      add[MAXN], mul[MAXN];

  void clear(long long x) {
    ch[x][0] = ch[x][1] = fa[x] = siz[x] = val[x] = sum[x] = rev[x] = add[x] =
        0;
    mul[x] = 1;
  }

  long long getch(long long x) { return (ch[fa[x]][1] == x); }

  long long isroot(long long x) {
    clear(0);
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
  }

  void maintain(long long x) {
    clear(0);
    siz[x] = (siz[ch[x][0]] + 1 + siz[ch[x][1]]) % mod;
    sum[x] = (sum[ch[x][0]] + val[x] + sum[ch[x][1]]) % mod;
  }

  void pushdown(long long x) {
    clear(0);
    if (mul[x] != 1) {
      if (ch[x][0])
        mul[ch[x][0]] = (mul[x] * mul[ch[x][0]]) % mod,
        val[ch[x][0]] = (val[ch[x][0]] * mul[x]) % mod,
        sum[ch[x][0]] = (sum[ch[x][0]] * mul[x]) % mod,
        add[ch[x][0]] = (add[ch[x][0]] * mul[x]) % mod;
      if (ch[x][1])
        mul[ch[x][1]] = (mul[x] * mul[ch[x][1]]) % mod,
        val[ch[x][1]] = (val[ch[x][1]] * mul[x]) % mod,
        sum[ch[x][1]] = (sum[ch[x][1]] * mul[x]) % mod,
        add[ch[x][1]] = (add[ch[x][1]] * mul[x]) % mod;
      mul[x] = 1;
    }
    if (add[x]) {
      if (ch[x][0])
        add[ch[x][0]] = (add[ch[x][0]] + add[x]) % mod,
        val[ch[x][0]] = (val[ch[x][0]] + add[x]) % mod,
        sum[ch[x][0]] = (sum[ch[x][0]] + add[x] * siz[ch[x][0]] % mod) % mod;
      if (ch[x][1])
        add[ch[x][1]] = (add[ch[x][1]] + add[x]) % mod,
        val[ch[x][1]] = (val[ch[x][1]] + add[x]) % mod,
        sum[ch[x][1]] = (sum[ch[x][1]] + add[x] * siz[ch[x][1]] % mod) % mod;
      add[x] = 0;
    }
    if (rev[x]) {
      if (ch[x][0]) rev[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
      if (ch[x][1]) rev[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
      rev[x] = 0;
    }
  }

  void update(long long x) {
    if (!isroot(x)) update(fa[x]);
    pushdown(x);
  }

  void print(long long x) {
    if (!x) return;
    pushdown(x);
    print(ch[x][0]);
    printf("%lld ", x);
    print(ch[x][1]);
  }

  void rotate(long long x) {
    long long y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
    fa[x] = z;
    if (!isroot(y)) ch[z][chy] = x;
    ch[y][chx] = ch[x][chx ^ 1];
    fa[ch[x][chx ^ 1]] = y;
    ch[x][chx ^ 1] = y;
    fa[y] = x;
    maintain(y);
    maintain(x);
    maintain(z);
  }

  void splay(long long x) {
    update(x);
    for (long long f = fa[x]; f = fa[x], !isroot(x); rotate(x))
      if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
  }

  void access(long long x) {
    for (long long f = 0; x; f = x, x = fa[x])
      splay(x), ch[x][1] = f, maintain(x);
  }

  void makeroot(long long x) {
    access(x);
    splay(x);
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }

  long long find(long long x) {
    access(x);
    splay(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }
} st;

main() {
  scanf("%lld%lld", &n, &q);
  for (long long i = 1; i <= n; i++) st.val[i] = 1, st.maintain(i);
  for (long long i = 1; i < n; i++) {
    scanf("%lld%lld", &u, &v);
    if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
  }
  while (q--) {
    scanf(" %c%lld%lld", &op, &u, &v);
    if (op == '+') {
      scanf("%lld", &c);
      st.makeroot(u), st.access(v), st.splay(v);
      st.val[v] = (st.val[v] + c) % mod;
      st.sum[v] = (st.sum[v] + st.siz[v] * c % mod) % mod;
      st.add[v] = (st.add[v] + c) % mod;
    }
    if (op == '-') {
      st.makeroot(u);
      st.access(v);
      st.splay(v);
      if (st.ch[v][0] == u && !st.ch[u][1]) st.ch[v][0] = st.fa[u] = 0;
      scanf("%lld%lld", &u, &v);
      if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
    }
    if (op == '*') {
      scanf("%lld", &c);
      st.makeroot(u), st.access(v), st.splay(v);
      st.val[v] = st.val[v] * c % mod;
      st.sum[v] = st.sum[v] * c % mod;
      st.mul[v] = st.mul[v] * c % mod;
    }
    if (op == '/')
      st.makeroot(u), st.access(v), st.splay(v), printf("%lld\n", st.sum[v]);
  }
  return 0;
}