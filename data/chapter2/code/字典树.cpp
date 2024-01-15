#include<iostream>
using namespace std;

struct Trie {
    int node[500005][26], cnt;
    int ended[500005];// 标记某个节点是否可作为串终点

    void add(string &s) {
        int parent = 0;
        for (int i = 0, ch; i < s.length(); i++) {
            ch = s[i] - 'a';
            if (0 == node[parent][ch]) { // 如果没有，就添加结点
                node[parent][ch] = ++cnt;
            }
            parent = node[parent][ch];
        }
        ended[parent] = true;
    }

    int find(string &s) {  // 查找字符串
        int parent = 0;
        for (int i = 0, ch; i < s.length(); i++) {
            ch = s[i] - 'a';
            if (0 == node[parent][ch]) {
                return false;
            }
            parent = node[parent][ch];
        }
        return ended[parent];
    }
};

int main() {
    Trie trie{};
    int n, m;
    ios::sync_with_stdio(false);
    string s;
    cin >> n;
    while (n--) {
        cin >> s;
        trie.add(s);
    }
    cin >> m;
    while (m--) {
        cin >> s;
        n = trie.find(s);
        switch (n) {
            case 0:
                cout << "None" << endl;
                continue;
            case 1:
                cout << "First" << endl;
                continue;
            default:
                cout << "Repeat" << endl;
        }
    }
    return 0;
}