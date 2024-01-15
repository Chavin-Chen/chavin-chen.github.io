/**
 * https://vjudge.net/problem/HDU-1878
 * 欧拉回路是指不令笔离开纸面，可画过图中每条边仅一次，且可以回到起点的一条回路。现给定一个图，问是否存在欧拉回路？
 * Input
 * 测试输入包含若干测试用例。每个测试用例的第1行给出两个正整数，分别是节点数N ( 1 < N < 1000 )和边数M；随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个节点的编号（节点从1到N编号）。当N为0时输入结
 * 束。
 * Output
 * 每个测试用例的输出占一行，若欧拉回路存在则输出1，否则输出0。
 * Sample Input
 * 3 3
 * 1 2
 * 1 3
 * 2 3
 * 3 2
 * 1 2
 * 2 3
 * 0
 * Sample Output
 * 1
 * 0
 *
 * 【附】一笔画问题（七桥问题）
 * 如果图G中的一个路径包括每个边恰好一次，则该路径称为欧拉路径(Euler path)。
 * 如果一个回路是欧拉路径，则称为欧拉回路(Euler circuit)。
 * 具有欧拉回路的图称为欧拉图（简称E图）。具有欧拉路径但不具有欧拉回路的图称为半欧拉图。
 *
 * 无向图判定
 * 1. 若无孤立点的无向图 G 为欧拉图，当且仅当图 G 连通且所有顶点的度都是偶数。
 * 2. 若如果无向连通图有 2k 个奇顶点，则图 G 可以用 k 条路径将图 G 的每一条边经过 一次，且至少要使用 k 条路径。
 * 3. 若无孤立点的无向图 G 为半欧拉图，当且仅当图 G 连通且 G 的奇顶点个数为 2 。 此时两个奇顶点分别为欧拉路径的起点和终点。
 * 
 * 有向图判定
 * 1. 若无孤立点的有向图 G 为欧拉图，当且仅当图 G 弱连通（无向基图连通）且所有顶点的入度等于出度。
 * 2. 若对于连通有向图，所有顶点入度与出度差的绝对值之和为 2k ，则图 G 可以用 k 条路径将图 G 的每一条边经过一次，且至少要使用 k 条路径。
 * 3. 若无孤立点的有向图 G 为半欧拉图，当且仅当图 G 弱连通，且恰有一个顶点 u 入度比出度小 1 ，一个顶点 v 入度比出度大 1 ，其余顶点入度等于出度。
 *    此时存在 u 作为起点， v 作为终点的欧拉路径。
 */
#include<iostream>

using namespace std;

// 并查集查找
int optFind(int *uSet, int x);

// 并查集联合
int optUnion(int *uSet, int a, int b);

int main() {
    int n, m, a, b;
    while (true) {
        cin >> n;
        if (0 == n) {
            break;
        }
        int *degree = new int[n + 1];
        // 并查集
        int *uSet = new int[n + 1];
        for (int i = 0; i < n + 1; i++) {
            uSet[i] = i;
            degree[i] = 0;
        }
        cin >> m;
        int vCnt = 0;
        while (m--) {
            cin >> a >> b;
            degree[a]++;
            degree[b]++;
            vCnt += optUnion(uSet, a, b);
        }
        // 先判断图连通
        if (vCnt != n - 1) {
            // 若图不连通，则无欧拉回路
            cout << 0 << endl;
        } else {
            // 对于无向连通图，存在欧拉回路的条件是：所有顶点的度为偶数
            bool isOk = true;
            for (int i = 1; i <= n; i++) {
                // 若存在奇数度顶点，则无欧拉回路
                if (degree[i] & 1) {
                    isOk = false;
                    break;
                }
            }
            cout << (int) isOk << endl;
        }
        delete[]degree;
        delete[]uSet;
    }
    return 0;
}

int optFind(int *uSet, int x) {
    return uSet[x] == x ? x : uSet[x] = optFind(uSet, uSet[x]);
}

int optUnion(int *uSet, int a, int b) {
    a = optFind(uSet, a);
    b = optFind(uSet, b);
    if (a == b) {
        return 0;
    }
    uSet[a] = b;
    return 1;
}