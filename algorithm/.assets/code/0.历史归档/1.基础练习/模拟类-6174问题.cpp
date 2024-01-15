/**
 * 【描述】
 * 假设你有一个各位数字互不相同的四位数，把所有的数字从大到小排序后得到a,从小到大后得到b,然后用a-b替换原来这个数，并且继续操作。
 * 例如，从1234出发，依次可以得4321-1234=3087、8730-378=8352、8532-2358=6174，又回到了它自己！现在要你写一个程序来判断一个四位数经过多少次这样的操作能出现循环，并且求出操作的次数.
 * 比如输入1234执行顺序是1234->3087->8352->6174->6174,输出是4,
 *
 * 【输入】
 * 第一行输入n,代表有n组测试数据。
 * 接下来n行每行都写一个各位数字互不相同的四位数
 *
 * 【输出】
 * 经过多少次上面描述的操作才能出现循环
 *
 * 【样例输入】
 * 1
 * 1234
 *
 * 【样例输出】
 * 4
 *
 */

#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;

int main() {
    string input;
    unordered_set<int> hashSet;
    int x, y, T;
    cin >> T;
    while (T--) {
        cin >> input;
        hashSet.clear();
        while (true) {
            // 取出顺序x
            sort(begin(input), end(input));
            x = (int)strtol(input.c_str(), nullptr, 10);
            if (hashSet.count(x)) {
                break;
            }
            // 记录x
            hashSet.insert(x);
            // 翻转
            reverse(begin(input), end(input));
            // 更新x到input
            y = (int)strtol(input.c_str(), nullptr, 10);
            x = y - x;
            stringstream ss;
            ss << x;
            input = ss.str();
        }
        cout << hashSet.size() << endl;
    }
    return 0;
}
