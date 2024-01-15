#include <iostream>
#include <vector>
#include <map>

using namespace std;

int dfs(int cnt, vector<char> &stack, const string &s) {
    if (s.empty()) return cnt + (int) stack.size();
    char c = s[0];
    if (c == '(' || c == '[' || c == '{') { // 左括号入栈
        stack.push_back(c);
        return dfs(cnt, stack, s.substr(1, s.size() - 1));
    }
    // 右括号 且 空栈+1
    if (stack.empty()) {
        return dfs(cnt + 1, stack, s.substr(1, s.size() - 1));
    }
    // 右括号且栈顶匹配，优先匹配
    if ((c == ')' && stack.back() == '(') || (c == ']' && stack.back() == '[') || (c == '}' && stack.back() == '{')) {
        stack.pop_back();
        return dfs(cnt, stack, s.substr(1, s.size() - 1));
    }
    // 右括号不匹配，考虑1: 匹配栈顶
    vector<char> stk(begin(stack), end(stack));
    stk.pop_back();
    int a = dfs(cnt + 1, stk, s);
    stk.clear();

    // 右括号不匹配，考虑2: 匹配当前括号
    int b = dfs(cnt + 1, stack, s.substr(1, s.size() - 1));
    return a < b ? a : b;
}

int find(const string &s, int j, int i, char c) {
    int k;
    for (k = j - 1; k >= i; --k)
        if (s[k] == c) break;
    return k < i ? -1 : k;
}

int dp[3005][3005];

int solve(const string &s) {
    map<char, char> m{{')', '('},
                      {']', '['},
                      {'}', '{'}};
    int n = s.size();
    for (int i = 0; i < n; i++)dp[i][i] = 1;
    int x, minx;
    for (int k = 1; k < n; k++) {
        for (int i = 0, j = i + k; j < n; i++) {
            j = i + k;
            if (s[j] == '(' || s[j] == '[' || s[j] == '{') { // 左括号，并不能对[i,j-1]有所增益
                dp[i][j] = dp[i][j - 1] + 1;
            } else {
                minx = INT_MAX;
                x = j;
                do {
                    // 从[i,j-1]中找一个能和s[j]匹配的左括号，用它将区间分为两段
                    x = find(s, x, i, m[s[j]]);
                    if (x < 0) minx = min(minx, dp[i][j - 1] + 1);
                    else {
                        if (x - 1 >= i && x + 1 <= j - 1) minx = min(minx, dp[i][x - 1] + dp[x + 1][j - 1]);
                        else if (x - 1 < i && x + 1 <= j - 1) minx = min(minx, dp[x + 1][j - 1]);
                        else if (x - 1 >= i && x + 1 > j - 1) minx = min(minx, dp[i][x - 1]);
                        else minx = min(minx, 0);
                    }

                } while (x >= i);
                dp[i][j] = minx;
            }
        }
    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << dp[i][j] << " ";
//        }
//        cout << endl;
//    }
    return dp[0][n - 1];
}

int main() {
    string s = "1234";
    int T;
    cin >> T;
    vector<char> stack;
    while (T--) {
        cin >> s;
        cout << dfs(0, stack, s) << endl;
        stack.clear();
        cout << solve(s) << endl;
    }
    return 0;
}

/*
https://blog.csdn.net/qq_55990690/article/details/125603293
https://www.pudn.com/news/628f833bbf399b7f351e7905.html
输入只包含[()]的字符串(最大长度3000)，求最少要添加多少括号使得最终所有括号满足无嵌套且成对出现
5
[[[
[)(]
([)]
([)]([)][)(][)(]([)][)(][([)][)[)[]([)][)(][)[[)(]([)]
([)]([)][)(][)(]([)][)(][([)][)[)[](((]]]][][][]((((]](]]]])))]([)][)(][)[[)(]([)][)(]([)][)(][([)][)[)[)[]([)][)(][)[[)(]([)][)(]([

3 2 2 20 54
 */
