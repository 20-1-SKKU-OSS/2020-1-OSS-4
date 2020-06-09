/*
 *	Author : ckckdud3
 *	This header file declares Queue structure and its methods.
 *      큐 : 단방향 연결 리스트를 이용한 큐의 구현
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

// InitQueue : Initializes Queue. // 큐 초기화
Queue *InitQueue(Queue *q);

// getSize : Returns the size of a queue. // 큐의 크기를 반환
int getSize(Queue *q);

// isEmpty : Checks whether the given queue is empty. // 큐가 비어있는지 확인
int isEmpty(Queue *q);

// Enqueue : Puts the new QNode at the rear of the queue. // 큐의 뒤쪽에 새로운 노드 생성
void Enqueue(Queue *q, Data data);

// Dequeue : Takes out the QNode at the front of the queue. // 큐의 앞에서 노드를 뺌
void Dequeue(Queue *q);

//Copy : Returns a deep-copied queue of the given queue. // q를 딥카피한 큐의 주소 반환
Queue *Copy(Queue *q);

//Search : Returns the index of target data. // 데이터 탐색
int Search(Queue *q, Data target);
#endif
