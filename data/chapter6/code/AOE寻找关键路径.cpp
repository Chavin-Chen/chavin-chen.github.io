#include<iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;
const int N = 9;

// AOE网: v表示事件, e表活动, 权值是活动持续时间;
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

// 顶点，表示事件
struct Vertex {
    // 顶点编号
    int index;
    // 顶点的入度
    int inDegree;
    // 最早发生时间
    int earliest;
    // 最晚发生时间
    int latest;

    Vertex() {
        index = 0;
        inDegree = 0;
        earliest = latest = -1;
    }
};

// 边，表示活动
struct Edge {
    // 前驱事件，后继事件
    int vPro, vPos;
    // 边权重：活动持续时间
    int weight;

    // 最早发生时间 = 前驱事件最早发生时间
    int earliest;
    // 最晚发生时间 = 后继事件最晚发生时间 - 活动持续时间
    int latest;

    Edge(int pro, int pos, int w) {
        vPro = pro;
        vPos = pos;
        weight = w;
        earliest = latest = -1;
    }

    string toString() {
        return string("<") + to_string(vPro) + "," + to_string(vPos) + ">";
    }
};

// 构造事件（点集）的TOPO序列
vector<Vertex *> &buildVTopoSeq();

// 寻找关键活动（边集）：最早发生时间=最晚发生时间
vector<Edge *> &findKeyEdge(vector<Edge> &edges, vector<Vertex *> &vTopoSeq);

int main() {
    vector<Edge> edges;
    // 根据图初始化边集
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!graph[i][j]) {
                continue;
            }
            edges.emplace_back(i, j, graph[i][j]);
        }
    }

    // 构造TOPO序列
    vector<Vertex *> &vTopoSeq = buildVTopoSeq();

    // 查询关键活动
    vector<Edge *> &keyEdge = findKeyEdge(edges, vTopoSeq);

    // 输出所有关键活动
    for (Edge *&x: keyEdge) {
        cout << x->toString();
    }
    return 0;
}

vector<Vertex *> &buildVTopoSeq() {
    vector<Vertex *> vertexes;
    for (int i = 0; i < N; i++) {
        vertexes.push_back(new Vertex());
    }

    // 初始化顶点入度
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            vertexes[j]->index = j;
            if (0 == graph[i][j]) {
                continue;
            }
            vertexes[j]->inDegree++;
        }
    }

    // 0入度顶点入队列
    queue<Vertex *> aQueue;
    for (int i = 0; i < N; ++i) {
        if (0 != vertexes[i]->inDegree) {
            continue;
        }
        aQueue.push(vertexes[i]);
    }

    auto *topoSeq = new vector<Vertex *>();
    // BFS宽搜0入度顶点队列
    Vertex *v;
    while (!aQueue.empty()) {
        v = aQueue.front();
        aQueue.pop();

        // 加入topo序列
        topoSeq->push_back(v);

        // 清空v的出边并更新各顶点入度
        for (int i = 0; i < N; ++i) {
            if (!graph[v->index][i]) {
                continue;
            }
            vertexes[i]->inDegree--;
            // 0入度加入队列
            if (0 == vertexes[i]->inDegree) {
                aQueue.push(vertexes[i]);
            }
        }
    }
    return *topoSeq;
}

vector<Edge *> &findKeyEdge(vector<Edge> &edges, vector<Vertex *> &vTopoSeq) {
    // 构造事件的最早发生时间, 首事件的最早发生时间为0
    vTopoSeq[0]->earliest = 0;
    // i事件最早发生的时间 = MAX(前驱事件最早发生时间 + 活动持续时间)
    // 顺取topo序列,vEarliest[i]=其先决活动都发生完毕
    for (int i = 1; i < vTopoSeq.size(); i++) { 
        vTopoSeq[i]->earliest = -1;
        // 找出i的先决事件中完成最晚的
        for (int k = 0; k < i; k++) {
            if (!graph[k][i]) {
                continue;
            }
            if (-1 == vTopoSeq[i]->earliest) {
                vTopoSeq[i]->earliest = vTopoSeq[k]->earliest + graph[k][i];
            } else {
                vTopoSeq[i]->earliest = max(vTopoSeq[k]->earliest + graph[k][i],
                                                vTopoSeq[i]->earliest);
            }
        }
    }

    // 构造事件的最晚发生时间, 终事件的最晚发生时间等于其最早发生时间
    vTopoSeq[vTopoSeq.size() - 1]->latest = vTopoSeq[vTopoSeq.size() - 1]->earliest;
    // i事件的最晚发生时间 = MIN(后继事件的最晚发生时间 - 活动持续时间)
    for (int i = (int) vTopoSeq.size() - 2; i >= 0; i--) {
        vTopoSeq[i]->latest = -1;
        for (int k = (int) vTopoSeq.size() - 1; k > i; k--) {
            if (!graph[i][k]) {
                continue;
            }
            if (-1 == vTopoSeq[i]->latest) {
                vTopoSeq[i]->latest = vTopoSeq[k]->latest - graph[i][k];
            } else {
                vTopoSeq[i]->latest = min(vTopoSeq[k]->latest - graph[i][k],
                                                vTopoSeq[i]->latest);
            }
        }
    }

    auto *keyEdges = new vector<Edge *>();
    // 更新活动最早和最晚发生时间，记录刻不容缓的活动：最早发生时间=最晚发生时间
    for (auto &edge : edges) {
        // 活动i最早发生时间是其前驱事件最早开始时间
        edge.earliest = vTopoSeq[edge.vPro]->earliest;
        // 活动i最晚发生时间是其后继事件最晚发生时间 - 活动持续时间
        edge.latest = vTopoSeq[edge.vPos]->latest - edge.weight;

        // 关键活动：活动的最早发生时间 == 活动的最晚发生时间
        if (edge.earliest == edge.latest) {
            keyEdges->push_back(&edge);
        }
    }
    return *keyEdges;
}
