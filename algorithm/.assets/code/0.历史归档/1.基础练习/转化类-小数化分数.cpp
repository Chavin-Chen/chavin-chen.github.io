/**
 * 【问题描述】
 *  任何小数都能表示成分数的形式，对于給定的小数，编写程序其化为最简分数输出，小数包括简单小数和循环小数。
 * 【输入形式】
 *  第一行是一个整数N，表示有多少组数据。
 *  每组数据只有一个纯小数，也就是整数部分为0。小数的位数不超过9位，循环部分用()括起来。
 * 【输出形式】
 *  对每一个对应的小数化成最简分数后输出，占一行
 * 【样例输入】
 * 3
 * 0.(4)
 * 0.5
 * 0.32(692307)
 * 【样例输出】
 * 4/9
 * 1/2
 * 17/52
 * ————————————————
 * 非循环小数化分数：0.123 = 123/1000
 * 循环小数化分数：0.12(4)
 *  - 分子：124 - 12，非循环部分拼循环节-非循环部分
 *  - 分母：900，循环节部分替换为9拼非循环部分替换为0
 */

#include<iostream>

using namespace std;

int gcd(int x, int y);

int main() {
    string s;
    int i, j, T;
    // 输入T组数据
    cin >> T;
    while (T--) {
        cin >> s;
        i = s.find('(');
        j = s.find(')');
        if (i == string::npos || j == string::npos) {
            // 如果没有循环小数, 假设输入为：0.123
            // 分子b = 123
            int b = (int) strtol(s.c_str() + 2, nullptr, 10);
            // 分母a = 1000
            int a = 1;
            for (i = 0; i < s.size() - 2; i++) {
                a *= 10;
            }
            // 则小数为 = 123/1000 的化简值
            int div = gcd(b, a);
            cout << b / div << "/" << a / div << endl;
        } else {
            // (混)循环小数转分数：(非循环部分拼循环节-非循环部分)/(循环节部分替换为9拼非循环部分替换为0）
            int a, b, t;
            s[i] = s[j] = 0;
            // 非循环部分
            int aCyc = (int) strtol(s.c_str() + 2, nullptr, 10);
            // 循环节
            int cyc = (int) strtol(s.c_str() + i + 1, nullptr, 10);
            // 分子 b = 非循环拼循环节 - 非循环部分
            t = aCyc;
            for (int k = i + 1; k < j; k++) {
                t *= 10;
            }
            b = t + cyc - aCyc;
            // 分母 a = 循环节部分替换为9拼非循环部分替换为0
            t = 0;
            for (int k = i + 1; k < j; k++) {
                t = t * 10 + 9;
            }
            a = t;
            for (int k = 2; k < i; k++) {
                a *= 10;
            }
            // 用最大公约数化简分数
            int div = gcd(b, a);
            cout << b / div << "/" << a / div << endl;
        }
    }
    return 0;
}

int gcd(int x, int y) {
    return 0 == y ? x : gcd(y, x % y);
}
