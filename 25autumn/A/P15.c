/* P15.单词的逆序输出
 *
 * 题目描述：
 * 将一个字符串中的单词逆序（注意是单词逆序，不是字母逆序），
 * 同时保持标点、空格等符号保持位置和顺序不变。
 * 字符串长度不超过1000。
 * 评测模式
 * 本题的评测使用精确匹配。
 *
 * 输入形式：
 * 一个字符串
 *
 * 输出形式：
 * 单词逆序后的字符串
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char str[1001], ans[1001];
int k1, k2, len, ans_key;
int a[1001], b[1001];

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void ans1(int x) {
    while (x < len) {
        if (!is_letter(str[x])) {
            return;
        }
        ans[ans_key++] = str[x++];
    }
    return;
}

void ans2(int x) {
    while (x < len) {
        if (is_letter(str[x])) {
            return;
        }
        ans[ans_key++] = str[x++];
    }
    return;
}

int main() {
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    len = strlen(str);
    int i = 0;
    while (i < len) {
        if (is_letter(str[i])) {
            a[k1++] = i;
        } else {
            b[k2++] = i;
        }
        int j = i;
        while (j < len && is_letter(str[j]) == is_letter(str[i])) {
            j++;
        }
        i = j;
    }
    int delta = 0;
    if (b[0] == 0) {
        ans2(0);
        delta = 1;
    }
    for (i = 0; i < k1; i++) {
        ans1(a[k1 - i - 1]);
        if (i + delta < k2) ans2(b[i + delta]);
    }
    ans[ans_key] = '\0';
    printf("%s", ans);
    return 0;
}