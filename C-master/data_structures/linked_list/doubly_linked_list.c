#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int element;
    struct ListNode *prev;
    struct ListNode *next;
}ListNode;
//노드 스트럭쳐 생성

ListNode* newNode(int val){
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->prev = node->next = NULL;
    node->element = val;
    return node;
}
//노드 생성

void addNode(ListNode** head, int val){
    ListNode* node = newNode(val);
    if(!(*head)){//비어있는 리스트
        *head = node;
    }
    else if((*head)->next == NULL){//마지막 위치의 노드
        node->prev = *head;
        (*head)->next = node;
        *head = node;
    }
    else{
        addNode(&(*head)->next, val);
    }
}
//노드 추가

void deleteNode(ListNode** head, int val){
    if(*head == NULL){//비어있음
        return;
    }
    else if((*head)->element == val){//원래 헤드 따로 저장
        ListNode* orghead = *head;
        
        if(!(*head)->prev && !(*head)->next){//노드 한개
            *head = NULL;
        }
        else if(!(*head)->prev && (*head)->next){//맨 앞 노드
            *head = (*head)->next;
            (*head)->prev = NULL;
            free(orghead);
        }
        else if((*head)->prev && !(*head)->next){//맨 끝 노드
            *head = (*head)->prev;
            (*head)->next = orghead->next;
            free(orghead);
        }
        else{//중간 노드
            *head = (*head)->next;
            (*head)->prev = orghead->prev;
            free(orghead);
        }
    }
    else{
        deleteNode(&(*head)->next, val);
    }
}
//노드 삭제

void printList(ListNode* node){
    ListNode* cnode = node;
    while(cnode != NULL){
        printf("%d\n", cnode->element);
        cnode = cnode->next;
    }
}
//출력

int main(){
    ListNode *head = 0;
    
    addNode(&head, 1);
    addNode(&head, 2);
    addNode(&head, 3);
    printList(head);
    deleteNode(&head, 3);
    printList(head);
}
