#include<iostream>
using namespace std;

struct Node {
    int val;
    int d;
    Node *L, *R;
    Node(int v) {
        val = v;
        d = 1;
        L = R = nullptr;
    }
    inline int getLDepth() { return getDepth(L); }
    inline int getRDepth() { return getDepth(R); }
    inline static int getDepth(Node *p) { return nullptr == p ? 0 : p->d; }
};

void l2Root(Node *&root) { // 将root->L旋转到root的位置
    Node *p = root->L;
    root->L = p->R;
    p->R = root;
    p->R->d = max(p->R->getLDepth(), p->R->getRDepth()) + 1;
    p->d = max(p->getLDepth(), p->getRDepth()) + 1;
    root = p; // root=l2Root(root)
}

void r2Root(Node *&root) { // 将root->R旋转到root的位置
    Node *p = root->R;
    root->R = p->L;
    p->L = root;
    p->L->d = max(p->L->getLDepth(), p->L->getRDepth()) + 1;
    p->d = max(p->getLDepth(), p->getRDepth()) + 1;
    root = p; // root=r2Root(root)
}

void reBalance(Node *&p) { // 刷新根p的子树高度，并对p子树做平衡处理
    if (nullptr == p) return;
    p->d = max(p->getLDepth(), p->getRDepth()) + 1; // 刷新当前子树高度
    if (p->getLDepth() - p->getRDepth() > 1) {
        int lLDepth = Node::getDepth(p->L->L);
        int lRDepth = Node::getDepth(p->L->R);
        if (lLDepth >= lRDepth) { // LL型
            l2Root(p);
        } else { // LR型
            r2Root(p->R);
            l2Root(p);
        }
    } else if (p->getRDepth() - p->getLDepth() > 1) {
        int rLDepth = Node::getDepth(p->R->L);
        int rRDepth = Node::getDepth(p->R->R);
        if (rRDepth >= rLDepth) { // RR型
            r2Root(p);
        } else { // RL型
            l2Root(p->L);
            r2Root(p);
        }
    }
}

void add(Node *&p, int n) {
    if (nullptr == p) {
        p = new Node(n);
        return;
    }
    if (n <= p->val) add(p->L, n);
    else add(p->R, n);
    reBalance(p);
}

void remove(Node *&p, int n) {
    if (nullptr == p) return;
    if (n < p->val) remove(p->L, n);
    else if (n > p->val) remove(p->R, n);
    else if (p->val == n) {
        if (nullptr == p->L && nullptr == p->R) { // 只有叶子结点可以直接删除
            p = nullptr;
            return;
        }
        if (p->getLDepth() >= p->getRDepth()) { // 左子树高度更高，找前驱结点做根
            Node *tmp = p->L;
            while (nullptr != tmp->R) tmp = tmp->R;
            p->val = tmp->val;
            remove(p->L, tmp->val);
        } else { // 右子树高度更高，找后继结点做根
            Node *tmp = p->R;
            while (nullptr != tmp->L) tmp = tmp->L;
            p->val = tmp->val;
            remove(p->R, tmp->val);
        }
    }
    reBalance(p); // 平衡处理
}

Node *find(Node *const p, int n) {
    if (nullptr == p) return nullptr;
    if (p->val == n) return p;
    Node *res;
    if (n > p->val && nullptr != (res = find(p->R, n))) return res;
    return find(p->L, n);
}
// ==================================================================
void dfs(Node *p, const string &s, const string &pre) {
    if (nullptr == p) return;
    cout << s << pre << p->val << endl;
    dfs(p->L, s + "|    ", "|--");
    dfs(p->R, s + "|    ", "|++");
}

int main() {
    Node *root = nullptr;
    for (int i = 1; i <= 100; i++) {
        add(root, i);
    }

    dfs(root, "", "");
    for (int i = 0; i < 200; i++) {
        remove(root, i);
    }
    dfs(root, "", "");
    return 0;
}
