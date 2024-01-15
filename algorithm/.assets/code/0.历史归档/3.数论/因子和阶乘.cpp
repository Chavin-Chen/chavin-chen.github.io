/**
 * 题目：输入正整数n（2≤n≤100），把阶乘n!=1*2*3*...*n分解成素因子相乘的形式，从小到大输出各个素数（2、3、5...）的指数。
 * 例如，5! 表示为 3 1 1（5!=23*31*51=120），程序忽略比最大素因子更大的素数（否则末尾会有无穷多个0）
 *
 * 样例输入：
 * 5
 * 53
 *
 * 样例输出：
 * 5! = 3 1 1
 * 53! = 49 23 12 8 4 4 3 2 2 1 1 1 1 1 1 1
 */

#include<iostream>
#include<vector>
#include<map>
#include <unordered_set>

using namespace std;

// 素数打表
void initPrimes(vector<int> &primes, int n);

int main() {
    vector<int> primes;
    int n;
    map<int, int> ans;

    // 初始化素数表
    initPrimes(primes, 100);

    while (cin >> n) {

        ans.clear();
        // 1...n 模拟阶乘
        for (int i = 1, temp; i <= n; i++) {
            temp = i;
            // 遍历素数表
            for (int j = 0; j < primes.size(); j++) {
                // 一直除直到不能整除
                while (0 == (temp % primes[j])) {
                    if (ans.find(j) != ans.end()) {
                        ans[j]++;
                    } else {
                        ans.emplace(j, 1);
                    }
                    temp /= primes[j];
                }
            }
        }

        // 输出素数表的指数
        cout << n << "! = ";
        for (int i = 0; i < ans.size(); i++) {
            cout << (i == 0 ? "" : " ") << ans.at(i);
        }
        cout << endl;
    }
    return 0;
}

void initPrimes(vector<int> &primes, int n) {
    unordered_set<int> nonPrime;
    for (int i = 2; i <= n; i++) {
        // 若i不是合数，则添加到素数队列
        if (nonPrime.find(i) == end(nonPrime)) {
            primes.push_back(i);
        }
        // 筛掉非素数
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
            // 当前数i和已找到的素数的积肯定是非质数
            nonPrime.insert(i * primes[j]);
            // 若当前数i不是素数则没有必要再筛了（一下假设 a,b,c均为素数且 a<b<c）
            // 假设 i == a * b, 当前素数为b, 就没有必要再筛 (a*b)*c 了
            // 因为 a*b*c 会在 素数为a,i=b*c 的时候被筛掉
            if (0 == (i % primes[j])) {
                break;
            }
        }
    }
}