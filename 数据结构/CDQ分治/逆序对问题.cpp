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
逆序对问题:
给出一个数组,求解(i < j && ai > aj)的数对的个数
那么我们使用归并思想,在归并排序期间每次统计右侧比左侧大的元素
此时假设左侧的指针指向i,右侧的指针指向j,那么i元素对应的逆序对数量就是i - m
当然逆序对也可以用树状数组解决,但是这里只给出归并的代码,因为是CDQ分钟的前置知识
这个分支的本质已经是CDQ分治了
*/


int n,m;
//归并排序求逆序对aa
ll merge_sort(int *nums,int l,int r){
    if(r - l <= 1) return 0;
    ll res = 0;
    int m = (l + r) >> 1;
    res += merge_sort(nums,l,m);
    res += merge_sort(nums,m,r);
    std::vector<int> tmp(r - l);
    int i = l,j = m,k = 0;
    while(i < m && j < r){
        //当出现有左侧的元素比右侧的大的时候,此时更新res
        //此时说明了i后面(包含i)一直到m前面的所有元素都比j位置大
        //那么这些数对都是逆序对
        if(nums[j] < nums[i]){
            tmp[k] = nums[j++];
            res += m - i;
        } else {
            tmp[k] = nums[i++];
        }
        k++;
    }
    for(;i < m;i++,k++) tmp[k] = nums[i];
    for(;j < r;j++,k++) tmp[k] = nums[j];
    for(i = l,k = 0;i < r;i++,k++){
        nums[i] = tmp[k];
    }
    return res;
} 

void solve(){
    cin >> n >> m;
    int nums[n];
    for(int i = 0;i < n;i++) cin >> nums[i];
    cout << merge_sort(nums,0,n) << '\n';
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