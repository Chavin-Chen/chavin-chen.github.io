/**
 * 求 a + b 组不成的最大数
 *
 * input:
 * 4 7
 *
 * output:
 * 17
 *
 * 组合数问题：a != b
 * a+b组不成最大数：a*b - a+b;
 * a+b组不成的数个数：(a-1) * (b-1)
 */

#include<iostream>

using namespace std;

#define MAX_N 1000005


int main() {
    int res[MAX_N];
    int a, b, ans;
    cin >> a >> b;

    // 初始化
    res[a] = res[b] = 1;
    ans = max(a, b) + 1;

    for (int i = ans; i < a * b; i++) {
        // 判断 i 是否可以通过 +a 或 +b的方式得到
        res[i] = (res[i - a] || res[i - b]) ? 1 : 0;
        // 如果i不能通过+a或+b的方式得到，就刷新结果
        if (!res[i]) {
            ans = max(ans, i);
        }
    }
    cout << ans << endl;
    return 0;
}
