#include <iostream>
using namespace std;

int main() {
    int N, x, *queue, ap, cnt, c;
    cin >> N >> x;
    // 给M给人编号1~N
    queue = new int[N + 1];
    for (int i = 0; i < N; i++) queue[i] = i + 1;
    ap = 0;
    cnt = N;
    // 从1号开始往下数，每数到X出列，直到只剩下1个人
    for (c = 0; cnt > 1; ap = (ap + 1) % N) {
        if (!queue[ap]) continue; // 忽略已经移除的
        // 数到X了，该成员出列
        if (++c == x) {
            queue[ap] = 0;
            cnt--;
            c = 0;
        }
    }
    // 找到队列中没被剔除的编号
    for (int i = 0; i < N; i++) {
        if (!queue[i]) {
            continue;
        }
        cout << queue[i] << endl;
        break;
    }
    return 0;
}