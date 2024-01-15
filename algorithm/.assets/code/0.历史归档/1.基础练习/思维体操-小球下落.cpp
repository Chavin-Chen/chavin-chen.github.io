/**
 * 小球下落:
 * 有一颗二叉树,做大的深度为D,所有叶子的深度都相同,所有节点从上到下从左到右的编号为 1,2,3,4....2^(D-1)
 * 在节点1处放一个小球,他会往下落,每个内节点上都有一个开关,初始化的时候都是关着的,当每次有小球落到一个开关的时候,他的状态就会变化,
 * 当小球到达一个内节点的时候,如果开关是关闭的,就往左走,否则就往右走,直到走到叶子节点。
 *
 * 输入D表示二叉树的深度,在输入I表示第几个小球（D <= 20 输入最多包含1000组数据）；
 *
 * 输出第I个小球最后落入的叶子节点数目。
 *
 *
 * 样式输入：
 * 4 2
 * 3 4
 * 10 1
 * 2 2
 * 8 128
 * 16 12345
 * 样式输出：
 * 12
 * 7
 * 512
 * 3
 * 255
 * 36358
 *
 * 提示：注意比较两种解法的时空复杂度
 */

#include<iostream>

using namespace std;

void funOne(int, int);

void funTwo(int, int);

int main() {
    int deep, i;
    while (cin >> deep >> i) {
        funOne(deep, i);
        funTwo(deep, i);
    }
    return 0;
}

void funOne(int deep, int i) {
    int tree[1 << deep];
    int curDeep = 1, curNode = 1;
    memset(tree, 0, sizeof(tree));
    // 模拟小球 1~i
    for (int j = 1; j <= i; j++) {
        curDeep = 1;
        curNode = 1;
        // 模拟掉落深度
        while (curDeep++ <= deep) {
            tree[curNode] = !tree[curNode];
            if (0 == tree[curNode]) {
                // 如果之前开关打开，就往右边走
                curNode = curNode * 2 + 1;
            } else {
                // 开关关闭往左边走
                curNode *= 2;
            }
        }
    }
    cout << curNode / 2 << endl;
}

void funTwo(int deep, int i) {
    int curNode = 1;
    // 模拟深度
    for (int d = 1; d < deep; d++) {
        if (i & 1) {
            // 如果当前是奇数号小球则经过i-1次切换后，d层状态为关（往左子树掉）
            curNode = curNode * 2;
            i = (i + 1) / 2;
        } else {
            // 如果当前是偶数号小球则经过i-1次切换后，d层状态为开（往右子树掉）
            curNode = curNode * 2 + 1;
            i /= 2;
        }
    }
    cout << curNode << endl;
}