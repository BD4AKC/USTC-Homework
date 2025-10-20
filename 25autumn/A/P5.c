/* P5.求第k个排列
 * 
 * 题目描述：
 * 求排列的第k个序列。给定26个字母的前n个字符（不重复），
 * 对其进行全排列，并按字典排序，求第k个排列的序列。
 * 例如，n=3时，字符为abc，其排列（按字典排序）为
 * abc、acb、bac、bca、cab、cba，
 * 则第1个排列为abc，第2个排列为acb，第6个排列为cba
 * 1≤n≤26，1≤k≤2^32-1（若k>n!，则显示最后一个排列
 * 
 * 输入形式：
 * n,k 
 * 
 * 输出形式：
 * 第k个排列
 */

#include <stdio.h>

int main() {
    int n;
    unsigned long long k, fac[27];
    scanf("%d,%llu", &n, &k);
    fac[0] = 1ULL;
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ULL * fac[i - 1] * i;
    }
    if (k > fac[n]) // 若k超出n!(且n!未溢出),取最后一个排列
        k = fac[n];
    int used[26] = {0};
    k--; // 转为 0‑based
    for (int i = n; i >= 1; i--) {
        unsigned long long f = fac[i - 1];
        unsigned long long idx = k / f; // 当前位置的序号
        k = k % f; // 剩余序号
        // 在未使用字符中找第idx小的字符
        int cnt = -1;
        for (int j = 0; j < n; j++) {
            if (used[j] == 0) {
                cnt++;
                if (cnt == idx) {
                    putchar('a' + j);
                    used[j] = 1;
                }
            }
        }
    }
    putchar('\n');
    return 0;
}