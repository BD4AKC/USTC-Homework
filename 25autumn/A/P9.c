/* P9.验证哥德巴赫猜想
 *
 * 题目描述：
 * 编程验证哥德巴赫猜想：
 * 一个不小于6的偶数可以表示为两个奇素数之和。
 * 如6=3+3，8=3+5，10=3+7。
 * 输入偶数n（unsigned int，6 ≤ n ≤ 10000），
 * 输出所有可能的分解结果（按第一个奇素数从小到大为序），
 * 但不包括把两个素数交换位置相加的情形。
 * 例如8=3+5，不要再输出8=5+3。
 *
 * 输入形式：
 * 偶数n
 *
 * 输出形式：
 * 所有分解结果
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void euler(bool *a, int n) { // 欧拉筛，筛选出小于n的素数
    memset(a, true, sizeof(bool) * (n + 1));
    int cnt = 0;
    int primes[10000] = {0};
    a[0] = a[1] = false;
    for (int i = 2; i <= n; i++) {
        if (a[i]) {
            primes[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * primes[j] <= n; j++) {
            a[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    bool a[10001];
    euler(a, n);
    for (int i = 3; i <= n/2; i += 2) {
        if (a[i] && a[n-i]) {
            printf("%d=%d+%d\n", n, i, n-i);
        }
    }
}