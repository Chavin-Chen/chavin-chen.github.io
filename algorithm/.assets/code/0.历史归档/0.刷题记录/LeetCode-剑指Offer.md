# LeetCode-剑指Offer

## 调整数组顺序使奇数位于偶数前面
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

示例：
输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。
 
链接：https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof

**首尾指针交换**
建立首尾指针，若发现偶数在奇数前则交换。
剥离出判断逻辑，可拓展成任意交换条件

```cpp
class Solution {
public:
    vector<int> exchange(vector<int> &arr) {
        int i = 0, j = arr.size() - 1, tmp, status;
        while (i < j) {
            status = state(arr[i], arr[j]);
            if (3 == status) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            if ((status & 1) == 0) {
                ++i;
            }
            if ((status & 2) == 0) {
                --j;
            }
        }
        return arr;
    }

    unsigned state(int a, int b) {
        unsigned res = 0;
        // 首指针为偶数则标记1位
        if ((a & 1) == 0) {
            res = (res | 1);
        }
        // 尾指针为奇数则标记2位
        if ((b & 1) == 1) {
            res = (res | 2);
        }
        return res;
    }
};
```


## 数值判断
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"-1E-16"、"0123"都表示数值，但"12e"、"1a3.14"、"1.2.3"、"+-5"及"12e+5.4"都不是。

链接：https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof

**分区判断**
以后`-12.23E-45`为例，可以把数值描述成`[A][.B][e|E C]`。
其中：
- A和C可以带符号的，B不能有符号
- B和C部分是可选的，A和B部分是可以只有一个的。

先去掉两端空白，从左向右读取，读到`.`再判断B，读到`e|E`再判断C。

```cpp
class Solution {
public: // [(+-)A][.B][e|E(+-)C]
    bool isNumber(string s) {
        const char *p = s.c_str();
        while (*p == ' ') ++p;
        // 先检查整数部分
        bool res = scanSign(p);
        // 如果有小数就检查小数部分
        if (*p == '.') {
            ++p;
            res = scanUnSign(p) || res;
        }
        // 如果有指数就检查指数部分
        if (*p == 'e' || *p == 'E') {
            ++p;
            res = res && scanSign(p);
        }
        while (*p == ' ') ++p;

        return res && (*p == 0);
    }

    static bool scanSign(const char *&s) {
        if (*s == '+' || *s == '-') {
            ++s;
        }
        return scanUnSign(s);
    }

    static bool scanUnSign(const char *&s) {
        const char *p = s;
        while (*s >= '0' && *s <= '9') {
            ++s;
        }
        return p != s;
    }
};
```

## 正则匹配
请实现一个函数用来匹配包含'. '和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。

链接：https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof

**回溯**
模式串指针：`i`、`j`指向两个相邻的元素。
主串指针：`k`当前匹配位置。

- 若`k`没走到主串结束：
    - `p[i]`不能匹配`s[k]`:
        - `p[j]=='*'`: 可以考虑`*==0`模式串右移两位舍弃`p[i]`
        - `p[j]!='*'`匹配失败
    - `p[i]`可以匹配`s[k]`:
        - `p[j]=='*'`: 
            - 用`p[i]*`：主串移位
            - 不用`p[i]*`：模式串移2位
        - `p[j]!='*'`双串都移位
