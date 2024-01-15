#include<iostream>
#include<stack>
using namespace std;

int main() {
    int n, out, in = 1;
    bool ok = true;
    stack<int> stk;
    cin >> n;
    // N个元素依次进站
    while (n--) {
        cin >> out;
        // 当前已经不合法了，只接受输入
        if (!ok) continue;
        // 判断 出站序号 和 进站序号
        if (in <= out) {
            // 如果 出站序号 大于 待进站序号，则先考虑批量进站
            while (in < out) {
                stk.emplace(in++);
            }
            // 出站序号 等于 进站序号
            in++;
        } else {
            // 如果 出站序号 小于 待进站序号，则查看栈顶：出站或标记非法
            if (!stk.empty() && stk.top() == out) {
                stk.pop();
            } else {
                ok = false;
            }
        }
    }
    cout << (ok ? "Yes" : "No") << endl;
    return 0;
}