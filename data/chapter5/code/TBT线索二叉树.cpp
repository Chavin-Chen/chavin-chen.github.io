#include<iostream>
using namespace std;

struct Node {
    int data;
    bool isL2Child, isR2Child;
    Node *L, *R;
    Node() {
        data = 0;
        L = R = nullptr;
    }
};

bool create(Node *&p);
Node *lastP;

// 线索化
void dfsProAndThreaded(Node *p);
void dfsPosAndThreaded(Node *p);
void dfsMidAndThreaded(Node *p);

// 通过后继找先序
void dfsProByRClue(Node *headP);

// 通过前驱找后序
void dfsPosByLClue(Node *headP);

// 通过后继找中序
void dfsMidByRClue(Node *head);
// 通过前驱找中序
void dfsMidByLClue(Node *head);

// 1 2 4 0 7 0 0 5 0 0 3 0 6 0 0
int main() {
    Node *root, *headP;
    // ======================= 先序线索 ========================
    create(root);
    lastP = headP = new Node;

    // 线索化
    dfsProAndThreaded(root);

    // 得到顺序的先序遍历
    lastP->R = headP;
    dfsProByRClue(headP);

    cout << endl << "=======================" << endl;

    // ======================= 后序线索 ========================
    create(root);
    lastP = headP = new Node;

    // 线索化
    dfsPosAndThreaded(root);

    // 得到逆序的后序遍历
    headP->L = lastP;
    dfsPosByLClue(headP);

    cout << endl << "=======================" << endl;

    // ======================= 中序线索 ========================
    create(root);
    lastP = headP = new Node;

    // 线索化
    dfsMidAndThreaded(root);

    // 根据线索进行中序遍历
    lastP->R = headP;
    headP->L = lastP;

    dfsMidByRClue(headP);
    cout << endl;
    dfsMidByLClue(headP);
    return 0;
}

void dfsProAndThreaded(Node *p) {
    if (!p) return;
    // 线索化
    if (!lastP->isR2Child) {
        lastP->R = p;
    }
    if (!p->isL2Child) {
        p->L = lastP;
    }

    // 访问当前结点
    cout << p->isL2Child << " " << p->data << " " << p->isR2Child << endl;
    lastP = p;

    // 搜索子树
    if (p->isL2Child) {
        dfsProAndThreaded(p->L);
    }
    if (p->isR2Child) {
        dfsProAndThreaded(p->R);
    }
}

void dfsPosAndThreaded(Node *p) {
    if (!p) return;
    // 搜索子树
    if (p->isL2Child) {
        dfsPosAndThreaded(p->L);
    }
    if (p->isR2Child) {
        dfsPosAndThreaded(p->R);
    }
    // 线索化
    if (!lastP->isR2Child) {
        lastP->R = p;
    }
    if (!p->isL2Child) {
        p->L = lastP;
    }

    // 访问当前结点
    cout << p->isL2Child << " " << p->data << " " << p->isR2Child << endl;
    lastP = p;
}

void dfsMidAndThreaded(Node *p) {
    if (!p) return;
    // 搜索左子树
    if (p->isL2Child) {
        dfsMidAndThreaded(p->L);
    }

    // 线索化
    if (!lastP->isR2Child) {
        lastP->R = p;
    }
    if (!p->isL2Child) {
        p->L = lastP;
    }

    // 访问当前结点
    cout << p->isL2Child << " " << p->data << " " << p->isR2Child << endl;
    lastP = p;

    // 搜索右子树
    if (p->isR2Child) {
        dfsMidAndThreaded(p->R);
    }
}

void dfsProByRClue(Node *headP) {
    Node *p = headP->R;
    while (p != headP) {
        cout << p->data;
        // 左子树 > 右子树,后继线索
        if (p->isL2Child) {
            p = p->L;
        } else {
            p = p->R;
        }
    }
}

void dfsPosByLClue(Node *headP) {
    Node *p = headP->L;
    while (p != headP) {
        cout << p->data;
        // 右子树 > 左子树,前驱线索
        if (p->isR2Child) {
            p = p->R;
        } else {
            p = p->L;
        }
    }
}

void dfsMidByRClue(Node *head) {
    Node *p = head->R;
    while (p != head) {
        cout << p->data;
        if (!p->isR2Child) {
            p = p->R;
        } else { // 后继线索 > 右子树的最左叶子
            p = p->R;
            while (p->isL2Child) {
                p = p->L;
            }
        }

    }
}

void dfsMidByLClue(Node *head) {
    Node *p = head->L;
    while (p != head) {
        cout << p->data;
        if (!p->isL2Child) {
            p = p->L;
        } else { // 前驱线索 > 左子树的最后叶子
            p = p->L;
            while (p->isR2Child) {
                p = p->R;
            }
        }
    }
}

bool create(Node *&p) {
    int input;
    cin >> input;
    if (0 == input) {
        p = nullptr;
        return false;
    }
    p = new Node;
    p->data = input;
    p->isL2Child = create(p->L);
    p->isR2Child = create(p->R);
    return true;
}