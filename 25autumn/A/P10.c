/* P10.逆算GPA
 *
 * 题目描述：
 * 某学生五门课程的成绩均为百分制整数。输入他的GPA，
 * 求其加权平均分的可能的范围（即最小值、最大值，
 * 保留一位小数），以及加权平均分的可能分值的数量。
 * 假定所有课程的学分均为1，绩点换算规则：
 *      100:5   [90, 100):4    [80,90):3
 * [70, 80):2    [60, 70):1    (0, 60):0
 *
 * 输入形式：
 * GPA分数
 *
 * 输出形式：
 * MinAve:最小值 MaxAve:最大值 PossibleAve:可能分值数量
 * 无解时输出Impossible
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int min_score;
    int max_score;
} ScoreRange;

ScoreRange get_score_range(int g) {
    ScoreRange range;
    switch(g) {
        case 5:
            range.min_score = 100;
            range.max_score = 100;
            break;
        case 4:
            range.min_score = 90;
            range.max_score = 99;
            break;
        case 3:
            range.min_score = 80;
            range.max_score = 89;
            break;
        case 2:
            range.min_score = 70;
            range.max_score = 79;
            break;
        case 1:
            range.min_score = 60;
            range.max_score = 69;
            break;
        case 0:
            range.min_score = 0;
            range.max_score = 59;
            break;
        default:
            range.min_score = -1;
            range.max_score = -1;
    }
    return range;
}

int main() {
    char input[20];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Impossible\n");
        return 0;
    }
    
    // Remove newline character if present
    input[strcspn(input, "\n")] = 0;
    
    double gpa;
    if (sscanf(input, "%lf", &gpa) != 1) {
        printf("Impossible\n");
        return 0;
    }
    
    double S = gpa * 5.0;
    int S_int = (int)round(S);
    
    // Check if GPA is valid
    if (fabs(S - S_int) > 1e-5 || S_int < 0 || S_int > 25) {
        printf("Impossible\n");
        return 0;
    }
    
    // Initialize DP table
    int dp[6][26][501] = {0}; // dp[courses][grade_points][total_score]
    dp[0][0][0] = 1;
    
    // Fill DP table
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= 25; j++) {
            for (int g = 0; g <= 5; g++) {
                int new_j = j + g;
                if (new_j > 25) continue;
                
                ScoreRange range = get_score_range(g);
                for (int s = range.min_score; s <= range.max_score; s++) {
                    for (int t = 0; t <= 500; t++) {
                        if (dp[i][j][t]) {
                            int new_t = t + s;
                            if (new_t <= 500) {
                                dp[i+1][new_j][new_t] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Find min, max and count of possible total scores
    int min_total = 501, max_total = -1, count = 0;
    for (int t = 0; t <= 500; t++) {
        if (dp[5][S_int][t]) {
            if (t < min_total) min_total = t;
            if (t > max_total) max_total = t;
            count++;
        }
    }
    
    if (count == 0) {
        printf("Impossible\n");
    } else {
        double min_ave = min_total / 5.0;
        double max_ave = max_total / 5.0;
        
        // Calculate number of distinct possible average scores
        // Since scores are integers, average scores are multiples of 0.2
        int possible_ave_count = 0;
        for (int t = min_total; t <= max_total; t++) {
            if (dp[5][S_int][t]) {
                possible_ave_count++;
            }
        }
        
        printf("MinAve:%.1lf MaxAve:%.1lf PossibleAve:%d\n", 
               min_ave, max_ave, possible_ave_count);
    }
    
    return 0;
}