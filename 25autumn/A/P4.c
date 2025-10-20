/* P4.数列求和计算π 
 * 
 * 题目描述：
 * 编程按以下公式计算π的近似值，
 * 直至某个k值对应项引入的相对误差小于指定精度。
 * 例如，输出n表示精度为10^(-n)，且输出显示小数点后n位。1≤n≤12
 * 
 * $
 *  \pi = \sum_{k=0}^{\infty} \frac{1}{16^k}
 *        \left( \frac{4}{8k+1}
 *             - \frac{2}{8k+4}
 *             - \frac{1}{8k+5}
 *             - \frac{1}{8k+6}
 *        \right)
 * $
 * 
 * 输入形式：
 * n
 * 
 * 输出形式：
 * π的值
 */

#include <stdio.h>
#include <math.h>

int main() {
    int n, k=0;
    scanf("%d", &n);
    double pi = 0.0;
    double delta = pow(10, -(n+2)); // 指定精度为10^(-n-2)
    while (1) {
        double tmp = 1.0 / pow(16, k) * (
            4.0 / (8*k+1) -
            2.0 / (8*k+4) -
            1.0 / (8*k+5) -
            1.0 / (8*k+6)
        ); // 计算第k项相对误差
        if (tmp < delta) { // 若相对误差小于指定精度，则停止计算
            break;
        }
        pi += tmp;
        k++;
    }
    printf("pi=%.*lf\n", n, pi);
    return 0;
}