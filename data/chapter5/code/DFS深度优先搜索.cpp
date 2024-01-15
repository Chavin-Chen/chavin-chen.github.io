#include<iostream>
using namespace std;

struct Node {
    char data;
    Node *L, *R;
};

void create(Node *&p);

// 函数栈方式实现 先序遍历
void dfsProRecursively(Node *p);

// 函数栈方式实现 中序遍历
void dfsMidRecursively(Node *p);

// 函数栈方式实现 后序遍历
void dfsPosRecursively(Node *p);

// 手工栈方式实现 先序遍历
void dfsProByStack(Node *p);

// 手工栈方式实现 中序遍历
void dfsMidByStack(Node *p);

// 手工栈方式实现 后序遍历
void dfsPosByStack(Node *p);

int main() {
    Node *root = new Node;
    // 创建二叉树
    create(root);

    dfsProRecursively(root);
    cout << endl;
    dfsProByStack(root);

    dfsMidRecursively(root);
    cout << endl;
    dfsMidByStack(root);

    dfsPosRecursively(root);
    cout << endl;
    dfsPosByStack(root);
    return 0;
}

void dfsProRecursively(Node *p) { // 先序遍历：函数递归栈实现
    if (!p) return;
    cout << p->data;
    dfsProRecursively(p->L);
    dfsProRecursively(p->R);
}

void dfsProByStack(Node *p) { // 先序遍历：手工栈实现
    // 创建栈
    Node *stack[100];
    int top = -1;
    // 结点指针非空 或 栈非空
    while (p || top >= 0) {
        // 纵向搜索左子树，直到叶子
        for (; p != nullptr; p = p->L) {
            // 纵向左搜过程先输出根节点
            cout << p->data;
            // 遍历后把根结点入栈
            stack[++top] = p;
        }
        if (top != -1) {
            // 切换到子树
            p = stack[top--]->R;
        }
    }
}

void dfsMidRecursively(Node *p) { // 中序遍历：函数递归栈实现
    if (!p) return;
    dfsMidRecursively(p->L);
    cout << p->data;
    dfsMidRecursively(p->R);
}

void dfsMidByStack(Node *p) { // 中序遍历：手工栈实现
    Node *stack[100];
    int top = -1;
    // 结点指针非空 或 栈非空
    while (p || top >= 0) {
        // 纵向遍历左子树，结点先全部入栈
        for (; p != nullptr; p = p->L) {
            stack[++top] = p;
        }
        if (top != -1) {
            // 输出栈顶数据（左子树）：当左子树未空或已访问时
            p = stack[top--];
            cout << p->data;
            // 切换到右子树进行搜索
            p = p->R;
        }
    }
}

void dfsPosRecursively(Node *p) { // 后序遍历：函数递归栈实现
    if (!p) return;
    dfsPosRecursively(p->L);
    dfsPosRecursively(p->R);
    cout << p->data;
}

void dfsPosByStack(Node *p) { // 后序遍历：手工栈实现
    Node *stack[100];
    int isVisR[100], top = -1;
    // 结点指针非空 或 栈非空
    while (p || top != -1) {
        // 纵向搜索左子树，所有结点入栈
        if (p) {
            stack[++top] = p;
            // 入栈后标记该结点右子树未访问
            isVisR[top] = 0;
            p = p->L;
        } else {
            // 如果栈顶（根结点）右子树未访问，就先搜索右子树
            if (!isVisR[top]) {
                p = stack[top]->R;
                // 并标记栈顶结点右子树已访问
                isVisR[top] = 1;
            } else {
                // 输出栈顶结点数据：在左右子树都访问后
                cout << stack[top--]->data;
            }
        }
    }

}

void create(Node *&p) { // 先序方式创建二叉树
    char d;
    cin >> d;
    // 输入#结束
    if (d == '#') {
        p = nullptr;
        return;
    } else {
        p = new Node;
        p->data = d;
        create(p->L);
        create(p->R);
    }
}