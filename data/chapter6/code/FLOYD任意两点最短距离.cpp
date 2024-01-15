#include<iostream>
using namespace std;

const int DIS_MAX = (1 << 31) - 1;
const int N = 8;

int dis[N][N] = {
        {0, 2, 3, 0, 0, 0, 0, 9},
        {2, 0, 0, 2, 4, 0, 0, 0},
        {3, 0, 0, 1, 0, 0, 1, 1},
        {0, 2, 1, 0, 0, 3, 1, 0},
        {0, 4, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 3, 2, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 2},
        {9, 0, 1, 0, 0, 0, 2, 0}
};

int main() {
    // 初始化距离：不邻接则置为MAX，x->x的距离置为0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!dis[i][j]) {
                dis[i][j] = (i == j) ? 0 : DIS_MAX;
            }
        }
    }

    int dI2K2J;
    // 找到一个中介点k，如果 dis(i->k>j) < dis(i->j) 则更新
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dI2K2J = dis[i][k] + dis[k][j];
                // 如果跟路径跟短，则更新
                if (dI2K2J >= 0 && dI2K2J < dis[i][j]) {
                    dis[i][j] = dI2K2J;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << dis[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
