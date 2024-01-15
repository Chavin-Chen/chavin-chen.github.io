# LeetCode记录


## 跳跃游戏
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个位置。

示例 1:
输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。

示例 2:
输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。

链接：https://leetcode-cn.com/problems/jump-game

**贪心**
每次跳到`i`就取当前可达的最远距离`maxD`和`i + dis[i]`最大值（补充跳跃距离）。 

```cpp
class Solution {
public:
    bool canJump(vector<int> &dis) {
        if (dis.size() <= 1) {
            return true;
        }
        int maxD = dis[0], i;
        for (i = 1; i <= maxD; i++) {
            maxD = max(maxD, i + dis[i]);
            if (maxD >= dis.size() - 1) {
                return true;
            }
        }
        return false;
    }
};
```





## 每日温度
请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。
例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。
提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。

链接：https://leetcode-cn.com/problems/daily-temperatures

**逆序搜索**
从最后一个元素往前搜索，用`next[t]`表示温度`t`当前最早出现的位置，`ans[i] = min(nextI, next[t])` 其中 `t > T[i]`。
O(nm)

**逆序搜索优化**
比较`T[i]`和`T[i+1]`:
- 若`T[i] < T[i+1]` : ans[i] = 1;
- 若`T[i] >= T[i+1]`:
	- 若 `ans[i+1] == 0`: 说明`i+1`后无更大元素，则 `ans[i] = 0`
	- 否则继续比较 `T[i]` 和 `T[i + ans[i+1]]`

**单调栈**
令元素栈单调：栈底元素 >= 栈顶元素。
顺序遍历列表：
- 若栈空或当前元素`T[i]`小于等于栈顶元素，则`i`直接入栈。
- 若`T[i]`大于栈顶元素，则`ans[i] = i-top`，出栈继续比较，直到满足入栈条件。

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        int n = T.size();
        vector<int> ans(n, 0);
        for (int i = n - 2, j; i >= 0; i--) {
            j = i + 1;
            while (j < n) {
                if (T[i] < T[j]) {
                    // 若 T[i] < T[i+1]; ans[i] = 1;
                    ans[i] = j - i;
                    break;
                } else if (ans[j] == 0) {
                    // 若 ans[i+1] == 0
                    ans[i] = 0;
                    break;
                } else {
                    // next high
                    j += ans[j];
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        vector<int> ans(T.size());
        vector<int> next(101, INT_MAX);

        for (int i = T.size() - 1, minNext; i >= 0; --i) {
            // 下一个更高温度的下标
            minNext = INT_MAX;
            for (int t = T[i] + 1; t <= 100; ++t) {
                minNext = min(minNext, next[t]);
            }
            ans[i] = minNext == INT_MAX ? 0 : minNext - i;
            // 不断刷新温度 T[i] 的首次出现下标
            next[T[i]] = i;
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        vector<int> ans(T.size(), 0);
        // 递减栈：栈底>=栈顶
        stack<int> stk;
        for (int i = 0; i < T.size(); ++i) {
            // 保持单调性
            while (!stk.empty() && T[i] > T[stk.top()]) {
                auto t = stk.top();
                stk.pop();
                ans[t] = i - t;
            }
            stk.push(i);
        }
        return ans;
    }
};
```
