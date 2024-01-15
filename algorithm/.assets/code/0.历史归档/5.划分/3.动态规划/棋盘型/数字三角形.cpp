#include<cstdio>
#include<algorithm>

int a[101][101];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            a[i][j] += std::max(a[i + 1][j], a[i + 1][j + 1]);
        }
    }
    printf("%d\n", a[0][0]);
    return 0;
}
/*
往左下或者右下
input:
5
13
11 8
12 7 26
6 14 15 8
12 7 13 24 11
output:
86

*/
