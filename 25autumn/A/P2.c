/* P2.阶乘求和
 * 
 * 题目描述：
 * 计算 1!+2!+3!+...+n!。计算结果不超过指定的max，超出则显示“overflow”。
 * 输入正整数n和max，输出计算结果。（1≤n≤100, 0≤max≤4e9）。
 * 
 * 要求：只使用单重循环，所有变量类型均为unsigned long
 * 
 * 输入形式：
 * n,max
 * 
 * 输出形式：
 * 和或者 overflow at x!
 */

#include <stdio.h>

int main() {
    unsigned long n, max;
    scanf("%lu,%lu", &n, &max);
    unsigned long sum = 0;
    unsigned long factorial = 1;
    for (unsigned long i = 1; i <= n; i++) {
        factorial *= i; // 求阶乘
        sum += factorial;
        if (sum > max) { // 超出max
            printf("overflow at %lu!\n", i);
            break;
        }
    }
    if (sum <= max) { // 没有超出max
        printf("%lu\n", sum);
    }
    return 0;
}