- 若主串已经结束：
    - 若`p[j]=='*'`则可以尝试`*==0`模式串右移两位舍弃`p[i]`
    - 返回匹配失败

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return dfs(s, p, 0, 1, 0);
    }

    bool dfs(string &s, string &p, int i, int j, int k) {
        if (i >= p.size()) {
            return k >= s.size();
        }
        if (k < s.size()) {
            // 如果对应字符不匹配，就看j是不是*
            // j不是*号则匹配失败
            if (p[i] != '.' && p[i] != s[k]) {
                if (j < p.size() && p[j] == '*') {
                    // p右移动两位，s不动
                    return dfs(s, p, i + 2, j + 2, k);
                }
                // 不匹配又没有*直接挂了
                return false;
            }
            // 若对应字符匹配上，后面又没有*，都右移动
            if (j >= p.size() || p[j] != '*') {
                return dfs(s, p, i + 1, j + 1, k + 1);
            }
            // 若对应字符匹配上且后面又没有*，则*: 0 或 + (懒惰）
            return dfs(s, p, i + 2, j + 2, k) || dfs(s, p, i, j, k + 1);
        }

        // :s已经结束
        // 如果后面又不是*，则直接返回失败
        if (j >= p.size() || p[j] != '*') {
            return false;
        }
        // 如果p[j]=* 则可以挣扎一下*:0
        return dfs(s, p, i + 2, j + 2, k);
    }
};
```

**动态规划**
令`dp[i][j]`表示主串`[0,i)`和模式串`[0,j)`是否匹配：
- 可分解：
    - 若`p[j-1] != '*'`:
        - 两串最后一个元素匹配：`dp[i][j] = dp[i-1][j-1]`
        - 普通字符还不匹配：`dp[i][j] = false`
    - 若`p[j-1] == '*'`
        - 不用*: `dp[i][j] = dp[i][j] || dp[i][j-2]`;
        - 若`p[j-2]==s[i-1]`则可选择用*: `dp[i][j] = dp[i][j] || dp[i-1][j]`;
- 能组合: 当前是否匹配取决于 子问题的结果 加 当前末尾字符是否匹配。
- 有重叠: 对于*用或不用产生回溯有重复路径。

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        bool dp[m + 1][n + 1];
        memset(dp, 0, sizeof(bool) * (m + 1) * (n + 1));
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (j == 0) {
                    // 模式串为空，主串也为空情况下可以匹配
                    dp[i][j] = (i == 0);
                    continue;
                }
                // 模式串最后一个字符不是*
                if (p[j - 1] != '*') {
                    // 若两串最后一个字符可以匹配
                    if (i > 0 && (p[j - 1] == '.' || p[j - 1] == s[i - 1])) {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    continue;
                }
                // 模式串最后一个字符是*
                if (j >= 2) {
                    // 舍弃模式串最后一个普通字符p[j-2]
                    dp[i][j] = dp[i][j] || dp[i][j - 2];
                    // 若模式串最后一个普通字符可以匹配,则主串移位
                    if (i >= 1 && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};
```




## 删除链表结点
1. 给定一个头指针`Node *head` 和待删除结点指针`Node *p`，要求`O(1)`时间删除结点。
2. 在有序链表中，删除重复结点。

对于单向链表，删除结点是否一定需要知道前驱结点指针？
答：不一定！
- 对于非尾结点（可以用后继结点覆盖当前结点）:`p->val = p->next->val; p->next = p->next->next`
- 对于尾结点，则需要将前驱结点的`next`指针置为空。


## 打印从1到最大的n位数
输入正整数 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

示例 :
输入: n = 1
输出: [1,2,3,4,5,6,7,8,9]

链接：https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/

**大数加法**
可以用一个`char`表示两个10进制位，用大数加法累加访问1~9..9（当产生溢出的时候达到最大值）。

**排列**
n个0~9的升序排列。

```cpp
class Solution {
public:
    void printNumbers(int n) {
        if (n <= 0) {
            return;
        }
        char *s = new char[n];
        dfs(n, 0, s);
    }

    void dfs(int n, int i, char *s) {
        if (i == n) {
            int j = 0;
            while (j < n && s[j] == '0') {
                ++j;
            }
            if (j == n) {
                return;
            }
            while (j < n) {
                cout << s[j++];
            }
            cout << endl;
            return;
        }
        for (char j = '0'; j <= '9'; j++) {
            s[i] = j;
            dfs(n, i + 1, s);
        }
    }
};
```


## 数值的整数次方
实现函数double Power(double base, int exponent)，求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。

链接：https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof


