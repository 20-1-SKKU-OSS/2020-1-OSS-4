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
Queue *Copy(queue *q);

#endif
