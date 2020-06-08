// Includes
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"	// Check queue.h for struct informations.

// Macro definition
#define TRUE 1
#define FALSE 0

// Implementing Methods

// InitQueue : Initializes Queue.
Queue *InitQueue(Queue *q){

	q = (Queue *)malloc(sizeof(Queue));
	q->size = 0;

	// Allocating memory for dummy nodes
	q->front = (QNode *)malloc(sizeof(QNode));

	q->front->next = NULL;
	q->rear = q->front;

	return q;
}

// getSize : Returns the size of a queue.
int getSize(Queue *q){

	return q->size;
}

// isEmpty : Checks whether the given queue is empty.
int isEmpty(Queue *q){

	if(getSize(q) == 0)
		return TRUE;
	else
		return FALSE;
}

// Enqueue : Puts the new QNode at the rear of the queue.
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

// Dequeue : Takes out the QNode at the front of the queue.
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

//Copy : Returns a deep-copied queue of the given queue.
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

//Search : Returns the index of target data.
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
