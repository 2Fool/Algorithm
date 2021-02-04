#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long ll;
typedef pair<ll, ll> pll;
const int N = 300010;
const ll INF = 2e18;

/*
本质上就是在问不同后缀的最长公共前缀
先求出sa[]和height[]

然后从大到小枚举r，用DSU合并有lcp>=r的后缀，然后更新数量和最大值
从大到小枚举的原因是r较大结果一定在r较小的结果里面包含，先计算大的
*/

int n, m;
char s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int w[N], p[N], sz[N];
ll max1[N], max2[N], min1[N], min2[N];
vector<int> hs[N];
pll ans[N];

void get_sa() {
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++ )
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        if (num == n) break;
        m = num;
    }
}

void get_height() {
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++ ) {
        if (rk[i] == 1) continue;
        if (k) k -- ;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
        height[rk[i]] = k;
    }
}

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

ll get(int x) { //计算C(x,2)组合数
    return x * (x - 1ll) / 2;
}

pll calc(int r) { //对于每个r求出答案
    static ll cnt = 0, maxv = -INF; //对数和最大值

    for (auto x : hs[r]) {
        int a = find(x - 1), b = find(x); //sa[i]和sa[i-1]合并到一个DSU
        cnt -= get(sz[a]) + get(sz[b]); //先减去2个DSU，然后重新算一遍加上
        p[a] = b;
        sz[b] += sz[a]; //将a合并到b里面
        cnt += get(sz[b]);

        //更新最大次大 最小和次小
        if (max1[a] >= max1[b]) {
            max2[b] = max(max1[b], max2[a]);
            max1[b] = max1[a];
        }
        else if (max1[a] > max2[b]) max2[b] = max1[a];

        if (min1[a] <= min1[b]) {
            min2[b] = min(min1[b], min2[a]);
            min1[b] = min1[a];
        }
        else if (min1[a] < min2[b]) min2[b] = min1[a];
        maxv = max(maxv, max(max1[b] * max2[b], min1[b] * min2[b]));
    }
    if (maxv == -INF) return {cnt, 0};
    return {cnt, maxv};
}

int main() {
    scanf("%d", &n), m = 122; //m是小写z，ASCII最大122
    scanf("%s", s + 1); //下标从1开始
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);

    get_sa();
    get_height();
    //将后缀按照最长公共前缀分类
    for (int i = 2; i <= n; i++) hs[height[i]].push_back(i);

    for (int i = 1; i <= n; i++) {
        p[i] = i, sz[i] = 1;
        max1[i] = min1[i] = w[sa[i]]; //最大值和最小值
        max2[i] = -INF, min2[i] = INF; //次大和次小
    }

    for (int i = n - 1; i >= 0; i --)ans[i] = calc(i); //从大到小枚举r 进行合并和计算
    for (int i = 0; i < n; i++) printf("%lld %lld\n", ans[i].x, ans[i].y);

    return 0;
}