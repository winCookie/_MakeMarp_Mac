### P11562 【MX-X7-T3】[LSOT-3] 寄存器
#### ▍题意

  给定一棵 $n$ 个节点的树，每个节点初始值为 $0$。每次操作可以独立设置每条边的开关状态，然后选择一个节点通电。通电的节点会翻转值（$0$ 变 $1$，$1$ 变 $0$），并且通电会通过开启的边传播到相连的节点。问最少需要多少次通电操作可以使每个节点的值等于给定的 $a_i$。

  数据范围：$1 \le n \le 10^6$，$0 \le a_i \le 1$。

#### ▍分析

  每次操作相当于翻转一个连通子图（即一棵子树或一条路径）。问题转化为用最少的连通子图翻转操作，使得每个节点被翻转的次数奇偶性等于 $a_i$（即 $a_i=1$ 的节点被翻转奇数次，$a_i=0$ 的节点被翻转偶数次）。

  **关键观察**：在树结构中，最少操作次数与树上节点值变化的频率有关。具体地，考虑一条路径，如果沿路径节点值频繁变化（即相邻节点值不同），则需要更多操作来调整这些变化。因此，我们需要找到树上一条路径，使得沿路径节点值变化的次数最大。记这个最大变化次数为 $d$，则最少操作数为 $\lfloor (d+1)/2 \rfloor$。

  **推导过程**：
  - 对于链情况（子任务2），问题简化为对数组进行区间翻转。观察发现，连续相同值的段可以合并，操作次数取决于值变化的次数。例如，数组 $[1,0,1,0,1]$ 需要大约 $\lceil \text{变化次数}/2 \rceil$ 次操作。
  - 对于树情况，通过类似树的直径的方法，找到最长值变化路径（即路径上相邻节点值不同的边数最多）。两次 DFS 用于找到这条路径：
    1. 第一次 DFS 从任意节点开始，计算到每个节点的路径上值变化的次数，并记录变化次数最大的节点 $maxp$。
    2. 第二次 DFS 从 $maxp$ 开始，重新计算值变化次数，得到最大值 $d$。
  - 答案即为 $\lfloor (d+1)/2 \rfloor$，因为每次操作最多覆盖路径上连续两个值变化段，因此需要至少 $\lfloor (d+1)/2 \rfloor$ 次操作。

  时间复杂度：两次 DFS 遍历整棵树，时间复杂度为 $O(n)$。

#### ▍参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int a[N], n;
vector<int> g[N];
int maxp, maxd;

void dfs(int u, int fa, int deep) {
    if (fa != 0 && a[u] != a[fa]) deep++;
    if (a[u] == 1 && deep > maxd) {
        maxd = deep;
        maxp = u;
    }
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u, deep);
    }
}

int main() {
    cin >> n;
    bool all_zero = true;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) all_zero = false;
    }
    if (all_zero) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    maxd = 0;
    dfs(1, 0, 0);
    maxd = 0;
    dfs(maxp, 0, 0);
    cout << (maxd + 1) / 2 << endl;
    return 0;
}
```