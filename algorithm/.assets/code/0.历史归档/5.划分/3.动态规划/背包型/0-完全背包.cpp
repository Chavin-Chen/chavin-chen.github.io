#include<iostream>
#include<vector>

using namespace std;

int main() {
    int V, N;
    cin >> N >> V;
    vector<pair<int, int>> arr(N + 1);
    for (int i = 1; i <= N; i++) { // input ci wi
        cin >> arr[i].first >> arr[i].second;
    }
    vector<int> dp(V + 1, 0); // dp[1..V]为0，不要求恰好装满
    for (int i = 1; i <= N; i++) {
        for (int j = arr[i].first; j <= V; j++) { // 顺序遍历 物品可取多次(V/C[i])
            dp[j] = max(dp[j], dp[j - arr[i].first] + arr[i].second);
        }
    }
    cout << dp[V] << endl;
    return 0;
}
/*
Input:
7 15
5 45
8 23
11 22
7 15
6 43
21 97
15 47
Output:
135

*/