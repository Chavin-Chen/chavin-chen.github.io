#include<iostream>
using namespace std;

int split(int *arr, int k, int left, int right) {
    if (left + 1 == right)return arr[left];
    int i = left, j = right - 1, e = arr[left];
    while (i < j) {
        while (i < j && arr[j] >= e)j--;
        arr[i] = arr[j];
        while (i < j && arr[i] <= e)i++;
        arr[j] = arr[i];
    }
    arr[i] = e;

    if (k == i + 1) {
        return e;
    } else if (k < i + 1) {
        return split(arr, k, left, i);
    } else {
        return split(arr, k, i + 1, right);
    }
}

// input:
// 7 3
// 15 23 24 11 5 65 4
// output:
// 11
int main() {
    ios::sync_with_stdio(false);
    int *arr, n, k;
    cin >> n >> k;
    arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << split(arr, k, 0, n) << endl;
    return 0;
}