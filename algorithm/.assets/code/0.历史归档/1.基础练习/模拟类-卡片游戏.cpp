/**
 * http://oj.csoeasy.com/problem.php?id=1158
 * 题目描述
 * 桌上有一叠牌，从第一张牌（即位于顶面的牌）开始从上往下依次编号为1~n。当至少还剩两张牌时进行以下操作：把第一张牌扔掉，然后把新的第一张放到整叠牌的最后。输入n,输出每次扔掉的牌，以及最后剩下的牌。
 *
 * 输入
 * 第一行为一个整数t（0<t<40），表示测试用例个数。以下t行每行包含一个整数n（0<n<40），为一个测试用例的牌数。
 *
 * 输出
 * 为每个测试用例单独输出一行，该行中依次输出每次扔掉的牌以及最后剩下的牌，每张牌后跟着一个空格。
 *
 * 样例输入
 * 2
 * 7
 * 4
 * 样例输出
 * 1 3 5 7 4 2 6
 * 1 3 2 4
 */

#include<iostream>

using namespace std;

int main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        int *queue = new int[n + 1];
        int hp = 0, tp = n, LEN = 1;
        // 编号1~N
//        generate_n(queue, n, [&LEN]() {
//            return LEN++;
//        });
        while (LEN <= n) {
            queue[LEN - 1] = LEN;
            LEN++;
        }

        // 模拟操作，直到队列为空
        while ((tp - hp + LEN) % LEN > 0) {
            // 取队头
            cout << queue[hp] << " ";
            // 队头后移一位
            hp = (hp + 1) % LEN;
            // 第二张放到队尾
            queue[tp] = queue[hp];
            tp = (tp + 1) % LEN;
            // 队头再后移一位
            hp = (hp + 1) % LEN;
        }
        cout << endl;
        delete[] queue;
    }
    return 0;
}