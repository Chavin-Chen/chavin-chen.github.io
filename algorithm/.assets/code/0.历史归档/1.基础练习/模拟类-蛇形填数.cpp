/**
 * https://www.dotcpp.com/oj/problem1796.html
 * 问题 1796: 蛇形填数
 *
 * 时间限制: 1Sec 内存限制: 128MB 提交: 501 解决: 126
 *
 * 题目描述
 * 在 n * n 方阵里填入 1, 2, …, n * n, 要求填成蛇形。例如 n = 4 时方阵为：
 *
 * 10 11 12 1
 * 9 16 13 2
 * 8 15 14 3
 * 7  6  5 4
 * 输入
 * 多组测试数据。
 * 每组测试数据第一行输入方阵的维数，即 n 的值。(n <= 100)
 * 输出
 * 每组测试数据输出结果是蛇形方阵，方阵中每行每两个元素间空格，末尾不要有多余空格，每个方阵后空一行。
 * 样例输入
 * 3
 * 样例输出
 * 7 8 1
 * 6 9 2
 * 5 4 3
 *
 */
#include<iostream>

using namespace std;
int a[105][105];

int main() {
    int n;
    cin >> n;
    int val, i = 1, j = n;
    val = a[i][j] = 1;
    while (val < n * n) {
        while (i + 1 <= n && !a[i + 1][j]) {
            a[++i][j] = ++val;
        }
        while (j - 1 >= 1 && !a[i][j - 1]) {
            a[i][--j] = ++val;
        }
        while (i - 1 >= 1 && !a[i - 1][j]) {
            a[--i][j] = ++val;
        }
        while (j + 1 <= n && !a[i][j + 1]) {
            a[i][++j] = ++val;
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cout << ((j == 1) ? "" : " ") << a[i][j];
        }
        cout << endl;
    }
    return 0;
}
