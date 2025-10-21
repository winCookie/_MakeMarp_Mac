/* 100pts */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
const int N = 2e5 + 10;
ll a[N], n;
ll ans;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= 2 * n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + 2 * n);
    for (int i = 1, j = 2 * n; i < j; i++, j--)
        ans += (ll)a[i] * a[j];
    cout << ans << endl;
    return 0;
}