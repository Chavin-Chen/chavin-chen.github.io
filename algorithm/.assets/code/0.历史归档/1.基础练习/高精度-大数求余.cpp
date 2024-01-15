/**
 * 对于高精度的大数N，求其除以M的余数。
 * 其中N的位数不超过 10000 位，0 < M < 2^63 - 1
 */
#include <iostream>

using namespace std;

int main() {
    string input;
    long long mod, ans = 0;
    cin >> input >> mod;
    // 同余定理：
    // 若`a≡b(mod m)，c≡d(mod m)`，则`a±c≡b±d(mod m)`
    // 若`a≡b(mod m)，c≡d(mod m)`，则`a*c≡b*d(mod m)`
    for (char i : input) {
        ans = ans * 10 + (i - '0');
        ans = ans % mod;
    }
    cout << ans << endl;
    return 0;
}
