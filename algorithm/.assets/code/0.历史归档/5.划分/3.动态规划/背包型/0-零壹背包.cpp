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
        for (int j = V; j >= arr[i].first; j--) { // 逆序遍历 物品仅取一次
            dp[j] = max(dp[j], dp[j - arr[i].first] + arr[i].second);
        }
    }
    cout << dp[V] << endl;
    return 0;
}
/**
Input:
7 15
4 6
3 9
2 8
7 7
12 18
6 11
5 7
Output:
34

 */