#include <iostream>
using namespace std;
struct Node {
    char val;
    Node* next;
    Node() { next = NULL; }
};
char s[10];
int main() {
    int n, i;
    char val;
    Node *head = new Node, *p = head;
    // 链表长度为N
    cin >> n;
    while (n--) {
        p->next = new Node;
        cin >> p->next->val;
        p = p->next;
    }
    while (cin >> s && s[0] != 'q') {
        if (s[0] == 'a') {
            cin >> i >> val;
            p = head;
            for (int j = 0; j < i; j++) {
                p = p->next;
            }
            // 插入结点
            Node* temp = p->next;
            p->next = new Node;
            p->next->val = val;
            p->next->next = temp;
        } else {
            cin >> i;
            p = head;
            for (int j = 1; j < i; j++) {
                p = p->next;
            }
            // 删除结点
            Node* temp = p->next;
            p->next = p->next->next;
            delete temp;
        }
    }
    // 遍历输出
    p = head->next;
    while (p) {
        cout << ((p == head->next) ? "" : " ") << p->val;
        p = p->next;
    }
    cout << endl;
    return 0;
}
