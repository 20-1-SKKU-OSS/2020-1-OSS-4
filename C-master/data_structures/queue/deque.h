#ifndef __DEQUE_H__
#define __DEQUE_H__

typedef int Data;

typedef struct _node{
	Data value;
	struct _node *prev;
	struct _node *next;
}DQNode;

struct Deque{
	int size;
	DQNode *front;
	DQNode *rear;
};

// InitQueue : Initializes deque.
Deque *InitDeque(Deque *q);

// getSize : Returns the size of the given deque.
int getSize(Deque *q);

// isEmpty : Checks whether the given deque is empty.
int isEmpty(Deque *q);

// EnqueueFront : Puts the new DQNode at the front of the deque.
void EnqueueFront(Deque *q, Data data);

// DequeueFront : Takes out the DQNode at the front of the deque.
Data *DequeueFront(Deque *q);

// EnqueueRear : Puts the new DQNode at the rear of the deque.
void EnqueueRear(Deque *q, Data data);

// DequeueRear : Takes out the DQNode at the rear of the deque.
Data *DequeueRear(Deque *q);

// Copy : Returns a deep-copied queue of the given queue.
Deque *Copy(Deque *q);

// Search : Returns the index of the target data.
int Search(Deque *q, Data target);
#endif
