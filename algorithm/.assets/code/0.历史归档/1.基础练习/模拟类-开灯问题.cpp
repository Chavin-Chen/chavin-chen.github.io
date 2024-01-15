/**
 * 题目描述
 * 有n个灯，（每个灯只有一个开关，按一下开，再按一下关）来了k个人，所有的灯刚开始时都关着的。
 * 第一个人按下了所有编号为 1 的倍数的灯的开关（也就是把所有灯都打开了），
 * 第二个人按下了所有编号为2的倍数的灯的开关，
 * 第三个人按下所有编号为3 的倍数的灯的开关……按此规律，
 * 问最后那些灯亮着？
 *
 * k<=n<=1000
 */

#include<iostream>

using namespace std;

int main() {
    int n, k;
    bool light[1001] = {};
    cin >> n >> k;
    // 可以把false看成灯开，这样一号打开了所有灯就可以省略一个O(n)遍历
    for (int i = 2, j; i <= k; i++) {
        j = i;
        // 操作所有 N*i 的灯
        while (j <= n) {
            light[j] = !light[j];
            j += i;
        }
    }
    bool isFirst = true;
    for (int i = 1; i <= n; i++) {
        if (!light[i]) {
            cout << (isFirst ? "" : " ") << i;
            isFirst = false;
        }
    }
    return 0;
}
