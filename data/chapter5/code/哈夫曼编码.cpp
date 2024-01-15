#include<iostream>
#include <vector>
using namespace std;

struct Node {
    int weight;
    char data;
    int L, R;
    bool hasParent;

    Node() {
        hasParent = false;
        L = R = -1;
        weight = data = 0;
    }
};
// 找到权重最小的子树
int findMinWeightIndex(vector<Node *> arr);
// 先序方式遍历输出编码
void dfs(vector<Node *> array, size_t index, vector<int> pathStack);

// 8
// a 5 b 29 c 7 d 8 e 14 f 23 g 3 h 11
int main() {
    int n;
    vector<Node *> array;
    Node *node;
    // 输入统计数据
    cin >> n;
    for (int i = 0; i < n; i++) {
        node = new Node;
        cin >> node->data >> node->weight;
        array.push_back(node);
    }
    // 构建Haffman树
    for (int t = n; t > 1; t--) {
        int left = findMinWeightIndex(array);
        array[left]->hasParent = true;
        int right = findMinWeightIndex(array);
        array[right]->hasParent = true;

        node = new Node;

        node->L = left;
        node->R = right;
        node->weight = array[left]->weight + array[right]->weight;
        array.push_back(node);
    }
    dfs(array, array.size() - 1, vector<int>());
    return 0;
}

int findMinWeightIndex(vector<Node *> arr) {
    int minWeight = -1, ans = -1;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i]->hasParent) {
            continue;
        } else if (minWeight < 0 || arr[i]->weight < minWeight) {
            minWeight = arr[i]->weight;
            ans = i;
        }
    }
    return ans;
}

void dfs(vector<Node *> array, size_t index, vector<int> pathStack) {
    if (index == -1) {
        return;
    }
    // 如果是叶子结点（Haffman树的子结点数只能是0或2）
    if (array[index]->L == -1) {
        cout << array[index]->data << ": ";
        // 输出编码
        for (int i : pathStack) {
            cout << i;
        }
        cout << endl;
        return;
    }
    // 左子树
    pathStack.push_back(0);
    dfs(array, array[index]->L, pathStack);

    // 右子树
    pathStack.at(pathStack.size() - 1) = 1;
    dfs(array, array[index]->R, pathStack);

    pathStack.pop_back();
}