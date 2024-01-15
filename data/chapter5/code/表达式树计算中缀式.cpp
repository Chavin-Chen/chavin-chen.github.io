#include <iostream>
#include <sstream>
using namespace std;

struct Node {
    int val;
    Node *L, *R;

    Node(int v) {
        val = v;
        L = R = nullptr;
    }
};

// 判断串是否是数字
template<typename T>
bool isNumber(const string &str, T test);

// 构造表达式树
Node *buildTree(const string &input);

// 后序遍历求解
int posCalc(Node *node);

int main() {
    // (1+2)*3-8/(2+2)*3 = 3
    string input;
    cin >> input;
    cout << posCalc(buildTree(input)) << endl;
    return 0;
}

template<typename T>
bool isNumber(const string &str, T test) {
    istringstream sin(str);
    return sin >> test && sin.eof();
}

Node *buildTree(const string &input) {
    if (isNumber(input, 0)) {
        // 纯数字表达式解析为叶子节点
        int n = stoi(input);
        Node *node = new Node(n);
        return node;
    }
    // 找到优先级最低的运算符(后缀式最外层的运算符(最后执行运算))
    int addOrSub = -1, multiOrDiv = -1, bracket = 0;
    for (int i = 0; i < input.size(); i++) {
        switch (input.at(i)) {
            case '(':
                bracket++;
                break;
            case ')':
                bracket--;
                break;
            case '+':
            case '-':
                if (bracket == 0) {
                    addOrSub = i;
                }
                break;
            case '*':
            case '/':
                if (bracket == 0) {
                    multiOrDiv = i;
                }
                break;
        }
    }
    int optIndex = addOrSub < 0 ? multiOrDiv : addOrSub;
    // 若这是一个被括号包裹的表达式(去掉括号重新构造)
    if (optIndex < 0) {
        return buildTree(input.substr(1, input.size() - 2));
    }
    // 构造左右子树
    Node *node = new Node(input.at(optIndex));
    node->L = buildTree(input.substr(0, optIndex));
    node->R = buildTree(input.substr(optIndex + 1));
    return node;
}

int posCalc(Node *node) { // 后序遍历求解
    if (nullptr == node) {
        return 0;
    }
    // 叶子结点说明是纯数字表达式
    if (nullptr == node->L && nullptr == node->R) {
        return node->val;
    }
    // 非叶子结点需要计算
    switch (node->val) {
        case '+':
            return posCalc(node->L) + posCalc(node->R);
        case '-':
            return posCalc(node->L) - posCalc(node->R);
        case '*':
            return posCalc(node->L) * posCalc(node->R);
        case '/':
            return posCalc(node->L) / posCalc(node->R);
    }
    return 0;
}