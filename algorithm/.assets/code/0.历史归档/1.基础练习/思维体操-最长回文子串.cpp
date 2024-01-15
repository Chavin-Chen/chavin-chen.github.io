/**
 * https://vjudge.net/problem/51Nod-1088
 * 输入一个字符串Str，输出Str里最长回文子串的长度。
 *
 * 回文串：指aba、abba、cccbccc、aaaa这种左右对称的字符串。
 *
 * 串的子串：一个串的子串指此（字符）串中连续的一部分字符构成的子（字符）串
 * 例如 abc 这个串的子串：空串、a、b、c、ab、bc、abc
 *
 * Input
 * 输入Str（Str的长度 <= 1000)
 *
 * Output
 * 输出最长回文子串的长度L。
 *
 * Sample Input
 * daabaac
 *
 * Sample Output
 * 5
 */
#include<iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    int maxLen = 0;
    // 以i为中心，前后比较
    for (int i = 0; i < s.size(); i++) {
        // Len=Odd
        for (int j = 0; i - j >= 0 && i + j < s.size(); j++) {
            if (s[i - j] != s[i + j]) {
                break;
            }
            if (2 * j + 1 > maxLen) {
                maxLen = 2 * j + 1;
            }
        }
        // Len=Even
        for (int j = 1; i - j + 1 >= 0 && i + j < s.size(); j++) {
            if (s[i - j + 1] != s[i + j]) {
                break;
            }
            if (2 * j > maxLen) {
                maxLen = 2 * j;
            }
        }
    }
    cout << maxLen << endl;
    return 0;
}
