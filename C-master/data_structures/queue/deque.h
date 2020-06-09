/*
 *	Author : ckckdud3
 *	This source file implements the methods of the Deque.
 *      Deque : Double-ended Queue
 *      It can enqueue/dequeue at both front and rear.
 *      데크 : Double-ended Queue
 *      front와 rear 양 쪽에서 데이터를 Enqueue 또는 Dequeue할 수 있다.
 */

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

// InitQueue : Initializes deque. // 데크 초기화
Deque *InitDeque(Deque *q);

// getSize : Returns the size of the given deque. // 데크 사이즈 반환
int getSize(Deque *q);

// isEmpty : Checks whether the given deque is empty. // 데크가 비었는지 확인
int isEmpty(Deque *q);

// EnqueueFront : Puts the new DQNode at the front of the deque. // front에 Enqueue
void EnqueueFront(Deque *q, Data data);

// DequeueFront : Takes out the DQNode at the front of the deque. // front에서 Dequeue
Data *DequeueFront(Deque *q);

// EnqueueRear : Puts the new DQNode at the rear of the deque. // rear에 Enqueue
void EnqueueRear(Deque *q, Data data);

// DequeueRear : Takes out the DQNode at the rear of the deque. // rear에서 Dequeue
Data *DequeueRear(Deque *q);

// Copy : Returns a deep-copied queue of the given queue. // q를 딥카피하여 반환
Deque *Copy(Deque *q);

// Search : Returns the index of target data. // 데이터 탐색
int Search(Deque *q, Data target);
#endif
