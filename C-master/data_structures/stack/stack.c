/*
    author: Christian Bender

    This is the implementation of the (generic) stack.
    The implementation uses the dynamic memory management and the principle
    of data hiding.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

/* 
   actual stack data structure
   This pointer will pointing at the actual field (of void * pointers) 
   that represents the stack.
 */
void **array;

/* the current capacity of the stack */
int max = 10; //스택의 현재 용량

/* counter variable for counting the elements of the stack. */
int counter = 0; //스택 안의 원소를 세기 위한 counter

/* 
    offset address 
    points at the top element of the stack.
*/
int offset = -1; //스택의 맨 위 원소 가리키는 

void initStack()
{

    array = malloc(sizeof(void *) * max);
    assert(array); /* tests whether pointer is assigned to memory. */
}

/*
    grow: increases the stack by 10 elements.
          This utility function isn't part of the public interface
*/
void  grow() //스택 안 원소 10 증가
{
    max += 10; /* increases the capacity */ //스택의 용량 10 증가

    int i; // for the loop
    void **tmp = malloc(sizeof(void *) * max);

    /* copies the elements from the origin array in the new one. */
    for (i = 0; i < max - 10; i++)
    {
        *(tmp + i) = *(array + i);
    }
    /*free the memory */
    free(array);
    array = tmp;  
}

/* push: pushs the argument onto the stack */
void push(void *object) //스택안에 인자 넣기
{

    assert(object); /* tests whether pointer isn't null */ //포인터가 널포인터가 아닌지 확인

    if (counter < max)
    {

        offset++; /* increases the element-pointer */ //원소 가리키는 포인터 

        /* 
            moves pointer by the offset address 
            pushs the object onto stack 
         */
        *(array + offset) = object; //offset 주소만큼 포인터를 옮김

        /* increases the inner counter */
        counter++;
    }
    else /* stack is full */ //스택이 다 찼을 경우
    {

        grow(); /* lets grow stack */
        push(object); /* recursive call */ //반복
    }
}

/*
    pop: pops the top element of the stack from the stack.
*/
void *pop() //스택에 가장 위에 있는 원소 빼내기
{

    void *top = *(array + offset);

    /* check pointers */
    assert(top);

    /* if use the pop-function, stack must not empty. */
    assert(!isEmpty()); //스택이 비어있으면 안됨

    /* decreases the offset address for pointing of
        the new top element */
    offset--;

    /* decreases the inner counter */
    counter--;

    return top;
}

/*
    size: gets the number of elements of the stack.
*/
int size() //스택 안에 있는 원소의 개수
{
    return counter;
}

/*
    isEmpty(): returns 1 if stack is empty otherwise 0.
*/
int isEmpty() //스택이 비어있으면 1, 아니면 0 반환
{
    return counter == 0;
}

/*
    top: returns the top element from the stack without removing it.
*/
void *top() //스택에 가장 위에 있는 원소를 스택에서 빼지 않고 반환함
{
    /* offset address points to the top element */
    return array[offset]; //offset은 가장 위에 있는 원소를 가리킴
}
