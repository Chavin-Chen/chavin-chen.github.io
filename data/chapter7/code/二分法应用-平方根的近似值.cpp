#include <iostream>
#include <iomanip>
using namespace std;

double bSearch(double left, double right, int val);

int main() {
    cout << setprecision(10) << bSearch(0, 3, 2) << endl;
    return 0;
}

// 零点定理：若f(x)在(a,b)区间单调，且f(a)*f(b)<0, 则f(x)在(a,b)区间有根
double bSearch(double left, double right, int val) {
    double mid;
    do {
        mid = left + (right - left) / 2;
        // f(mid) - val > 0; mid在根的右边
        if (mid * mid > val) {
            right = mid;
        } else {
            left = mid;
        }
    } while (right - left > 1E-10);
    return mid;
}
