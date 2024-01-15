#include<iostream>

using namespace std;

int dfs(int x, int y, int mod) {
    if (0 == y) {
        return 1;
    }
    int tmp = dfs(x, y / 2, mod);//x^(y/2)
    if (y & 1) { // odd: t*t*x
        return (((x * tmp) % mod) * tmp) % mod;
    } else { // even: t*t
        return (tmp * tmp) % mod;
    }

}

int main() {
    ios::sync_with_stdio(false);
    int x, y;
    cin >> x >> y;
    cout << dfs(x, y, 1E7 + 7) << endl;
    return 0;
}