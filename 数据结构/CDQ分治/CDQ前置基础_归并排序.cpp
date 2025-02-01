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
基础知识:
CDQ分治和离线二分
1.这两个算法有什么关系?
--没有太大的关系,就像莫队和分块一样,他们在底层的思想上是同源的,但是他们后面怎么用的
以及算法的底层的原理是完全不一样的
2.他们的作用?
--对于传统的二分类的数据结构题(比如树状数组和线段树,主席树,李超树等),只要不强制在线
那么它们就是几乎万能的替代品
CDQ分治是cdq发明的算法,他的前身是"分治求逆序对"
换句话来说,整个算法来自于"归并排序"的扩展,只是在归并的基础上多做了一些东西而已

分治求逆序对
分治求逆序对就是对于一对数组元素,如果他们的数组下标和值的大小关系相反,那么就是一个逆序对

复习归并排序:
归并排序的核心是合并的过程,将两个有序的数组a[i]和b[j]和并到一个有序数组c[k]
从左到右枚举a[i]和b[j],找到最小的值并放入c[k],重复上述重复上述的过程直到a[i]和b[j]有一个为空的时候
将另一个数组的剩下的元素放入c[k],为了保证排序的稳定性,前段首元素小于或者等于后段的首元素的时候(a[i] <= b[j])
而非小于(a[i] < b[j])的时候就要作为最小值放入c[k]
*/

//归并合并的代码
//merge过程就是把a[i]和b[j]中的元素升序放入到c[k]数组中
void merge(const int *a,int alen,const int *b,int blen,int *c){
    int i = 0,j = 0,k = 0;
    while(i < alen && j < blen){
        if(b[j] < a[i]){
            c[k] = b[j];
            j++;
        } else {
            c[k] = a[i];
            i++;
        }
        k++;
    }
    for(;i < alen;i++,k++) c[k] = a[i];
    for(;j < blen;j++,k++) c[k] = b[j];
}

//分治实现归并排序
//下面代码代表的区间分别是[l,r),[l,mid),[mid,r)
void merge_sort(int *a,int l,int r){
    //剩下一个元素本身就是排好序的,直接return
    if(r - l <= 1) return;
    int mid = (l + r) >> 1;
    merge_sort(a,l,mid);
    merge_sort(a,mid,r);
    int tmp[1024] = {};
    merge(a + l,mid - l,a + mid,r - mid,tmp + l);
    for(int i = l;i < r;i++) a[i] = tmp[i];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    return 0;
}