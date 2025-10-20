/* P12.链表建立与排序
 * 
 * 问题描述：
 * 读入N个int型整数，将它们按照从小到大的顺序存放并显示。(0<=N<=1000)。
 * 要求1：数据存放在一个链表中。每输入一个数据，
 * 即将它插入到链表中，并维护链表的有序性。
 * 要求2：建立链表、插入链表，显示链表等操作应使用单独的函数完成。
 * 注意：上面的要求 1 、要求 2 都将由人工检查，
 * 请确保您提交的最后一个版本的代码符合要求。<2025/09/21更正>
 */

#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 函数声明
void insertNode(struct Node** head, int value);
void displayList(struct Node* head);
void freeList(struct Node* head);

int main() {
    // 建立空链表
    struct Node* head = NULL;
    int N;
    
    // 读取整数个数
    scanf("%d", &N);
    
    // 读取并插入N个整数
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        insertNode(&head, num);
    }
    
    // 显示排序后的链表
    displayList(head);
    
    // 释放链表内存
    freeList(head);
    
    return 0;
}

// 向有序链表中插入新节点
void insertNode(struct Node** head, int value) {
    // 创建新节点
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    
    // 如果链表为空或新节点值小于头节点，插入在头部
    if (*head == NULL || value < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    
    // 寻找插入位置
    struct Node* current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }
    
    // 插入新节点
    newNode->next = current->next;
    current->next = newNode;
}

// 显示链表内容
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf("\n");
        }
        current = current->next;
    }
}

// 释放链表内存
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}