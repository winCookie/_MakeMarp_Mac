### P4877 [USACO14FEB] Cow Decathlon G
▍题意
  有 $N$ 头奶牛和 $N$ 项比赛，每头奶牛必须参加一项比赛，每项比赛也必须有一头奶牛参加。奶牛 $i$ 参加比赛 $j$ 会得到分数 $S_{i,j}$。此外，有 $B$ 种奖励分，第 $i$ 种奖励会在第 $K_i$ 项比赛结束时检查，如果当时总分大于或等于 $P_i$，则立即获得额外 $A_i$ 分。奖励分检查顺序可以自由安排。求能获得的最大总得分。

  数据范围：$1 \le N, B \le 20$，$1 \le K_i \le N$，$1 \le P_i \le 4 \times 10^4$，$1 \le A_i \le 10^3$，$1 \le S_{i,j} \le 10^3$。

▍分析
  由于 $N$ 较小，可以使用状态压缩动态规划。用二进制位掩码表示已分配奶牛的集合，状态 $f[mask]$ 表示分配奶牛集合 $mask$ 后获得的最大分数。状态转移时，考虑下一个比赛（即当前已完成比赛数量 $k = popcount(mask)$）和未分配的奶牛，更新新状态。同时，在每个状态检查奖励分：如果 $k$ 等于某个奖励的 $K_i$ 且当前分数 $f[mask] \ge P_i$，则加上奖励分 $A_i$。

  **算法步骤**：
  1. 读入 $N$ 和 $B$，存储奖励分。
  2. 读入得分矩阵 $S$。
  3. 初始化 DP 数组 $f$，大小为 $2^N$，$f[0] = 0$，其余为负无穷。
  4. 预处理每个状态 $mask$ 的 $popcount$（已完成比赛数量）。
  5. 遍历所有状态 $mask$：
     - 若 $f[mask]$ 无效则跳过。
     - 计算当前已完成比赛数量 $k = popcount(mask)$。
     - 应用奖励分：遍历所有奖励，若 $K_i = k$ 且 $f[mask] \ge P_i$，则 $f[mask] += A_i$。
     - 若 $k = N$，则跳过转移（已完成）。
     - 否则，对于每个未分配奶牛 $j$（即 $mask$ 中位 $j$ 为 0），计算新状态 $new\_mask = mask | (1 << j)$，新得分为 $f[mask] + S[j][k+1]$，更新 $f[new\_mask]$。
  6. 输出 $f[(1<<N)-1]$。

  时间复杂度：$O(2^N \cdot N \cdot B)$，在 $N \le 20$ 时可行。

▍参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, B;
    cin >> N >> B;
    vector<tuple<int, int, int>> bonuses(B);
    for (int i = 0; i < B; i++) {
        int k, p, a;
        cin >> k >> p >> a;
        bonuses[i] = {k, p, a};
    }
    vector<vector<int>> S(N, vector<int>(N + 1));
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> S[i][j];
        }
    }

    vector<int> f(1 << N, -1e9);
    f[0] = 0;
    vector<int> popcount(1 << N, 0);
    for (int mask = 0; mask < (1 << N); mask++) {
        popcount[mask] = __builtin_popcount(mask);
    }

    for (int mask = 0; mask < (1 << N); mask++) {
        if (f[mask] < 0) continue;
        int k = popcount[mask];
        int current_score = f[mask];
        for (auto &bonus : bonuses) {
            int k_i, p_i, a_i;
            tie(k_i, p_i, a_i) = bonus;
            if (k_i == k && current_score >= p_i) {
                current_score += a_i;
            }
        }
        if (k == N) {
            f[mask] = max(f[mask], current_score);
            continue;
        }
        for (int j = 0; j < N; j++) {
            if (mask & (1 << j)) continue;
            int new_mask = mask | (1 << j);
            int new_score = current_score + S[j][k + 1];
            if (new_score > f[new_mask]) {
                f[new_mask] = new_score;
            }
        }
    }
    cout << f[(1 << N) - 1] << endl;
    return 0;
}
```