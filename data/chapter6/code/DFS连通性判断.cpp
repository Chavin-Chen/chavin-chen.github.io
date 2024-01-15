#include<iostream>
using namespace std;

bool vis[100];
int graph[100][100];

int dfs(int k, int n);


// 9
// 0 6 4 5 0 0 0 0 0
// 0 0 0 0 1 0 0 0 0
// 0 0 0 0 1 0 0 0 0
// 0 0 0 0 0 2 0 0 0
// 0 0 0 0 0 0 9 7 0
// 0 0 0 0 0 0 0 4 0
// 0 0 0 0 0 0 0 0 2
// 0 0 0 0 0 0 0 0 4
// 0 0 0 0 0 0 0 0 0
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    if (dfs(0, n) == n) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}

int dfs(int k, int n) {
    if (vis[k]) {
        return 0;
    }
    vis[k] = true;
    int cnt = 1;
    // 找到任意可达的顶点，并一直搜索下去
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        if (!graph[k][i] && !graph[i][k]) {
            continue;
        }
        cnt += dfs(i, n);
    }
    return cnt;
}
