/**
 * 找出所有 AABB 形式的完全平方数。
 */
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    int a, b;
    // 枚举AB
    for (a = 1; a < 10; a++) {
        for (b = 0; b < 10; b++) {
            // 构造数据
            int n = 1100 * a + 11 * b;
            // 判断是否满足条件
            int m = sqrt(n);
            if (m * m == n) {
                cout << n << " : " << m << endl;
            }
        }
    }
    return 0;
}
