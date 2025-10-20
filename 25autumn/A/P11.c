/* P11.判断回文
 * 
 * 题目描述：
 * 输入一个字符串，检查该字符串是否是“回文”。
 * 字符串长度<100，可能包括空格。
 * 要求：使用指针实现。
 * 
 * 输入形式：
 * 字符串
 * 
 * 输出形式：
 * Yes或No
 */

#include <stdio.h>
#include <string.h>

int check(char *str) {
    char *start = str;           // 指向字符串开头
    char *end = str + strlen(str) - 1;  // 指向字符串结尾
    
    // 当start指针在end指针左侧时继续比较
    while (start < end) {
        // 如果字符不相等，则不是回文
        if (*start != *end) {
            return 0;
        }
        start++;  // 开头指针向后移动
        end--;    // 结尾指针向前移动
    }
    return 1;  // 是回文
}

int main() {
    char str[100];
    fgets(str, sizeof(str), stdin);
    
    // 去掉fgets读取的换行符
    str[strcspn(str, "\n")] = '\0';
    
    if (check(str)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}