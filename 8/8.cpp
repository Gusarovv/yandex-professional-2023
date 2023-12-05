#include <bits/stdc++.h>

#define int long long

using namespace std;

const int M7 = 1'000'000'007;

vector<vector<int>> matmul(const vector<vector<int>> &l, const vector<vector<int>> &r) {
    int n = l.size();
    int m = r.size();
    assert(m == r[0].size() && m == l[0].size());
    
    vector<vector<int>> result(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                result[i][j] += (l[i][k] * r[k][j]) % M7;
                result[i][j] %= M7;
            }
        }
    }
    return result;
}

vector<vector<int>> binpow(vector<vector<int>> mtx, int k) {
    vector<vector<int>> result(mtx.size(), vector<int>(mtx[0].size()));
    for (int i = 0; i < mtx.size(); ++i) {
        result[i][i] = 1;
    }
    while (k) {
        if (k & 1) {
            result = matmul(mtx, result);
        }
        mtx = matmul(mtx, mtx);
        k >>= 1;
    }
    return result;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> start(1, vector<int>(n));
    vector<vector<int>> dp(n, vector<int>(n, 1));
    for (int i = 0; i < n; ++i) {
        cin >> start[0][i];
        for (int j = 0; j <= i; ++j) {
            dp[j][i] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int to = i + 1; to < n; ++to) {
            for (int j = 0; j < n; ++j) {
                dp[j][to] += dp[j][i];
            }
        }
    }
    
    dp = binpow(dp, k);
    start = matmul(start, dp);
    for (auto &i: start[0]) {
        cout << i << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) 
        solve();
    return 0;
}
