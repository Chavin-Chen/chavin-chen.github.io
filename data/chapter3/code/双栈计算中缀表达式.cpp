#include <cstring>
#include <iostream>
#include <stack>

using namespace std;

// 获取符号优先级
int priority(char);
// 计算二元式压入数字栈
void calc(stack<int> &nStk, stack<char> &oStk);

int main() {
    char input[1000];
    cin >> input;
    int i = 0, len = strlen(input), tmp;
    stack<char> oStk;
    stack<int> nStk;
    while (i < len) {
        if (input[i] >= '0' && input[i] <= '9') { // 如果是数字，则提取出来直接入栈
            tmp = 0;
            while (i < len && input[i] >= '0' && input[i] <= '9') {
                tmp = tmp * 10 + input[i++] - '0';
            }
            nStk.emplace(tmp);
            continue;
        }
        // 当符号栈为空 或 优先级高于栈顶【入栈】
        if (oStk.empty() || priority(input[i]) > priority(oStk.top())) {
            oStk.emplace(input[i++]);
        } else if (oStk.top() == '(') { // 栈顶符号优先级更高，为左括号时
            if (input[i] == ')') { // 括号匹配直接弹出
                oStk.pop();
            } else { // 栈顶时左括号，当前为其他符号直接【入栈】
                oStk.emplace(input[i]);
            }
            ++i;
        } else { // 栈顶非左括号 且 优先级更高，出栈计算
            calc(nStk, oStk);
        }
    }
    // 清空符号栈，计算表达式
    while (!oStk.empty()) calc(nStk, oStk);
    cout << nStk.top() << endl;
    return 0;
}

int priority(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 3;
        default:
            return 0;
    }
}

void calc(stack<int> &nStk, stack<char> &oStk) {
    char ch = oStk.top();
    oStk.pop();
    int y = nStk.top();
    nStk.pop();
    int &x = nStk.top();
    switch (ch) {
        case '-':
            x = x - y;
            break;
        case '*':
            x = x * y;
            break;
        case '/':
            x = x / y;
            break;
        default:
            x = x + y;
            break;
    }
}