**高质量代码**
- 规范：模块划分合理，排版命名清晰
- 完整：功能用例、边界用例、负面用例
- 鲁棒：防御性编程、关注 网络/文件/延时任务上下文状态 等问题。


对于`x^y`关注底数和指数分别为: 正数、0、负数 的情况。同时用快速幂求值。

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        char sign = x < 0 && ((abs(n) & 1) == 1) ? -1 : 1;
        if (abs(x) < 1E-6) {
            return 0;
        }
        if (n == 0) {
            return 1;
        }
        double ans = dfs(abs(x), abs(n)) * sign;

        return n < 0 ? 1.0 / ans : ans;
    }

    double dfs(double x, unsigned int y) {
        if (y == 0) {
            return 1;
        }
        double ans = dfs(x, y >> 1);
        if (y & 1) {
            return ans * ans * x;
        }
        return ans * ans;
    }
};
```



## 整数二进制中1的个数
**遍历位统计**
注意右移动的话对于负数统计会有问题，所以:
1. 方式一：选择左移和`0x80000000`做与运算。
2. 方式二：或者用一个`mask=1`值不断左移和n做与运算。
上述方式固定循环32次。

还可以通过不断进行 `n & n-1`运算，循环的次数就是1的个数。

**二路分治**
n中1的个数=n高位区1的个数 + 低位区1的个数。

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n) {
            if (n & 0x80000000) {
                cnt++;
            }
            n = n << 1;
        }
        return cnt;
    }
};

class Solution {
public:
    int hammingWeight(uint32_t n) {
        unsigned char cnt = 0;
        while (n) {
            ++cnt;
            n = n & (n - 1);
        }
        return cnt;
    }
};

class Solution {
public:
    int hammingWeight(uint32_t n) {
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
        n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
        n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
        n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
        return n;
    }
};

```

## 剪绳子II（贪心）
在分解成子问题后，每一步的最优选择最终可以确保最优解。

```cpp
class Solution {
public:
    int cuttingRope(int n) {
        if (n < 4) {
            return n == 2 ? 1 : 2;
        }
        long long ans = 1;
        // 若一个数由N个部分构成，则这N个部分越接近欧拉数 e = lim(1+1/x)^x = 2.7，它们的乘积就越大。
        while (n > 4) {
            ans = (ans * 3) % 1000000007;
            n -= 3;
        }
        if (n == 4) {
            ans = (ans * 4) % 1000000007;
        } else if (n == 3) {
            ans = (ans * 3) % 1000000007;
        } else if (n == 2) {
            ans = (ans * 2) % 1000000007;
        }
        return int(ans);
    }
};
```


## 剪绳子I（动态规划）
- 可：问题可分解成更小的子问题，f(n) = F(f(i))
- 能：当子问题得到答案后，可以推导出当前问题的解
- 有：各个子问题计算时有重叠部分（不能记忆化的是搜索|分治模型）
- 最优解：最值问题
- 步骤：自上而下分析，自下而上求解。


```cpp
class Solution {
public:
    int cuttingRope(int n) {
        if (n < 4) {
            return n == 2 ? 1 : 2;
        }
        auto *dp = new int[n + 2]; // 空间O(n)
        dp[0] = dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        // 时间O(n^2)
        for (int i = 4; i <= n; i++) {
            dp[i] = 0;
            for (int j = 1; j < i; j++) {
                dp[i] = max(dp[i], dp[j] * dp[i - j]);
            }
        }
        return (int) dp[n];
    }
};
```



## 回溯法
### 机器人的运动范围
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

链接：https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof

