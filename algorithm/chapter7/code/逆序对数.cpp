#include<iostream>
using namespace std;

int tmp[100];

int mergeCount(int *arr, int left, int right) {
    if (left + 1 == right) {
        return 0;
    }
    int mid = left + (right - left) / 2;
    int i = left, j = mid, k = left;
    int ans = 0;
    ans += mergeCount(arr, left, mid);
    ans += mergeCount(arr, mid, right);
    while (i < mid || j < right) {
        if (j >= right || (i < mid && arr[i] <= arr[j])) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            ans += mid - i;
        }
    }
    for (i = left; i < right; i++) {
        arr[i] = tmp[i];
    }
    return ans;
}

//input:
//7
//14 51 23 21 16 95 10
//14
//51 23 21 16 95 10 14 51 23 21 16 95 10 12
//output:
//12
//54
int main() {
    ios::sync_with_stdio(false);
    int *arr, n;
    while (cin >> n) {
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << mergeCount(arr, 0, n) << endl;
    }
    return 0;
}
