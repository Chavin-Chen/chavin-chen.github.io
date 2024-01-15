/**
 * 输入一个字典（用******结尾），然后再输入若干单词。
 * 每输入一个单词w，你都需要在字典中找出所有可以用w的字母重排后得到的单词，并按照字典序从小到大的顺序在一行中输出（如果不存在，输出:(）。
 * 输入单词之间用空格或空行隔开，且所有输入单词都由不超过6个小写字母组成。注意，字典中的单词不一定按字典序排列。
 *
 * 样例输入：
 * tarp given score refund only trap work earn course pepper part
 * ******
 * resco nfudre aptr sett oresuc
 *
 * 样例输出：
 * score
 * refund
 * part trap trap
 * :(
 * course
 */

#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;


int main() {
    char sorted[100][10] = {}, origin[100][10] = {}, word[10] = {}, ans[100][10] = {};
    int i = 0, j, ap;
    // 输入字典并处理
    while (EOF != scanf("%s", word) && word[0] != '*') {
        strcpy(origin[i], word);
        strcpy(sorted[i], word);
        // 对字典单词做字母排序
        sort(sorted[i], sorted[i] + strlen(sorted[i]));
        i++;
    }
    // 输入待查单词
    while (EOF != scanf("%s", word)) {
        ap = 0;
        // 单词字母重排
        sort(word, word + strlen(word));
        // 在字母有序字典中查找
        for (j = 0; j < i; j++) {
            if (strcmp(sorted[j], word) != 0) {
                continue;
            }
            // 把没排序的原字典单词加入到答案中，插入排序
            int k = ap - 1;
            while (k >= 0) {
                if (strcmp(ans[k], origin[j]) <= 0) {
                    break;
                }
                strcpy(ans[k + 1], ans[k]);
                --k;
            }
            strcpy(ans[k + 1], origin[j]);
            ap++;
        }

        if (ap == 0) {
            printf(":(\n");
            continue;
        }

        for (int k = 0; k < ap; k++) {
            printf((k == 0) ? "%s" : " %s", ans[k]);
        }
        printf("\n");
    }
    return 0;
}