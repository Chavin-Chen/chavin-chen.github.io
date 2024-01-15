#include <iostream>
#include <stack>
using namespace std;

int main() {
    char num[101], res[101];
    int i, j, mod, rad;
    stack<int> stk;
    // 输入大数 与 进制值R
    cin >> num >> rad;
    while (true) {
        mod = i = j = 0;
        // 模拟竖式除法:从高位到低位依次取被除数
        while (0 != num[i]) {
            mod = mod * 10 + num[i++] - '0';
            // 如果当前值tmp除以R有非前导零的商，则记录到res中
            if (mod / rad > 0 || (mod / rad == 0 && j > 0)) {
                res[j++] = (char) (mod / rad + '0');
            }
            mod %= rad;
        }
        // 余数压入栈中
        stk.emplace(mod);
        // 如果没有商了，终止除法
        if (j == 0) break;
        // 用商做被除数
        for (int k = 0; k < j; k++) num[k] = res[k];
        num[j] = 0;
    }
    // 栈弹出，逆序输出
    while (!stk.empty()) {
        if (stk.top() > 9) {
            cout << (char) (stk.top() - 10 + 'A');
        } else {
            cout << stk.top();
        }
        stk.pop();
    }
    cout << endl;
    return 0;
}