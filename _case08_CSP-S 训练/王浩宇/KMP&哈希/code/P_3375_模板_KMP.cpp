#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
const int N = 1e6 + 10;
/* S 模式串与 T 匹配串，一对多 */
string s, p;
int nxt[N];
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> s >> p;

    int n = s.size(), m = p.size();
    s = " " + s, p = " " + p;
    /* 构造回跳数组 nxt[j] */
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && p[i] != p[j + 1])
            j = nxt[j];
        if (p[i] == p[j + 1])
            ++j;
        nxt[i] = j;
    }
    /* 匹配过程，进可攻退可守，退而求其次！*/
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s[i] != p[j + 1])
            j = nxt[j];
        if (s[i] == p[j + 1])
            ++j;
        if (j == m)
            cout << i - m + 1 << endl;
    }
    for (int i = 1; i <= m; i++)
        cout << nxt[i] << " ";
    return 0;
}