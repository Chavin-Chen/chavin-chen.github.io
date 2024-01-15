#include <cstring>
#include <iostream>
using namespace std;

// 查找子串t在主串s中的位置
int kmp(const char s[], const char t[]) {
    int sLen = (int)strlen(s), tLen = (int)strlen(t);
    int i, j;
    // 构建子串t的回溯数组next; next[0] = -1, j左(子串)i右(主串)，不断回溯子串j
    i = 0, j = -1;
    int* next = new int[tLen]{-1};
    while (i < tLen) {
        if (j == -1 || t[i] == t[j]) {  // 若回滚越界 或 发生匹配则移动下标
            ++i;
            ++j;
            if (t[i] != t[j]) {  // 当匹配时主串和子串的t[j]元素匹配失败时,子串回溯到t[i]位置继续和主串匹配
                next[i] = j;
            } else {  // 线索优化：若移动动后的元素相等，则复用左边元素的回溯位置
                next[i] = next[j];
            }
        } else {  // 不匹配则回滚左侧下标（左侧串相当于匹配时的子串）
            j = next[j];
        }
    }
    // 开始串匹配过程
    i = 0, j = -1;
    while (i < sLen && j < tLen) {  // 若子串已无法再回滚 或 发生匹配，则移动主串和子串
        if (j == -1 || s[i] == t[j]) {
            ++i;
            ++j;
        } else {  // 不匹配则子串回溯，主串不动
            j = next[j];
        }
    }
    delete[] next;
    if (j == tLen) {  // 若子串移到尽头，则说明主串中找到了子串
        return i - j;
    }
    return -1;
}

int main() {
    char s[100], t[100];
    while (cin >> s >> t) {
        cout << "pos : " << kmp(s, t) << endl;
    }
    return 0;
}