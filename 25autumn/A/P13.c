/* P13.�����˿������ж�
 *
 * ��Ŀ������
 * ����һ�� 5 ���Ƶ����ͣ������õ����͡�
 * �������ֻ�ɫ��Diamonds��Clubs��Hearts��Spades��
 * ��ʮ�����ȼ���2��3��4��5��6��7��8��9��10��J��Q��K��A����
 * A �ȿ���Ϊ���ȼ���Ҳ����Ϊ��С�ȼ���
 * ����ʱ����ɫ�ô�д����ĸ��ʾ���ȼ������ֻ���ĸ��ʾ
 * ��10 �� T ��ʾ���������ǷǷ����롣
 * �������ظ�������������һ��������Ϊ 0 ���������
 *
 * <2025/09/24����>
 * ���зǷ����룬ֱ�Ӷ������ɣ�
 * ֱ������Ϊ 0 ʱ���������ܹ��ĺϷ�����ᱣ֤Ϊ5���ơ�
 *
 * ���ʹӴ�С�У�
 * ��ͬ��˳ straight flush��ͬ��ɫ�ҵȼ�˳��������
 * ������ four of a kind��4 ���Ƶȼ���ͬ��
 * ����« full house��3 ���Ƶȼ���ͬ����2����Ҳ�ȼ���ͬ��
 * ��ͬ�� flush��5 ���ƻ�ɫ��ͬ��
 * ��˳�� straight��5 ���Ƶȼ�˳��������
 * ������ three of a kind��3 ���Ƶȼ���ͬ��
 * ������ two pairs�������������ӣ�
 * ��һ���� pair��2 ���Ƶȼ���ͬ��
 * ������ high card�����������ƣ�
 *
 * ������ʽ:
 * ��ɫ�ô�д����ĸ��ʾ���ȼ������ֻ���ĸ��ʾ��10��T��ʾ����
 * �����ǷǷ����롣
 * �������ظ�������������һ��������Ϊ0���������
 *
 * �����ʽ��
 * �����������
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct card {
    char suit; // ��ɫ
    int rank; // �ȼ�
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
                // �ظ��ƣ�����
                i--;
                break;
            }
        }
    }

    sort_as_rank();

    // �ж�����
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

void sort_as_rank() { // ���յȼ�����
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

bool four_of_a_kind() { // ���ţ��ȼ���ͬ
    return (card[0].rank == card[3].rank || card[1].rank == card[4].rank);
}

bool full_house() { // ��«��3���Ƶȼ���ͬ����2����Ҳ�ȼ���ͬ
    return ((card[0].rank == card[2].rank && card[3].rank == card[4].rank) 
    || (card[0].rank == card[1].rank && card[2].rank == card[4].rank));
}

bool flush() { // ͬ����5���ƻ�ɫ��ͬ
    return (card[0].suit == card[1].suit && card[1].suit == card[2].suit 
        && card[2].suit == card[3].suit && card[3].suit == card[4].suit);
}

bool straight() { // ˳�ӣ�5���Ƶȼ�˳������,ע��A
    return ((card[0].rank == card[1].rank - 1 && card[1].rank == card[2].rank - 1 
        && card[2].rank == card[3].rank - 1 && card[3].rank == card[4].rank - 1) 
		|| (card[0].rank == 2 && card[1].rank == 3 && card[2].rank == 4 
        && card[3].rank == 5 && card[4].rank == 14));
}

bool three_of_a_kind() { // ���ţ��ȼ���ͬ
    return (card[0].rank == card[2].rank || card[1].rank == card[3].rank 
        || card[2].rank == card[4].rank);
}

bool two_pairs() { // ���ԣ�������������
    return ((card[0].rank == card[1].rank && card[2].rank == card[3].rank) ||
        (card[0].rank == card[1].rank && card[3].rank == card[4].rank) ||
        (card[1].rank == card[2].rank && card[3].rank == card[4].rank));
}

bool pair() { // һ�ԣ�2���Ƶȼ���ͬ
    return (card[0].rank == card[1].rank || card[1].rank == card[2].rank 
        || card[2].rank == card[3].rank || card[3].rank == card[4].rank);
}
