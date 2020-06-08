/*
 *	Author : ckckdud3
 *	This header file declares Queue structure and its methods.
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef int Data;

typedef struct _node{
	Data value;
	struct _node *next;
}QNode;

struct Queue{
	int size;
	QNode *front;
	QNode *rear;
};

// InitQueue : Initializes Queue.
Queue *InitQueue(Queue *q);

// getSize : Returns the size of the given queue.
int getSize(Queue *q);

// isEmpty : Checks whether the given queue is empty.
int isEmpty(Queue *q);

// Enqueue : Puts the new QNode at the rear of the queue.
void Enqueue(Queue *q, Data data);

// Dequeue : Takes out the QNode at the front of the queue.
void Dequeue(Queue *q);

// Copy : Returns a deep-copied queue of the given queue.
Queue *Copy(Queue *q);

// Search : Returns the index of target data.
int Search(Queue *q, Data target);
#endif
