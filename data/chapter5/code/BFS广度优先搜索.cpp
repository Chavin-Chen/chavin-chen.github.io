#include <iostream>
using namespace std;

struct Node {
    char ch;
    Node *l, *r;
} *queue[100];
int ap = 0;

void create(Node *&p);
void bfs(Node *root);

int main() {
    Node *root;
    // 以先序方式创建二叉树
    create(root);
    // 借助队列宽度优先遍历
    bfs(root);
    return 0;
}

void create(Node *&p) {
    char input;
    cin >> input;
    if (input == '#') {
        p = nullptr;
    } else {
        // 创建根结点
        p = new Node;
        p->ch = input;
        // 构建左子树
        create(p->l);
        // 构建右子树
        create(p->r);
    }
}

void bfs(Node *root) {
    // 根结点加入队列
    queue[ap++] = root;
    // 遍历当前队列中的结点
    for (int i = 0; i < ap; i++) {
        cout << queue[i]->ch;
        // 如果结点还有子结点，同样加入到队列中
        if (queue[i]->l) {
            queue[ap++] = queue[i]->l;
        }
        if (queue[i]->r) {
            queue[ap++] = queue[i]->r;
        }
    }
}