```cpp
class Solution {
    int x, y, cnt;
    bool *vis;
public:
    int movingCount(int m, int n, int k) {
        cnt = 0;
        // 一维数组当多维用:
        // arr[i][j] = arr[i*cols + j]
        // arr[i][j][k] = arr[i*(rows*cols) + j*cols + k]
        vis = new bool[(m) * (n)];
        memset(vis, 0, sizeof(bool) * m * n); // 初始化内存
        x = m;
        y = n;
        dfs(0, 0, k);
        delete[]vis;
        return cnt;
    }

    void dfs(int i, int j, int k) {
        if (i < 0 || j < 0 || i >= x || j >= y || vis[i * y + j]) {
            return;
        }
        if (i / 10 + (i % 10) + j / 10 + (j % 10) > k) {
            return;
        }
        vis[i * y + j] = true;
        cnt++;
        dfs(i - 1, j, k);
        dfs(i + 1, j, k);
        dfs(i, j - 1, k);
        dfs(i, j + 1, k);
    }
};
```

### 矩阵中的路径
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。
如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。
[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]
但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。

链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof

```cpp
class Solution {
public:
    bool exist(vector<vector<char>> &rect, string s) {
        if (rect.size() * rect[0].size() < s.size()) {
            return false;
        }
        if (rect.empty() || rect[0].empty()) {
            return s.empty();
        }
        for (int row = 0; row < rect.size(); ++row) {
            for (int col = 0; col < rect[0].size(); ++col) {
                if (dfs(rect, row, col, s, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    bool dfs(vector<vector<char>> &rect, int row, int col, const string &word, int k) {
        if (k == word.size()) {
            return true;
        }
        if (row < 0 || row >= rect.size() || col < 0 || col >= rect[0].size()) {
            return false;
        }
        if (word[k] != rect[row][col]) {
            return false;
        }

        rect[row][col] = '#'; // 就地记录访问标记
        if (dfs(rect, row - 1, col, word, k + 1) ||
            dfs(rect, row + 1, col, word, k + 1) ||
            dfs(rect, row, col - 1, word, k + 1) ||
            dfs(rect, row, col + 1, word, k + 1)) {
            return true;
        }
        rect[row][col] = word[k]; // 复位
        return false;
    }
};
```

## 寻找旋转排序数组中的最小值 II
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
请找出其中最小的元素。
注意数组中可能存在重复的元素。

https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/

```cpp
class Solution {
public:
    int findMin(vector<int> &nums) {
        int i = 0, j = nums.size() - 1, m;
        if (nums[i] < nums[j]) {
            return nums[i];
        }
        while (i < j) {
            m = i + ((j - i) >> 2);
            // 二分与右边点比较（右边界是原数组的有序分界点）
            if (nums[m] > nums[j]) {
                i = m + 1;
            } else if (nums[m] < nums[j]) {
                j = m;
            } else {
                --j;
            }
        }
        return nums[i];
    }
};

```

## Fibonacci数列
f(n) = f(n-1)+f(n-2), 其中f(0)=0,f(1)=1

**青蛙跳台阶**
青蛙可以一次跳1阶或2阶，求第N阶的跳法总数。f(n)=f(n-2)+f(n-1)，其中f(0)=f(1)=1

**青蛙跳台阶2**
青蛙可以一次跳1阶或2阶...或n阶，求第N阶的跳法总数。f(n)=f(n-1)+...f(1)+f(0)=2^(n-1)，其中f(0)=f(1)=1

**2xN方框覆盖**
一个`2*N`的方块，用`2*1`方块覆盖，求总覆盖方法数。f(n)=f(n-2)+f(n-1)，其中f(0)=f(1)=1

## 队列与栈互实现

**双栈实现队列**
- 入队：始终往A栈压入
- 出队：仅弹出B栈，若B为空则弹出A压入B。

**双队列实现栈**
- 入栈：始终进A队列
- 出栈：若队列A
    - 为空：B出进A，直到B仅剩一个元素做栈顶元素
    - 仅一个元素：A队头做栈顶元素
    - 多个元素：A出进B，直到A仅剩一个元素做栈顶元素

 
## 二叉树下一个结点
给出一棵树和一个结点，求该结点的中序遍历中的下一个结点（结点右父结点指针）：
- 若结点有右子树，下一个结点为*右子树的最左结点*
- 否则若该结点是其父节点的左结点，则下一个结点为*父结点*
- 否则下一个结点：一个祖先结点，该结点为其父节点左结点
 

