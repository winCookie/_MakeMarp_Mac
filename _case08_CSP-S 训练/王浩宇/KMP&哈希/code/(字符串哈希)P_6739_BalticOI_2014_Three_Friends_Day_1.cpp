#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define endl "\n"
const int N = 2e6 + 10;
ull base = 13331; // 哈希基数
int n, mid, len1, len2, ans;
string s, a, b, c, d;
ull hsh[N], pre[N]; // hsh: 前缀哈希数组, pre: 基数幂次数组

// 获取区间[l, r]的哈希值
ull getHash(int l, int r) { return hsh[r] - hsh[l - 1] * pre[r - l + 1]; }

// 获取区间[l, r]中删除位置k后的哈希值
ull getSubHash(int l, int r, int k) {
    // 将[l, k-1]和[k+1, r]两段拼接起来计算哈希
    return getHash(l, k - 1) * pre[r - k] + getHash(k + 1, r);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> s;

    // 检查字符串长度是否为奇数，偶数长度不可能通过删除一个字符形成回文
    if (!(n % 2))
        puts("NOT POSSIBLE"), exit(0);

    s = " " + s;                    // 让字符串下标从1开始
    pre[0] = 1, mid = (n + 1) >> 1; // mid是中间位置

    // 预处理哈希数组和基数幂次数组
    for (int i = 1; i <= n; i++) {
        hsh[i] = hsh[i - 1] * base + (s[i] - 'A' + 1);
        pre[i] = pre[i - 1] * base;
    }

    // 情况1：删除字符在左半部分
    len1 = getHash(mid + 1, n);     // 右半部分的哈希值
    a = s.substr(mid + 1, n - mid); // 右半部分的字符串

    // 遍历左半部分的每个位置，尝试删除该字符
    for (int i = 1; i <= mid; i++) {
        // 计算删除位置i后左半部分的哈希值
        len2 = getSubHash(1, mid, i);
        if (len1 == len2) { // 如果左右两半哈希值相等
            ans++;
            c = a; // 记录结果字符串
            break; // 找到一个解就退出
        }
    }

    // 情况2：删除字符在右半部分
    len2 = getHash(1, mid - 1); // 左半部分(不含中间字符)的哈希值
    b = s.substr(1, mid - 1);   // 左半部分的字符串

    // 遍历右半部分的每个位置，尝试删除该字符
    for (int i = mid; i <= n; i++) {
        // 计算删除位置i后右半部分的哈希值
        len1 = getSubHash(mid, n, i);
        if (len1 == len2) { // 如果左右两半哈希值相等
            ans++;
            d = b; // 记录结果字符串
            break; // 找到一个解就退出
        }
    }

    // 输出结果
    if (ans == 0)
        puts("NOT POSSIBLE"); // 无解
    else if (ans == 1 || c == d)
        cout << (c.size() ? c : d) << endl; // 唯一解或两个解相同
    else
        puts("NOT UNIQUE"); // 多个不同解

    return 0;
}