/* P13.德州扑克牌型判断
 *
 * 题目描述：
 * 分析一手 5 张牌的牌型，输出最好的牌型。
 * 牌有四种花色（Diamonds、Clubs、Hearts、Spades）
 * 和十三个等级（2、3、4、5、6、7、8、9、10、J、Q、K、A），
 * A 既可作为最大等级，也可作为最小等级。
 * 输入时，花色用大写首字母表示，等级用数字或字母表示
 * （10 用 T 表示）。不考虑非法输入。
 * 若输入重复牌则丢弃，若第一张牌输入为 0 则结束程序。
 *
 * <2025/09/24补充>
 * 会有非法输入，直接丢弃即可，
 * 直到输入为 0 时结束程序，总共的合法输入会保证为5张牌。
 *
 * 牌型从大到小有：
 * ·同花顺 straight flush（同花色且等级顺序相连）
 * ·四张 four of a kind（4 张牌等级相同）
 * ·葫芦 full house（3 张牌等级相同，另2张牌也等级相同）
 * ·同花 flush（5 张牌花色相同）
 * ·顺子 straight（5 张牌等级顺序相连）
 * ·三张 three of a kind（3 张牌等级相同）
 * ·两对 two pairs（存在两个对子）
 * ·一对子 pair（2 张牌等级相同）
 * ·高牌 high card（其它，杂牌）
 *
 * 输入形式:
 * 花色用大写首字母表示，等级用数字或字母表示（10用T表示）。
 * 不考虑非法输入。
 * 若输入重复牌则丢弃，若第一张牌输入为0则结束程序。
 *
 * 输出形式：
 * 输出牌型名称
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct card {
    char suit; // 花色
    int rank; // 等级
} card[5];

bool four_of_a_kind();
bool full_house();
bool flush();
bool straight();
bool three_of_a_kind();
bool two_pairs();
bool pair();
void sort_as_rank();

int main() {
    for (int i = 0; i < 5; i++) {
        char card_str[3];
        scanf("%2s", card_str);
        if (card_str[0] == '0') {
            break;
        }
        card[i].suit = card_str[0];
        char c = card_str[1];
        if (c >= '2' && c <= '9') {
            card[i].rank = (int)c - '0';
        } else if (c == 'T') {
            card[i].rank = 10;
        } else if (c == 'J') {
            card[i].rank = 11;
        } else if (c == 'Q') {
            card[i].rank = 12;
        } else if (c == 'K') {
            card[i].rank = 13;
        } else if (c == 'A') {
            card[i].rank = 14;
        } else {
            continue;
        }
        for (int j = 0; j < i - 1; j++) {
            if (card[i].rank == card[j].rank && card[i].suit == card[j].suit) {
                // 重复牌，丢弃
                i--;
                break;
            }
        }
    }

    sort_as_rank();

    // 判断牌型
    if (straight() && flush()) printf("straight flush\n");
    else if (four_of_a_kind()) printf("four of a kind\n");
    else if (full_house()) printf("full house\n");
    else if (flush()) printf("flush\n");
    else if (straight()) printf("straight\n");
    else if (three_of_a_kind()) printf("three of a kind\n");
    else if (two_pairs()) printf("two pairs\n");
    else if (pair()) printf("pair\n");
    else printf("high card\n");
    //printf("straight\n");
	return 0;
}

void sort_as_rank() { // 按照等级排序
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (card[j].rank > card[j + 1].rank || 
               (card[j].rank == card[j + 1].rank && card[j].suit < card[j + 1].suit)) {
                struct card temp = card[j];
                card[j] = card[j + 1];
                card[j + 1] = temp;
            }
        }
    }
}

bool four_of_a_kind() { // 四张，等级相同
    return (card[0].rank == card[3].rank || card[1].rank == card[4].rank);
}

bool full_house() { // 葫芦，3张牌等级相同，另2张牌也等级相同
    return ((card[0].rank == card[2].rank && card[3].rank == card[4].rank) 
    || (card[0].rank == card[1].rank && card[2].rank == card[4].rank));
}

bool flush() { // 同花，5张牌花色相同
    return (card[0].suit == card[1].suit && card[1].suit == card[2].suit 
        && card[2].suit == card[3].suit && card[3].suit == card[4].suit);
}

bool straight() { // 顺子，5张牌等级顺序相连,注意A
    return ((card[0].rank == card[1].rank - 1 && card[1].rank == card[2].rank - 1 
        && card[2].rank == card[3].rank - 1 && card[3].rank == card[4].rank - 1) 
		|| (card[0].rank == 2 && card[1].rank == 3 && card[2].rank == 4 
        && card[3].rank == 5 && card[4].rank == 14));
}

bool three_of_a_kind() { // 三张，等级相同
    return (card[0].rank == card[2].rank || card[1].rank == card[3].rank 
        || card[2].rank == card[4].rank);
}

bool two_pairs() { // 两对，存在两个对子
    return ((card[0].rank == card[1].rank && card[2].rank == card[3].rank) ||
        (card[0].rank == card[1].rank && card[3].rank == card[4].rank) ||
        (card[1].rank == card[2].rank && card[3].rank == card[4].rank));
}

bool pair() { // 一对，2张牌等级相同
    return (card[0].rank == card[1].rank || card[1].rank == card[2].rank 
        || card[2].rank == card[3].rank || card[3].rank == card[4].rank);
}
