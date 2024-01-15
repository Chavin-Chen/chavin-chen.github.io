/**
 * https://www.dotcpp.com/oj/problem2080.html
 *
 * 【题目描述】
 * 给定n个十六进制正整数，输出它们对应的八进制数。
 *
 * 【输入】
 * 输入的第一行为一个正整数n （1<=n<=10）。
 * 接下来n行，每行一个由0~9、大写字母A~F组成的字符串，表示要转换的十六进制正整数，每个十六进制数长度不超过100000。
 *
 * 【输出】
 * 输出n行，每行为输入对应的八进制正整数。
 *
 * 【注意】
 * 输入的十六进制数不会有前导0，比如012A。
 * 输出的八进制数也不能有前导0。
 *
 * 【样例输入】
 * 2
 * 39
 * 123ABC
 *
 * 【样例输出】
 * 71
 * 4435274
 * 提示
 *
 * 【提示】
 * 先将十六进制数转换成某进制数，再由某进制数转换成八进制。
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef char byte;

byte getHexValue(char c);

int main() {
    vector<byte> bin;
    stack<byte> oct;
    byte val;
    int T;
    string input;

    cin >> T;
    while (T--) {
        cin >> input;
        // 翻转Hex串
//        reverse(begin(input), end(input));
        for (int i = 0, j = input.size() - 1; i < j; i++, j--) {
            input[i] ^= input[j];
            input[j] ^= input[i];
            input[i] ^= input[j];
        }

        // Hex to Binary
        bin.clear();
        for (int i = 0; i < input.size(); i++) {
            val = getHexValue(input[i]);
            for (int j = 0; j < 4; j++) {
                bin.push_back(val & 1);
                val >>= 1;
            }
        }

        // 从低位 Bin to Oct
        for (int i = 0; i < bin.size(); i += 3) {
            val = 0;
            for (int j = 0; j < 3 && i + j < bin.size(); j++) {
                val = val + (bin[i + j] << j);
            }
            oct.push(val);
        }

        // 逆序输出（高位->低位）八进制
        bool filter = false;
        while (!oct.empty()) {
            byte val = oct.top();
            // 过滤前导0
            filter = filter || val;
            if (filter) {
                cout << (int)val;
            }
            oct.pop();
        }
        cout << endl;
    }
    return 0;
}

byte getHexValue(char c) {
    if (c >= '0' && c <= '9') {
        return (byte) (c - '0');
    }
    return (byte) (c - 'A' + 10);
}
