// 题目连接：https://www.nowcoder.com/practice/00ffd656b9604d1998e966d555005a4b

#include<iostream>
#include<stack>

using namespace std;

string pos[] = {"", "拾", "佰", "仟"}; // x%4 != 0
string unit[] = {"元", "万", "亿"}; // x%4==0 => x/4
string num[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};

int main(int argc, char *argv[]) {
    string input;
    cin >> input;
    stack<string> ans;
    int pot = input.find('.');
    if (pot > 0) {
        if (pot + 2 < input.length() && input[pot + 2] - '0' > 0) {
            ans.push("分");
            ans.push(num[input[pot + 2] - '0']);
        }
        if (pot + 1 < input.length() && input[pot + 1] - '0' > 0) {
            ans.push("角");
            ans.push(num[input[pot + 1] - '0']);
        }
    }
    if (ans.empty()) ans.push("整");
    if (atoi(input.data()) >= 1) {
        char *s = new char[pot];
        for (int j = 0, i = pot - 1; i >= 0; i--) {
            s[j++] = input[i];
        }
        bool canZero = false;
        for (int i = 0; i < pot; i++) {
            if (i % 4 == 0) { // 加单位
                ans.push(unit[i / 4]);
            }
            if (s[i] > '0') { // 加数字
                ans.push(pos[i % 4]); // 十百千
                if (i % 4 == 1 && s[i] - '0' == 1) {
                    continue;
                }
                ans.push(num[s[i] - '0']);
                canZero = true;
            } else if (i % 4 != 0 && canZero) { // 加中缀零
                canZero = false;
                ans.push(num[0]);
            }
        }
    }
    cout << "人民币";
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    cout << endl;
    return 0;
}