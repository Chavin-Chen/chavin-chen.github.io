#include <iostream>
using namespace std;

class Array {
    int *arr, capacity;
    int ap;

    void check() {
        if (ap < capacity - 1) return;

        int *p = arr;  // 当容量还差一个到达极限时扩容
        arr = new int[2 * capacity]; // 增长因子为 2.0
        memcpy(arr, p, sizeof(int) * capacity);
        capacity *= 2;
        delete p;
    }

public:
    Array(int capacity) : capacity(capacity), arr(new int[capacity]), ap(0) {}

    void add(int val) {
        check(); // 添加元素前先检查容量
        arr[ap++] = val;
    }

    int length() {
        return ap;
    }

    int get(int i) {
        return arr[i];
    }
};