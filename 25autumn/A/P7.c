/* P7.支付与找零
 *
 * 题目描述：
 * 现有面值为a、b、c（0 < c < b < a ≤ 100）的三种钞票，
 * 买方分别有na、nb、nc张，卖方分别有ma、mb、mc张。
 * 问双方能否就一个价值为E的商品完成购买？
 * 如果可以，请给出一种双方交换钞票张数之和最少的支付与找钱的方法
 * （张数相同时，取找钱数量最少的方法）。
 * 每人每种面额钞票数不超过100，商品价值不超过10000，均为整数。
 *
 * 输入形式：
 * 分三行分别输入面值、买方钞票数、卖方钞票数、商品价格
 * a,b,c
 * na,nb,nc
 * ma,mc,mc
 * E
 *
 * 输出形式：
 * 分若干行依次输出a、b、c三种面额钞票的交换数量，每行格式如下：
 * Buyer pays ** bills of ** yuan.
 * 或
 * Seller changed ** bills of ** yuan.
 * 不需要交换的钞票不显示。
 * 如无法完成买卖，则输出：
 * Cannot buy.
 *
 * 本题目测试样例保证每组只有唯一解。
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c, na, nb, nc, ma, mb, mc, E;
    scanf("%d,%d,%d", &a, &b, &c);
    scanf("%d,%d,%d", &na, &nb, &nc);
    scanf("%d,%d,%d", &ma, &mb, &mc);
    scanf("%d", &E);
    int ans[4] = {100000}; // 答案
    if (E > na*a+nb*b+nc*c) {
        printf("Cannot buy.\n");

    } else {
        for (int i = 0; i <= ma+na; i++) {
            for (int j = 0; j <= mb+nb; j++) {
                for (int k = 0; k <= mc+nc; k++) {
                    if (i*a+j*b+k*c == E+ma*a+mb*b+mc*c) { // 找到一种交换方案
                        int num = abs(i-ma)+abs(j-mb)+abs(k-mc);
                        if (num < ans[0]) { // 记录交换数量
                            ans[0] = num;
                            ans[1] = i;
                            ans[2] = j;
                            ans[3] = k;
                        }
                    }
                }
            }
        }
    }
    if (ans[0] == 100000) {
        printf("Cannot buy.\n");
    } else {
        if (ans[1] > ma)
            printf("Buyer pays %d bills of %d yuan.\n", ans[1] - ma, a);
        if (ans[1] < ma)
            printf("Seller changed %d bills of %d yuan.\n", ma - ans[1], a);
        if (ans[2] > mb)
            printf("Buyer pays %d bills of %d yuan.\n", ans[2] - mb, b);
        if (ans[2] < mb)
            printf("Seller changed %d bills of %d yuan.\n", mb - ans[2], b);
        if (ans[3] > mc)
            printf("Buyer pays %d bills of %d yuan.\n", ans[3] - mc, c);
        if (ans[3] < mc)
            printf("Seller changed %d bills of %d yuan.\n", mc - ans[3], c);
    }
    return 0;
}