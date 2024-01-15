/**
 * https://vjudge.net/problem/HDU-1279
 * 数论中有许多猜想尚未解决，其中有一个被称为“角谷猜想”的问题，该问题在五、六十年代的美国多个著名高校中曾风行一时，
 * 这个问题是这样描述的：任何一个大于一的自然数，如果是奇数，则乘以三再加一；如果是偶数，则除以二；
 * 得出的结果继续按照前面的规则进行运算，最后必定得到一。现在请你编写一个程序验证他的正确性。
 * 
 * Input
 * 本题有多个测试数据组，第一行为测试数据组数N，接着是N行的正整数。
 * 
 * Output
 * 输出验证“角谷猜想”过程中的奇数，最后得到的1不用输出；每个测试题输出一行；
 * 每行中只有两个输出之间才能有一个空格；如果没有这样的输出，则输出：No number can be output !。
 * 
 * Sample Input
 * 4
 * 5
 * 9
 * 16
 * 11
 * 
 * Sample Output
 * 5
 * 9 7 11 17 13 5
 * No number can be output !
 * 11 17 13 5
 * 
 */
#include<iostream>
#include <vector>

#define MAXN 1000
using namespace std;

int vis[MAXN];
vector<int> visVec[MAXN];

int dfs(int x, vector<int> &s) {
    if (x == 1) {
        return 0;
    }
    if (x < MAXN && 0 != vis[x]) {
        // 如果有记忆值，直接返回记忆值
        s.insert(s.end(), visVec[x].begin(), visVec[x].end());
        return vis[x];
    }
    int res;
    vector<int> resVec;
    if ((x & 1)) {
        // 如果是奇数
        res = dfs(3 * x + 1, resVec) + 1;
        resVec.insert(resVec.begin(), x);
    } else {
        // 如果是偶数
        res = dfs(x / 2, resVec) + 1;
    }
    // 必要时记录一下搜索结果
    if (x < MAXN) {
        vis[x] = res;
        visVec[x].insert(visVec[x].end(), resVec.begin(), resVec.end());
    }
    s.insert(s.begin(), resVec.begin(), resVec.end());
    return res;
}

int main() {
    vector<int> vec;
    int T, x;
    cin >> T;
    while (T--) {
        cin >> x;
        vec.clear();
        dfs(x, vec);
        if (vec.empty()) {
            cout << "No number can be output !";
        } else {
            for (int i = 0; i < vec.size(); i++) {
                cout << (i == 0 ? "" : " ") << vec[i];
            }
        }
        cout << endl;
    }
    return 0;
}
