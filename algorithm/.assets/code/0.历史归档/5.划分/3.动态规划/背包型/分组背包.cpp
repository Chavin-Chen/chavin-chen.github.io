#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>

using namespace std;
/**
 * https://www.nowcoder.com/practice/f9c6f980eeec43ef85be20755ddbeaf4
 */
int main() {
    int V, n;
    cin >> V >> n;
    vector<vector<tuple<int, int, int>>> input(n + 1, vector<tuple<int, int, int>>());
    vector<vector<pair<int, int>>> arr;

    for (int i = 1; i <= n; i++) {
        tuple<int, int, int> t;
        cin >> get<0>(t) >> get<1>(t) >> get<2>(t);
        if (get<2>(t) == 0) { // 主件放在位置0
            input[i].insert(begin(input[i]), t);
        } else {
            int j = get<2>(t);
            input[j].push_back(t);
        }
    }

    for (int i = 1; i <= n; i++) { // 分组
        if (input[i].empty()) continue;
        vector<pair<int, int>> vec;
        pair<int, int> key(get<0>(input[i][0]), get<0>(input[i][0]) * get<1>(input[i][0]));
        vec.push_back(key);
        if (input[i].size() > 1) {
            pair<int, int> add1(key.first + get<0>(input[i][1]),
                                get<0>(input[i][1]) * get<1>(input[i][1]) + key.second);
            vec.push_back(add1);
            if (input[i].size() > 2) {
                pair<int, int> add2(key.first + get<0>(input[i][2]),
                                    get<0>(input[i][2]) * get<1>(input[i][2]) + key.second);
                vec.push_back(add2);
                vec.emplace_back(add1.first + add2.first - key.first, add1.second + add2.second - key.second);
            }
        }
        arr.push_back(vec);
    }

    vector<int> dp(V + 1, 0);
    for (auto &k : arr) { // 分组背包
        for (int j = V; j >= 0; j--) {
            for (auto it = begin(k); it != end(k); it++) {
                if (j >= it->first) {
                    dp[j] = max(dp[j], dp[j - it->first] + it->second);
                }
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}