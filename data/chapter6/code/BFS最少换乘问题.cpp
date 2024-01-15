#include<iostream>
#include<queue>
using namespace std;

const int N = 8;
bool vis[N];
int g[N][N] = {
        {0, 2, 3, 0, 0, 0, 0, 9},
        {2, 0, 0, 2, 4, 0, 0, 0},
        {3, 0, 0, 1, 0, 0, 1, 1},
        {0, 2, 1, 0, 0, 3, 1, 0},
        {0, 4, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 3, 2, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 2},
        {9, 0, 1, 0, 0, 0, 2, 0}
};
queue<int> aQueue;

// 迷宫最短路问题（路径定长）
// 最小换乘问题
int main() {
    // 起点入队
    vis[0] = true;
    aQueue.push(0);
    while (!aQueue.empty()) {
        int x = aQueue.front();
        aQueue.pop();
        cout << x << " ";
        // 找到所有可达的顶点，入队
        for (int i = 0; i < N; i++) {
            if (!vis[i] && g[x][i]) {
                aQueue.push(i);
                vis[i] = true;
            }
        }
    }
    return 0;
}
