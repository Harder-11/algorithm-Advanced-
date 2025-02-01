#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 200005;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int hs = 1331;
const double PI = acos(-1);
#define ls u << 1
#define rs u << 1 | 1
#define mid ((l + r) >> 1)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;

/*
首先复习单调队列优化滑动窗口问题,给定一个定长的窗口,求窗口内的最大和最小值
那么很显然,加上当前窗口有一个值3,如果后面加入的元素比3更大,那么3永远都不可能成为窗口内的最大值了
那就把3去掉,如果加入的比3小,那么都保留下来,那么用一个deque保存其中的元素
这样就维护出了一个单调递减的队列

那么在求最长上升子序列问题中f[i] = max(f[j] + 1),j < i且a[j] < a[i]
比如是 1 9 7 8 4 3 5 8
当求了f[3]之后,还有必要考虑某个数接在9后面吗?
7的存在使得9没有机会了,保留1,7即可(因为7比9小,给后面限制更小)
到4的时候,4和7往前的最长上升子序列长度是一样的,7也没机会了,让4代替7的位置
保留1 4 8(分别对于f值的123,这里的4是代替7之后所以在容器中是在8之前)
那么用一个容器stack或者queue来维护留下来的还有机会往后面加数的数字
每次二分的在容器里面找到第一个大于等于a[i]的位置,更新f[i]的值,并且把a[i]放到这个位置
最后答案就是容器当中元素的个数
时间复杂度O(nlogn)

*/

int n,a[N];
//用vector代替队列
vector<int> q;

void solve(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        if(lower_bound(q.begin(),q.end(),a[i]) == q.end()){
            q.push_back(a[i]);
        } else {
            int x = lower_bound(q.begin(),q.end(),a[i]) - q.begin();
            q[x] = a[i];
        }
    }
    cout << q.size() << '\n';
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