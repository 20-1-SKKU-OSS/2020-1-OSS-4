/*
 *	Author : ckckdud3
 *	This source file implements Bitonic Sort.
 */

// Includes
#include <stdio.h>
#include <stdlib.h>

void Swap(int *arr, int i, int j, int direction);
void BitonicMerge(int *arr, int base, int size, int direction);
void BitonicRecursive(int *arr, int base, int size, int direction);
void BitonicSort(int *arr, int size);

int main(){
	int *arr;
	int size;

	printf("Size of array : ");
	scanf("%d",&size);
	if(size >= 1){
		arr = (int *)malloc(sizeof(int)*size);
		for(int i=0;i<size;i++){
			printf("input #%d : ",i+1);
			scanf("%d",arr+i);
		}

		for(int i=0;i<size;i++)
			printf("%d ",*(arr+i));
		printf("\n");

		BitonicSort(arr);

		for(int i=0;i<size;i++)
			printf("%d ",*(arr+i));
		printf("\n");
	}
}

void Swap(int *arr, int i, int j, int direction){
	int temp;
	if(direction == (*(arr+i) > *(arr+j))){
		temp = *(arr+i);
		*(arr+i) = *(arr+j);
		*(arr+j) = temp;
	}
}


void BitonicMerge(int *arr, int base, int size, int direction){
	int mid;
	if(size > 1){
		mid = c/2;
		for(int i=base,i<base+mid,i++){
			Swap(i,i+mid,direction);
		}
		BitonicMerge(base,mid,direction);
		BitonicMerge(base+mid,mid,direction);
	}
}

void BitonicRecursive(int *arr, int base, int size, int direction){
	int mid;
	if(size > 1){
		mid = size/2;
		BitonicRecursive(arr,base,mid,1);
		BitonicRecursive(arr,base+mid,mid,0);
		BitonicMerge(arr,base,size,direction);
}

void BitonicSort(int *arr, int size){
	BitonicRecursive(0,size,1);
}
