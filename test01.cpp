#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> scores(n * m);
    for (int i = 0; i < n * m; i++) {
        cin >> scores[i];
    }

    // 记录小R的成绩
    int r_score = scores[0];

    // 从高到低排序
    sort(scores.begin(), scores.end(), greater<int>());

    // 找到小R的排名（从1开始）
    int rank = 0;
    for (int i = 0; i < n * m; i++) {
        if (scores[i] == r_score) {
            rank = i + 1;
            break;
        }
    }

    // 根据排名计算座位
    int col = (rank - 1) / n + 1; // 列号
    int offset = (rank - 1) % n;  // 在列中的偏移

    int row;
    if (col % 2 == 1) { // 奇数列：从上到下
        row = offset + 1;
    } else { // 偶数列：从下到上
        row = n - offset;
    }

    cout << row << " " << col << endl;
    return 0;
}