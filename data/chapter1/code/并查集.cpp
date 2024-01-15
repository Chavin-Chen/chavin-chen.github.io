#include <unordered_map>
using namespace std;

struct Dsu { // Disjoint Set Union
    int n;
    // 令arr[i]表示i元素所在集合的编号，集合根结点arr[root]=root
    unordered_map<int, int> arr;
    // 记录各集合中的元素个数
    unordered_map<int, int> dit; 

    Dsu(int n) : n(n), arr(unordered_map<int, int>()), dit(unordered_map<int, int>()) {}

    Dsu *add(int x) {
        if (0 != arr.count(x)) return this;
        arr.emplace(x, x);
        dit.emplace(x, 1);
        return this;
    }

    void merge(int x, int y) {
        int rX = find(x);
        int rY = find(y);
        if (rX == rY) return;
        // 启发式合并：将小集合并到大集合中
        if (dit[rX] > dit[rY]) swap(rX, rY);
        arr[rX] = rY;
        dit[rY] += dit[rX];
        dit.erase(rX);
    }

    int find(int x) {
        // 压缩路径，元素直接挂到集合根结点下
        return arr[x] == x ? x : arr[x] = find(arr[x]);
    }
};
