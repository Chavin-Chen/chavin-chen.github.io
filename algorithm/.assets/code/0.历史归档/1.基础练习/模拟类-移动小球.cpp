/**
 * https://vjudge.net/problem/HRBUST-1652
 * 给你n个小球，从左到右编号依次为1,2,3,4,5,6.........n，并规定小球1的左边的球号为n，小球n的右边的球号为1.现在有以下3种操作：A x y表示把编号为x小球移动到编号为y的小球的左边，B x y表示把编号为x小球移动到编号为y的小球的右边，Q 1 m为询问编号为m的小球右边的球号，Q 0 m为询问编号为m的小球左边的球号。
 * Input
 * 第一行有一个整数n(0<n<10000),表示有n组测试数据，随后每一组测试数据第一行是两个整数N,M，其中N表示球的个数(1<N<10000)，M表示操作的的次数(0<M<10000)。
 * 随后的M行，每行有三个数 s x y，s表示操作的类型，x，y为小球号。当s为Q时，若x为1，则询问小球y右边的球号，x为0，则询问小球y左边的球号。
 * Output
 * 输出每次询问的球号。
 * Sample Input
 * 1
 * 6 3
 * A 1 4
 * B 3 5
 * Q 1 5
 * Sample Output
 * 3
 */

#include<iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node *L;
    Node *R;

    Node() {
        val = 0;
        L = R = nullptr;
    }
};

int main() {
    Node *head = new Node;
    Node *ap, *bp;
    vector<Node *> nodes;
    int T, n, m, a, b;
    string s;

    cin >> T;
    while (T--) {
        for (Node *p:nodes) {
            delete p;
        }
        nodes.clear();
        // nodes[0] == nullptr
        nodes.push_back(bp = nullptr);
        ap = head;

        cin >> n >> m;
        // 构造环
        for (int i = 1; i <= n; i++) {
            ap = (ap->R = new Node);
            ap->val = i;
            nodes.push_back(ap);
            if (nullptr != bp) {
                ap->L = bp;
            }
            bp = ap;
        }
        ap->R = head->R;
        head->R->L = ap;

        // 执行操作
        while (m--) {
            cin >> s >> a >> b;
            if ('Q' == s[0]) {
                ap = nodes[b];
                ap = (0 == a) ? ap->L : ap->R;
                cout << ap->val << endl;
                continue;
            }
            ap = nodes[a];
            bp = nodes[b];
            // 取出a
            ap->L->R = ap->R;
            ap->R->L = ap->L;
            if ('A' == s[0]) {
                ap->L = bp->L;
                ap->R = bp;
                bp->L->R = ap;
                bp->L = ap;
            } else {
                ap->R = bp->R;
                bp->R->L = ap;
                ap->L = bp;
                bp->R = ap;
            }
        }
    }
    return 0;
}