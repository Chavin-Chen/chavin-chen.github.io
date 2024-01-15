#include<iostream>
using namespace std;

const int N = 8;

int graph[8][8] = {
        {0, 2, 3, 0, 0, 0, 0, 9},
        {2, 0, 0, 2, 4, 0, 0, 0},
        {3, 0, 0, 1, 0, 0, 1, 1},
        {0, 2, 1, 0, 0, 3, 1, 0},
        {0, 4, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 3, 2, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 2},
        {9, 0, 1, 0, 0, 0, 2, 0}
};
bool vis[8];
// dis[i] 表示从起点到i顶点的距离
int dis[8];

void dijkstra(int v);

int main() {
    dijkstra(0);
    for (int i = 1; i < N; i++) {
        cout << "0->" << i << " : " << dis[i] << endl;
    }
    return 0;
}

void dijkstra(int v) {
    vis[v] = true;
    for (int i = 0; i < N; i++) {
        dis[i] = graph[v][i] ? graph[v][i] : -1;
    }
    int minDis, k;

    for (int t = 1; t < N; t++) {
        k = minDis = -1;
        // 找到一个距离起点v最近的顶点k
        for (int i = 0; i < N; i++) {
            if (vis[i]) {
                continue;
            }
            if (minDis > 0 && dis[i] > minDis) {
                continue;
            }
            minDis = dis[i];
            k = i;
        }
        if (k < 0) {
            continue;
        }
        vis[k] = true;
        // 刷新一下所有可以途径k到达起点v的顶点 到起点的距离dis[i]
        for (int i = 0; i < N; i++) {
            if (0 == graph[k][i]) {
                continue;
            }
            if (dis[i] >= 0 && dis[i] < dis[k] + graph[k][i]) {
                continue;
            }
            // 如果 v -> k -> i 路径更短，则更新dis[i]
            dis[i] = dis[k] + graph[k][i];
        }

    }
}