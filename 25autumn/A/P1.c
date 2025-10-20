/* P1.判断三角形
 * 
 * 题目描述：
 * 输入三条线段长度（不超过1000的正整数）。
 * 判断能否构成三角形，及三角形类型（直角、等边、等腰、其它）。
 * 
 * 输入形式：
 * 三个正整数，逗号分隔
 * 
 * 输出形式：
 * right triangle/
 * equilateral triangle/
 * isosceles triangle/
 * normal triangle/
 * NOT triangle
 */

#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d,%d,%d", &a, &b, &c);
    if (a+b>c && a+c>b && b+c>a) {
        if (a==b && b==c) { // 等边三角形
            printf("equilateral triangle\n");
        } else if (a==b || b==c || a==c) { // 等腰三角形
            printf("isosceles triangle\n");
        } else if (a*a+b*b==c*c || b*b+c*c==a*a || c*c+a*a==b*b) { // 直角三角形
            printf("right triangle\n");
        } else { // 一般三角形
            printf("normal triangle\n");
        }
    } else { // 不能构成三角形
        printf("NOT triangle\n");
    }
    return 0;
}