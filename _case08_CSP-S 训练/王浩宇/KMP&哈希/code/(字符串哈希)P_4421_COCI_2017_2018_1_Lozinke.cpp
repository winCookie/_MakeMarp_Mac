#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define endl "\n"
const int N = 20005;
unordered_map<ll, int> _hash, _hash2; // 整串的hash，串是否已出现
ll vis[N];                            // 记录子串 hash，用于避免重复计算贡献
string s[N];
int n;
ll get(string t, int l, int r) {
    ll _hashcode = 1;
    for (int i = l; i <= r; i++)
        _hashcode = _hashcode * 26 + (t[i] - 'a') + 1;
    return _hashcode;
}
void solve() {
    for (int i = 1; i <= n; i++)
        _hash[get(s[i], 0, s[i].size() - 1)]++;
}
ll check(string t) {
    ll ans = -1; /* 0～0 是空串肯定存在，则预-1 */
    int len = t.size(), cnt = 0;
    /* 暴力枚举子串 */
    for (int i = 0; i < len; i++)
        for (int j = i; j < len; j++) {
            /* 子串存在 && 子串没有计算过贡献 */
            ll _subhashcode = get(t, i, j);
            if (_hash[_subhashcode] && !_hash2[_subhashcode]) {
                ans += _hash[_subhashcode];
                _hash2[_subhashcode] = 1, vis[++cnt] = _subhashcode;
            }
        }
    /* 还原占位 */
    for (int i = 1; i <= cnt; i++)
        _hash2[vis[i]] = 0;
    return ans;
}
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    solve();
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += check(s[i]);
    cout << ans << endl;
    return 0;
}