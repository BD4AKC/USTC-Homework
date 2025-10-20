/* P14.行程码压缩
 *
 * 题目描述：
 * 行程码（Run-Length Encoding）是一种统计编码，适用于经常出现连续符号的数据压缩，编码规则为：
 * 对2-8个连续出现的相同字符，用一个计数值和该字符来代替。
 * 例如aaa******dd表示为3a6*2d,超过8个相同字符时，
 * 每次截取8个进行编码，例如???????????(11个)表示为8?3?
 * 出现单独字符时，以计数值1开头，再列举连续的单独字符，在出现第一个连续相同字符之前以计数值1结尾。
 * 例如aaa!$$表示为3a1!12$，aaa!@#$$表示为3a1!@#12$
 * 输出编码结果时，计数值减1后以3位二进制数表示，字符以8位ASCII表示。
 * 例如3a6*2d表示为010 0110 0001 101 0010 1010 001 0110 0100，下划线表示计数值。
 * 最后按字节输出，即01001100, 00110100, 10101000, 10110010, 00000000
 * （不足一个字节时末尾补0），十六进制形式为4c34a8b200。
 *
 * 输入形式：
 * 从文本文件A14s.txt读入一个字符串。
 *
 * 输出形式：
 * 向文本文件A14t.txt入压缩后的十六进制串。
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool flag = false;
char str[1000000], ans[1000000];
int i = 0, j = 0, k = 0, len = 0, count = 1;
bool a[1000000] = {}, b[1000000] = {};

void Debug(FILE *);

void dec_to_bin(int num, int pos) { // 十进制转二进制
    num--;
    b[pos + 0] = (num & 4) >> 2;
    b[pos + 1] = (num & 2) >> 1;
    b[pos + 2] = (num & 1);
}

void char_to_ascii(char c, int pos) { // 字符转ASCII
    int num = (int)c;
    b[pos + 0] = (num & 128) >> 7;
    b[pos + 1] = (num & 64) >> 6;
    b[pos + 2] = (num & 32) >> 5;
    b[pos + 3] = (num & 16) >> 4;
    b[pos + 4] = (num & 8) >> 3;
    b[pos + 5] = (num & 4) >> 2;
    b[pos + 6] = (num & 2) >> 1;
    b[pos + 7] = (num & 1);
}

void output(FILE *fout) {
    for (i = 0; i < k; i += 8) { // 按字节输出
        int num = 0;
        for (j = i; j < i + 8; j++) {
            num <<= 1;
            num |= b[j];
        }
        fprintf(fout, "%02x", num);
    }
    fprintf(fout, "\n");
}

int main() {
    FILE *fin, *fout; // 初始化
    fin = fopen("A14s.txt", "r");
    fout = fopen("A14t.txt", "w");
    fscanf(fin, "%s", str);
    len = strlen(str);
    str[len] = (char)((int)str[len - 1] + 1); // 补上结束符

    while (i < len) { // 遍历字符串，编码
        if (str[i] == str[i+1]) { // 连续字符
            if (flag) {
                a[j] = true;
                ans[j++] = '1';
                flag = false;
            }
            count++;
            if (count == 9) { // 超过8个相同字符
                a[j] = true;
                ans[j++] = '8';
                ans[j++] = str[i];
                count = 1;
            }
        } else { // 单独字符
            if (count > 1) { // 连续相同字符结束
                a[j] = true;
                ans[j++] = (char)(48 + count);
                ans[j++] = str[i];
                flag = false;
                count = 1;
            } else { // 连续单独字符
                if (flag) { // 途中
                    ans[j] = str[i];
                    j++;
                } else { // 开始
                    flag = true;
                    a[j] = true;
                    ans[j++] = '1';
                    ans[j++] = str[i];
                }
            }

        }
        i++;
    }

    for (i = 0; i < j; i++) {
        if (a[i]) {
            dec_to_bin((int)ans[i] - 48, k);
            k += 3;
        } else {
            char_to_ascii(ans[i], k);
            k += 8;
        }
    }

    output(fout);

    // Debug(fout);

    fclose(fin);
    fclose(fout);
}

void Debug(FILE *fout) {
    fprintf(fout, "--------Debug--------\n");
    fprintf(fout, "%s\n", ans);
    for (i = 0; i < j; i++) {
        if (a[i]) fprintf(fout, "1");
        else fprintf(fout, " ");
    }
    fprintf(fout, "\n");
    for (i = 0; i < k; i++)
    {
        if (b[i]) fprintf(fout, "1");
        else fprintf(fout, "0");
    }
    fprintf(fout, "\n");
}