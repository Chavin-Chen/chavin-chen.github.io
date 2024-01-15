#include<iostream>
#include<queue>
using namespace std;

const int N = 8;
bool vis[N];
int graph[N][N] = {
        {0, 2, 3, 0, 0, 0, 0, 9},
        {2, 0, 0, 2, 4, 0, 0, 0},
        {3, 0, 0, 1, 0, 0, 1, 1},
        {0, 2, 1, 0, 0, 3, 1, 0},
        {0, 4, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 3, 2, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 2},
        {9, 0, 1, 0, 0, 0, 2, 0}
};

int prim();

int kruskal();

int main() {
    cout << prim() << endl;

    cout << kruskal() << endl;
    return 0;
}


int prim() {
    int weightCnt = 0;
    int minWeight, targetV;
    // 初始化子图
    vis[0] = true;
    // 一共N-1个顶点
    for (int t = 1; t < N; t++) {
        minWeight = -1, targetV = -1;
        // 找一个不在子图中的顶点 i
        for (int i = 0; i < N; i++) {
            if (vis[i]) {
                continue;
            }
            // 再找到它和当前的子图最短边 (i,j)
            for (int j = 0; j < N; j++) {
                if (!vis[j] || 0 == graph[j][i]) {
                    continue;
                }
                if ((minWeight < 0 || graph[j][i] < minWeight)) {
                    minWeight = graph[j][i];
                    targetV = i;
                }
            }
        }
        // 用这条最短边把点 targetV 加入到子图中
        vis[targetV] = true;
        weightCnt += minWeight;
    }
    return weightCnt;
}

int parent[8];

// 并查集
int dsu(int k) {
    return k == parent[k] ? k : parent[k] = dsu(parent[k]);
}

int kruskal() {
    // 初始化并查集
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }
    int weightCnt = 0;
    int minWeight = -1, x, y;
    // 共需要 N-1 条边
    for (int t = 1; t < N; t++) {
        minWeight = -1;
        x = y = -1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (0 == graph[i][j]) {
                    continue;
                }
                if (dsu(i) == dsu(j)) {
                    continue;
                }
                if (minWeight >= 0 && graph[i][j] >= minWeight) {
                    continue;
                }
                // 找到了一条连通两个不同子图，且权重最小的边
                minWeight = graph[i][j];
                x = i;
                y = j;
            }
        }
        if (x < 0 || y < 0) {
            continue;
        }
        // 用着条最小的边，把顶点x和y连通到一个子图中
        parent[dsu(y)] = dsu(dsu(x));
        weightCnt += minWeight;
    }
    return weightCnt;
}