#include<iostream>
#include<cstring>
using namespace std;

// 重建先序序列
void rebuildProSeq(char *posSeq, char *midSeq, long len);

// 重建后序序列
void rebuildPosSeq(char *proSeq, char *midSeq, long len);

int main() {
    char proSeq[100] = "1247536";
    char midSeq[100] = "4725136";
    char posSeq[100] = "7452631";

    rebuildProSeq(posSeq, midSeq, strlen(midSeq));
    cout << endl << "==============================" << endl;
    rebuildPosSeq(proSeq, midSeq, strlen(midSeq));

    return 0;
}

void rebuildProSeq(char *posSeq, char *midSeq, long len) {
    if (len < 1) {
        return;
    }
    // 找到根结点在中序序列中的位置
    long p = strchr(midSeq, posSeq[len - 1]) - midSeq;
    // 访问根结点
    cout << posSeq[len - 1];
    // 重建左子树
    rebuildProSeq(posSeq, midSeq, p);
    // 重建右子树
    rebuildProSeq(posSeq + p, midSeq + p + 1, len - p - 1);
}

void rebuildPosSeq(char *proSeq, char *midSeq, long len) {
    if (len < 1) return;
    // 找到根结点在中序序列中的位置
    long p = strchr(midSeq, proSeq[0]) - midSeq;
    // 重建左子树
    rebuildPosSeq(proSeq + 1, midSeq, p);
    // 重建右子树
    rebuildPosSeq(proSeq + p + 1, midSeq + p + 1, len - p - 1);
    // 访问根结点
    cout << proSeq[0];
}