/*
 *	Author : ckckdud3
 *	This source file implements the methods of the Deque.
 *      Deque : Double-ended Queue
 *      It can enqueue/dequeue at both front and rear.
 *      데크 : Double-ended Queue
 *      front와 rear 양 쪽에서 데이터를 Enqueue 또는 Dequeue할 수 있다.
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"	// Check deque.h for struct informations.

// Macro definition
#define TRUE 1
#define FALSE 0

// Implementing Methods

// InitQueue : Initializes deque. // 데크 초기화
Queue *InitDeque(Deque *q){
	q = (Deque *)malloc(sizeof(Deque));
	q->size = 0;

	// Allocating memory for dummy nodes // 양 쪽 더미노드 생성
	q->front = (DQNode *)malloc(sizeof(DQNode));
	q->rear = (DQNode *)malloc(sizeof(DQNode));

	q->front->prev = NULL;
	q->front->next = q->rear;

	q->rear->prev = q->front;
	q->rear->front = NULL;

	return q;
}

// getSize : Returns the size of the given deque. // 데크 사이즈 반환
int getSize(Deque *q){
	return q->size;
}

// isEmpty : Checks whether the given deque is empty. // 데크가 비었는지 확인
int isEmpty(Deque *q){
	if(getSize(q) == 0)
		return TRUE;
	else
		return FALSE;
}

// EnqueueFront : Puts the new DQNode at the front of the deque. // front에 Enqueue
void EnqueueFront(Deque *q, Data data){

	DQNode *newnode = (DQNode *)malloc(sizeof(DQNode));
	newnode->value = data;
	if(q != NULL){
		newnode->next = q->front->next;
		newnode->prev = q->front;
		q->front->next->prev = newnode;
		q->front->next = newnode;
	}
}

// DequeueFront : Takes out the DQNode at the front of the deque. // front에서 Dequeue
Data *DequeueFront(Deque *q){

	Data *tempval = NULL;
	if(q != NULL && !isEmpty(q)){
		tempval = (Data *)malloc(sizeof(Data));
		DQNode *temp = q->front->next;
		*tempval = temp->value;
		q->front->next = temp->next;
		temp->next->prev = q->front;
		free(temp);
		(q->size)--;
	}
	return tempval;	
}

// EnqueueRear : Puts the new DQNode at the rear of the deque. // rear에 Enqueue
void EnqueueRear(Deque *q, Data data){

	DQNode *newnode = (DQNode *)malloc(sizeof(DQNode));
	newnode->value = data;
	if(q != NULL){
		newnode->prev = q->rear->prev;
		newnode->next = q->rear;
		q->rear->prev->next = newnode;
		q->rear->prev = newnode;
	}
}

// DequeueRear : Takes out the DQNode at the rear of the deque. // rear에서 Dequeue
Data DequeueRear(Deque *q){

	Data tempval = NULL;
	if(q != NULL && !isEmpty(q)){
		tempval = (Data *)malloc(sizeof(Data));
		DQNode *temp = q->rear->prev;
		*tempval = temp->value;
		q->rear->prev = temp->prev;
		temp->prev->next = q->rear;
		free(temp);
		(q->size)--;
	}
	return tempval;
}

// Copy : Returns a deep-copied queue of the given queue. // q를 딥카피하여 반환
Deque *Copy(Deque *q){

	Deque *copyq = NULL;
	if(q != NULL){
		InitDeque(copyq);
		if(isEmpty(q))
			return copyq;
		else{
			DQNode *cursor = q->front->next;
			while(cursor != q->rear){
				EnqueueRear(copyq, cursor->value);
				cursor = cursor->next;	
			}
		}
	}
	return copyq;
}

// Search : Returns the index of target data. // 데이터 탐색
int Search(Deque *q, Data target){
	
	if(q != NULL){
		DQNode *cursor = q->front->next;
		int index = 0;
		while(cursor != q->rear){
			if(cursor->value == target)
				return index;
			cursor = cursor->next;
			index++;
		}
	}
	// If there is no such value, returns -1 for representing "not found".
	return -1;
}
