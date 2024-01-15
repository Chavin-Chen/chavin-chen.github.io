#include <cstdio>
int a[100] = {0, 3, 6, 6};
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 4; i <= n; i++) {
        a[i] = a[i - 2] * 2 + a[i - 1];
    }
    printf("%d\n", a[n]);
    return 0;
}
/*
RBG格子涂色,视为环状的格子相邻格子颜色相异,求涂色方式
input:
9
output:
510

*/