## 反方向输出链表
给一个链表头指针，反向输出链表。

**思路**
- 反向修改链表指针
- 栈或递归遍历链表
- 统计结点数，用反向vector迭代器存入链表正向遍历结点。


## URL字符编码
把输入字符串中的空格转成`%20`(百分号+空格的两位十六进制ASCII码)。

**逆序双指针**
避免移位带来的时间消耗，和辅助空间浪费：先统计空格数，再拓展原数组空间，从末尾往前转换填充。

注：通常合并有序数组，逆序复制效果会更好。

```cpp
class Solution {
public:
    string replaceSpace(string s) {
        int i = s.find(0x20, 0), j;
        int cnt = 0;
        while (i >= 0 && i < s.size()) {
            cnt++;
            i = s.find(0x20, i + 1);
        }
        i = s.size() - 1;
        s.resize(s.size() + cnt * 2, ' ');
        j = s.size() - 1;
        while (i >= 0) {
            if (s[i] == 0x20) {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
                --i;
            } else {
                s[j--] = s[i--];
            }
        }
        return s;
    }
};
```

## 二维数组中查找
二维数组中，每一行从左到右递增，从上到下递增。需实现输入一个整数，判断该数是否在数组中存在。

**反斜角查找**
正斜角开始查找（左上角或右下角），会导致接下来的两个区域有重叠，从而使问题复杂。
而反斜角开始查找（右上角或左下角），会导致接下来仅查找一个区域即可。



## 数组中的重复数字
找出数组中重复的数字。
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

示例 1：
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
 
限制：
2 <= n <= 100000

链接：https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof


**一般方法**
- 双重循环查找：T:O(n^2)
- 排序后查找：T:O(nLogn) 
- 哈希表：T:O(n) S:O(n)

**原地哈希（鸽巢原理）**
每找到一个`N[i]`：
- 若 `N[i] == i`, 则`++i`
- 否则 若 `N[i] == N[N[i]]`，找到重复数字 `N[i]`
- 否则 交换`N[i] <=> N[N[i]]`(此时 `N[x]== x`，其中`x=N[i]`)，继续搜索。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int> &N) {
        for (int i = 0, t; i < N.size();) {
            if (N[i] == i) {
                ++i;
            } else {
                t = N[N[i]];
                if (t == N[i]) {
                    return t;
                }
                N[N[i]] = N[i];
                N[i] = t;
            }
        }
        return -1;
    }
};
```

**历史标记**
把每个访问过的值作为下标，将其对应的数值改为负数（是其已经访问的标记），当找到负值标记时直接返回。
优点：原数组修改后可复原。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int> &arr) {
        for (int i = 0, n; i < arr.size(); i++) {
            n = arr[i] < 0 ? -arr[i] : arr[i];
            if (arr[n] < 0) {
                return n;
            }
            // 标记赋值表示访问过
            arr[n] = -arr[n];
        }
        return 0;
    }
};
```

### 拓展
在长度为 n 的数组中所有的数字都在 `1 ~ n-1` 范围（所以至少有一个数字重复），找出任意一个重复数字。
要求：不能修改原数组。

思路：二分统计数字，若某部分统计超额则存在重复数字。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int> &N) {
        int mid, cnt;
        int left = 0, right = N.size();
        while (left <= right) {
            mid = left + ((right - left) / 2);
            cnt = count(N, left, mid);
            
            // 重复值为left
            if (left == mid) {
                return left;
            }

            if (cnt > mid - left) {
                // 重复值在[0, mid)
                right = mid;
            } else {
                // 重复值在[mid, right)
                left = mid;
            }
        }
        return -1;
    }

private:
    int count(vector<int> &N, int left, int right) {
        int cnt = 0;
        for (int i = 0; i < N.size(); i++) {
            if (N[i] >= left && N[i] < right) {
                ++cnt;
            }
        }
        return cnt;
    }
};
```

