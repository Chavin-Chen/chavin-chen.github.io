#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

void desc();

int main() {
    int n, i = 3, e;
    cin >> n;
    int *arr = new int[n + 4]{22, 16, 11};
    make_heap(arr, arr + 3, greater<>()); // 初始化小根堆
    while (n--) {
        cin >> e;
        arr[i++] = e;
        push_heap(arr, arr + i, greater<>()); // 插入元素后调整堆:尾元素上浮
    }
    cout << "is heap:" << is_heap(arr, arr + i, greater<>()) << endl;
    while (i >= 1) {
        pop_heap(arr, arr + i, greater<>()); // 移除元素后调整堆: 根元素下沉
        cout << arr[--i] << endl;
    }
    // 上述循环部分等同于
//    sort_heap(arr, arr + i, greater<>());
//    while (i > 0) cout << arr[--i] << endl;
    return 0;
}

void desc() { // STL在头文件<queue>中封装有priority_queue<T>堆适配器
    priority_queue<int, vector<int>, less<>> q;
    int n, e;
    cin >> n;
    while (n--) {
        cin >> e;
        q.emplace(e);
    }
    while (!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
}