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

/*
一个长度为n的"RBY"三原色序列有四种操作
1.mix j1,j2...jm(子序列):把序列的第ji位按顺序取出,从左到右做合并操作
	a.如果前两个同色,则删去
	b.如果前两个异色,则变为另一个颜色(剩下的那一种颜色)
	c.特别的如果序列为空,则混合的结果为白色(W),如果只有一个,那么最后混合就是它
2.RY 选择一个子序列将所有的R变成Y,所有的Y变成R,B和空位置不变
3.RB 选择一个子序列将所有的R变成B,所有的B变成R,Y和空位置不变
4.YB 选择一个子序列将所有的B变成Y,所有的Y变成B,R和空位置不变
你需要根据操作的信息确定一种可能的原序列,保证n,k <= 1e3

思路:超级妙妙题,我们给每种颜色赋一个编号,R = 1,Y = 2,B = 3,W或者.为0
我们可以发现:mix操作本质是在求所有选中的数的异或和(二者相同就是抵消,二者不同就是第三者)
但是交换两种颜色的操作并不好表示,但是我们将每个数拆成两个bit,ai和bi后,就变得很简单了
RY:交换ai和bi;
RB:bi <- ai XOR bi
YB:ai <- ai XOR bi

那么我们可以维护当前的ai和bi与初识关系值,则每个mix操作都可以对两个bit分别列出一个方程
最终我们最多有2n个未知数,不超过2k个方程,用高斯消元+bitset就可以求出
时间复杂度为O(n*k*min{n,k}/w)
*/

int n,k,cnt;
bitset<N << 1> a[N << 1];
int t[N << 1],pos[N << 1],b[N << 1],x[N << 1];

int col(char c){
    if(c == 'W'){
        return 0;
    } else if(c == 'R'){
        return 1;
    } else if(c == 'Y'){
        return 2;
    } else {
        return 3;
    }
}

void solve(){
    cin >> n >> k;
    for(int i = 0;i < n;i++){
        t[2 * i] = 1;
        t[2 * i + 1] = 2;
    }
    for(int i = 0;i < k;i++){
        string op;
        cin >> op;
        int m;
        cin >> m;
        for(int j = 0;j < m;j++){
            cin >> pos[j];
            pos[j]--;
        }
        if(op == "mix"){
            char res;
            cin >> res;
            int c = col(res);
            for(int j = 0;j < m;j++){
                int p = pos[j];
                a[cnt][2 * p] = t[2 * p] & 1;
                a[cnt][2 * p + 1] = t[2 * p] >> 1;
            }
            b[cnt++] = c & 1;
            for(int j = 0;j < m;j++){
                int p = pos[j];
                a[cnt][2 * p] = t[2 * p + 1] & 1;
                a[cnt][2 * p + 1] = t[2 * p + 1] >> 1;
            }
            b[cnt++] = c >> 1;
        } else if(op == "RY"){
            for(int j = 0;j < m;j++){
                int p = pos[j];
                swap(t[2 * p],t[2 * p + 1]);
            }
        } else if(op == "RB"){
            for(int j = 0;j < m;j++){
                int p = pos[j];
                t[2 * p + 1] ^= t[2 * p];
            }
        } else {
            for(int j = 0;j < m;j++){
                int p = pos[j];
                t[2 * p] ^= t[2 * p + 1];
            }
        }
    }
    int r = 0;
    for(int i = 0;i < 2 * n && r < cnt;i++){
        for(int j = r;j < cnt;j++){
            if(a[j][i]){
                swap(a[j],a[r]);
                swap(b[j],b[r]);
                break;
            }
        }
        if(!a[r][i]){
            continue;
        }
        for(int j = 0;j < cnt;j++){
            if(j != r && a[j][i]){
                a[j] ^= a[r];
                b[j] ^= b[r];
            }
        }
        r++;
    }
    for(int i = r;i < cnt;i++){
        if(b[i]){
            cout << "NO\n";
            return;
        }
    }
    for(int i = 0;i < r;i++){
        int j = 0;
        while(!a[i][j]){
            j++;
        }
        x[j] = b[i];
        for(int k = j + 1;k < 2 * n;k++){
            if(a[i][k]){
                x[j] ^= x[k];
            }
        }
    }
    cout << "YES\n";
    for(int i = 0;i < n;i++){
        int c = x[2 * i] | x[2 * i + 1] << 1;
        cout << ".RYB"[c];
    }
    cout << "\n";
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