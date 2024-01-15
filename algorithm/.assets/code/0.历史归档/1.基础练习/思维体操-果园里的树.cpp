/**
 * 题目：果园里的树排列成矩阵。它们的x和y坐标均是1~99的整数。输入若干个三角形，依次统计每一个三角形内部和边界上共有多少棵树
 *
 * 样例输入：
 * 1.5 1.5 1.5 6.8 6.8 1.5
 * 10.7 6.9 8.5 1.5 14.5 1.5
 *
 * 样例输出：
 * 15
 * 17
 *
 */
#include<iostream>
#include<cmath>

using namespace std;

/**
 * 求三角形有向面积
 */
double triangleArea(double x1, double y1, double x2, double y2, double x3, double y3);

int main() {
    double x1, x2, x3, y1, y2, y3;
    while (cin >> x1 >> x2 >> x3 >> y1 >> y2 >> y3) {
        int cnt = 0;
        // 求大三角形面积
        double s = triangleArea(x1, y1, x2, y2, x3, y3);
        double sV12, sV23, sV31;
        for (int i = 1; i < 100; i++) {
            for (int j = 1; j < 100; j++) {
                sV12 = triangleArea(i, j, x1, y1, x2, y2);
                sV23 = triangleArea(i, j, x2, y2, x3, y3);
                sV31 = triangleArea(i, j, x3, y3, x1, y1);
                // 如果大三角形面积 等于 三个小三角形面积之和，则点在内部或边上。
                if (fabs(s - sV12 - sV23 - sV31) < 1e-5) {
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}

double triangleArea(double x1, double y1, double x2, double y2, double x3, double y3) {
    // 三角形有向面积：s = x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3
    // s == 0, vi 三点共线
    // s > 0 则 v1,v2,v3呈逆时针排列
    // s < 0 则 v1,v2,v3呈顺时针排列
    return fabs(x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3);
}