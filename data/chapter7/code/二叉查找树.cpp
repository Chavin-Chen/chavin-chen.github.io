#include<iostream>
using namespace std;

struct Node {
    int val;
    Node *L, *R;

    Node() {
        val = 0;
        L = R = nullptr;
    }
};

void build(Node *&p, int e);

void dfsMid(Node *p);

int main() {
    int arr[] = {3, 5, 7, 2, 0, 9, 4, 11, 13, 1};
    Node *root = nullptr;
    for (int i : arr) {
        if (root == nullptr) {
            root = new Node;
            root->val = i;
        } else {
            // 构建二叉查找树
            build(root, i);
        }
    }

    // 中序遍历得到排序序列
    dfsMid(root);
    return 0;
}

void build(Node *&p, int e) {
    if (p == nullptr) {
        p = new Node;
        p->val = e;
    } else if (e <= p->val) {
        build(p->L, e);
    } else {
        build(p->R, e);
    }
}

void dfsMid(Node *p) {
    if (nullptr == p) {
        return;
    }
    dfsMid(p->L);
    cout << p->val << " ";
    dfsMid(p->R);
}
