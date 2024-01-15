#include <iostream>
using namespace std;

// 递归方式 树深度：logN
int dfsBSearch(const int *arr, int key, int left, int right);

// 循环方式
int loopBSearch(const int *arr, int key, int left, int right);

int main() {
    // 先决条件：关键字有序
    int arr[10] = {12, 21, 23, 25, 54, 66, 75, 78, 95, 98};
    int key = 12;
    cout << dfsBSearch(arr, key, 0, 10) << endl;
    cout << loopBSearch(arr, key, 0, 10) << endl;

    key = 98;
    cout << dfsBSearch(arr, key, 0, 10) << endl;
    cout << loopBSearch(arr, key, 0, 10) << endl;

    key = 66;
    cout << dfsBSearch(arr, key, 0, 10) << endl;
    cout << loopBSearch(arr, key, 0, 10) << endl;

    key = 100;
    cout << dfsBSearch(arr, key, 0, 10) << endl;
    cout << loopBSearch(arr, key, 0, 10) << endl;
    return 0;
}

int dfsBSearch(const int *arr, int key, int left, int right) {
    if (left >= right) {
        return -1;
    }
    // 二分点，[left, right)
    int mid = left + (right - left) / 2;
    if (arr[mid] == key) {
        return mid;
    }
    // 搜索左区间
    if (arr[mid] > key) {
        return dfsBSearch(arr, key, left, mid);
    }
    // 搜索右区间
    if (arr[mid] < key) {
        return dfsBSearch(arr, key, mid + 1, right);
    }
    return -1;
}

int loopBSearch(const int *arr, int key, int left, int right) {
    int mid;
    do {
        // 二分点
        mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        // 缩小区间
        if (arr[mid] > key) {
            // 搜索左区间
            right = mid;
        } else {
            // 搜索右区间
            left = mid + 1;
        }
    } while (left < right);
    return -1;
}
