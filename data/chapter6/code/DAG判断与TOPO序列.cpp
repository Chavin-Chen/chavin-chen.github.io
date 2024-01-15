#include<iostream>
#include<queue>
using namespace std;

const int N = 9;
int graph[N][N] = {
        {0, 6, 4, 5, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 9, 7, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void kahn();

void dfs();

bool dfs4DAG(int k, int *vis);

void dfs4Topo(int k, int *vis, vector<int> &topo);

int main() {
    // 深度搜索找TOPO序
    dfs();

    // 宽度搜索找TOPO序
    kahn();

    return 0;
}

void dfs() {
    int *vis = new int[N]{};
    bool isDAG = true;
    // 先通过DFS判断是否是DAG：O(V)
    for (int i = 0; i < N && isDAG; i++) {
        if (vis[i]) {
            continue;
        }
        isDAG &= dfs4DAG(i, vis);
    }
    if (!isDAG) {
        cout << "NO" << endl;
        return;
    }
    // 如果是DAG再通过DFS找出TOPO序列：O(E)
    vis = new int[N]{};
    vector<int> topo;
    //遍历每个顶点
    for (int i = 0; i < N; i++) {
        if (vis[i]) {
            continue;
        }
        dfs4Topo(i, vis, topo);
    }
    // 逆序输出则为TOPO序
    while (!topo.empty()) {
        cout << topo.back() << " ";
        topo.pop_back();
    }
    cout << endl << "DAG" << endl;
}

bool dfs4DAG(int k, int *vis) {
    if (0 != vis[k]) {
        return true;
    }
    // 标记正在访问
    vis[k] = 1;
    for (int i = 0; i < N; i++) {
        if (!graph[k][i]) {
            continue;
        }
        // 如果k出边可达i，且i正在访问，则存在环。
        if (1 == vis[i]) {
            cout << " :: " << i << endl;
            return false;
        }
        // i未在访问，则继续搜索
        if (0 == vis[i]) {
            if (!dfs4DAG(i, vis)) {
                return false;
            }
        }
    }
    // 标记已经访问过了
    vis[k] = 2;
    return true;
}

void dfs4Topo(int k, int *vis, vector<int> &topo) {
    vis[k] = 1;
    // 找到一个没访问过，且 k->i 顶点
    for (int i = 0; i < N; i++) {
        if (vis[i] || !graph[k][i]) {
            continue;
        }
        dfs4Topo(i, vis, topo);
    }
    // 加k到栈中（逆序）
    topo.push_back(k);
}


void kahn() {
    int inDegree[N] = {};
    queue<int> aQueue;
    int visCnt = 0, t;

    // 初始化入度记录 O(V^2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inDegree[j] += graph[i][j] ? 1 : 0;
        }
    }

    // 把入度为0的顶点入队列
    for (int i = 0; i < N; i++) {
        if (0 == inDegree[i]) {
            aQueue.push(i);
        }
    }
    while (!aQueue.empty()) {
        t = aQueue.front();
        cout << t << " ";
        aQueue.pop();
        visCnt++;
        // 找到从 t -> i的边去掉，则i的入度减1
        for (int i = 0; i < N; i++) {
            if (!graph[t][i]) {
                continue;
            }
            inDegree[i]--;
            // 如果i入度为0了，则加入到队列
            if (0 == inDegree[i]) {
                aQueue.push(i);
            }
        }
    }
    cout << endl << ((visCnt == N) ? "DAG" : "NO") << endl;
}