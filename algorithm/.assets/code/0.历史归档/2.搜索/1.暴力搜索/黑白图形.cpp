/**
 * 图形中有两种颜色:黑（1）和 白（0）
 * 求图形中共有几个黑色块相连的区域
 * 
 * input:
 * 6
 * 1 0 0 1 0 0
 * 0 0 1 0 1 0
 * 0 0 0 0 0 0
 * 1 1 0 0 0 0
 * 1 1 1 0 0 0
 * 0 1 0 1 0 0
 * output:
 * 3
 * 
 */
#include<iostream>

using namespace std;
int graph[100][100];

void dfs(int x, int y) {
    if (graph[x][y] <= 0)return;
    // 标记为已访问
    graph[x][y] = -1;
    // 左上
    dfs(x - 1, y - 1);
    // 正上
    dfs(x - 1, y);
    // 右上
    dfs(x - 1, y + 1);
    // 正右
    dfs(x, y + 1);
    // 右下
    dfs(x + 1, y + 1);
    // 正下
    dfs(x + 1, y);
    // 左下
    dfs(x + 1, y - 1);
    // 正左
    dfs(x, y - 1);
}

int main() {
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> graph[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 如果已访问或非黑块
            if (graph[i][j] <= 0) {
                continue;
            }
            ans++;
            dfs(i, j);
        }
    }
    cout << ans << endl;
    return 0;
}
/*

*/
