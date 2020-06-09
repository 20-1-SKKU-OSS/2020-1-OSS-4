/*
 *	Author : ckckdud3
 *	This header file declares Queue structure and its methods.
 *      큐 : 단방향 연결 리스트를 이용한 큐의 구현
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"	// Check queue.h for struct informations.

// Macro definition
#define TRUE 1
#define FALSE 0

// Implementing Methods

// InitQueue : Initializes Queue. // 큐 초기화
Queue *InitQueue(Queue *q){

	q = (Queue *)malloc(sizeof(Queue));
	q->size = 0;

	// Allocating memory for dummy nodes
	q->front = (QNode *)malloc(sizeof(QNode));

	q->front->next = NULL;
	q->rear = q->front;

	return q;
}

// getSize : Returns the size of a queue. // 큐의 크기를 반환
int getSize(Queue *q){

	return q->size;
}

// isEmpty : Checks whether the given queue is empty. // 큐가 비어있는지 확인
int isEmpty(Queue *q){

	if(getSize(q) == 0)
		return TRUE;
	else
		return FALSE;
}

// Enqueue : Puts the new QNode at the rear of the queue. // 큐의 뒤쪽에 새로운 노드 생성
void Enqueue(Queue *q, Data data){

	QNode *newnode = (Qnode *)malloc(sizeof(QNode));
	newnode->value = data;
	newnode->next = NULL;

	if(q != NULL){
		q->rear->next = newnode;
		q->rear = newnode;
		(q->size)++;
	}
}

// Dequeue : Takes out the QNode at the front of the queue. // 큐의 앞에서 노드를 뺌
Data *Dequeue(Queue *q){

	Data *tempval = NULL;
	if(q != NULL && !isEmpty(q)){
		tempval = (Data *)malloc(sizeof(Data));
		QNode *temp = q->front->next;
		*tempval = temp->value;
		q->front->next = temp->next;
		free(temp);
		(q->size)--;
	}
	return tempval;
}

//Copy : Returns a deep-copied queue of the given queue. // q를 딥카피한 큐의 주소 반환
Queue *Copy(Queue *q){

	Queue *copyq = NULL;
	if(q != NULL){
		InitQueue(copyq);
		if(isEmpty(q))
			return copyq;
		else{
			QNode *cursor = q->front;
			while(cursor->next != NULL){
				cursor = cursor->next;
				Enqueue(copyq, cursor->value);
			}
		}
	}
	return copyq;
}

//Search : Returns the index of target data. // 데이터 탐색
int Search(Queue *q, Data target){

	if(q != NULL){
		QNode *cursor = q->front->next;
		int index = 0;
		while(cursor->next != NULL){
			if(cursor->value == target)
				return index;
			cursor = cursor->next;
			index++;
		}
	}
	// If there is no such value, returns -1 for representing "not found".
	return -1;
}
