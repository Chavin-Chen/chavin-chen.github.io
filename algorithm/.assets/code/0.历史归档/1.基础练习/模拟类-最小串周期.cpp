/**
 * https://www.dotcpp.com/oj/status.php?user=chavin
 *
 * 题目描述
 * 右右喜欢听故事，但是右右的妈妈总是讲一些“从前有座山，山里有座庙，庙里有个老和尚给小和尚讲故事，讲的什么呢？从前有座山……”这样循环的故事来搪塞右右。
 * 我们定义，如果一个字符串是以一个或者一个以上的长度为k的重复字符串所连接成的，那么这个字符串就叫做周期为k的串。
 * 例如:
 * 字符串’abcabcabcabc’周期为3，因为它是由4个循环’abc’组成的。它同样是以6为周期（两个重复的’abcabc’）和以12为周期（一个循环’abcabcabcabc’）。
 * 右右现在想给他的朋友大灰狼转述妈妈讲的故事，请帮他写一个程序，可以测定一个字符串的最小周期。
 *
 * 输入
 * 一个最大长度为100的无空格的字符串。
 *
 * 输出
 * 一个整数，表示输入的字符串的最小周期。
 *
 * 样例输入
 * HaHaHa
 *
 * 样例输出
 * 2
 */
#include<iostream>

using namespace std;

int main() {
    string input;
    while (cin >> input) {
        int period = 1;
        // 从最小周期开始枚举
        while (period < input.size()) {
            bool isCycle = true;
            int i;
            // 验证周期串
            for (i = 0; i < input.size(); i++) {
                if (input[i % period] != input[i]) {
                    isCycle = false;
                    break;
                }
            }
            // 如果已经证明是周期串，则输出当前周期
            if (isCycle && i % period == 0) {
                cout << period << endl;
                break;
            }
            // 找到一个可以做周期的值
            do {
                ++period;
            } while (period < input.size() && input.size() % period != 0);
        }
        // 如果周期枚举到串长度了，说明不是周期串
        if (period >= input.size()) {
            cout << input.size() << endl;
        }
    }
    return 0;
}
