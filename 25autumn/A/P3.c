/* P3.数字菱形
 * 
 * 题目描述：
 * 编程输出下面图形。其中上半层的高度（即最大的数字）由键盘输入，不超过9。
 *    1
 *   2 2
 *  3 3 3
 * 4 4 4 4
 *  3 3 3
 *   2 2
 *    1
 * 
 * 输入形式：
 * 上半层高度
 * 
 * 输出形式：
 * 居左显示的菱形
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 2*n-1; i++) {
        int num = n-abs(i-n); // 计算当前行数字个数
        for (int j = 1; j <= n-num; j++) {
            printf(" "); // 打印空格
        }
        for (int j = 1; j <= num-1; j++) {
            printf("%d ", num); // 打印前num-1个数字
        }
        printf("%d\n", num); // 打印最后一个数字
    }
    return 0;
}