/* P6.给定日期求星期几
 *
 * 题目描述：
 * 已知1600年1月1日是周六，编程计算A年B月C日的星期数（1～7）。
 * 对非法日期应报错。（1600 ≤ Y ≤ 2100)
 *
 * 输入形式：
 * 年,月,日
 * 
 * 输出形式：
 * 星期数
 */

#include <stdio.h>
int main() {
    int day_of_month[13] = {0,
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    }; // 月份天数表
    int Year, Month, Day;
    scanf("%d,%d,%d", &Year, &Month, &Day);
    if ((Year < 1600 || Year > 2100)
        || (Month < 1 || Month > 12)
        || (Day < 1 || Day > 31)
        || (Day > day_of_month[Month])) { // 非法日期
        printf("Invalid\n");
        return 0;
    }
    if (Month == 2) { // 闰年判断
        if (Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0)) {
            if (Day > 29) { // 非法日期
                printf("Invalid\n");
                return 0;
            }
        } else {
            if (Day > 28) { // 非法日期
                printf("Invalid\n");
                return 0;
            }
        }
    }
    int century = Year / 100; // 世纪数
    int year_in_century = Year % 100; // 世纪内年份
    int month = Month < 3 ? Month + 12 : Month; // 月份
    int day = Day; // 日
    int D = century / 4 - 2 * century + year_in_century
        + year_in_century / 4 + 13 * (month + 1) / 5
        + day - 1; // 公式计算公历日期
    int W = D % 7; // 星期数
    printf("%d\n", W);
    return 0;
}