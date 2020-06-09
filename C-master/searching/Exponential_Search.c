#include <stdio.h>

/*
 *   Exponential_Search : 이진 탐색이 절반부터 시작하여 줄여나간다면,
 *   			  지수 탐색은 1부터 시작하여 두배씩 늘려나가면서
 *   			  탐색하는 알고리즘이다.
 */

// Utility function to find minimum of two numbers
int min(int x, int y) {
	return (x < y) ? x : y;
}

// Binary search algorithm to return the position of
// target x in the sub-array arr[low..high]		// 범위를 찾아냈다면 그 안에서 이진 탐색
int BinarySearch(int arr[], int low, int high, int x)
{
	// Base condition (search space is exhausted)
	if (low > high)
		return -1;

	// we find the mid value in the search space and
	// compares it with target value

	int mid = (low + high)/2;	// overflow can happen
	// int mid = low + (high - low)/2;

	// Base condition (target value is found)
	if (x == arr[mid])
		return mid;

	// discard all elements in the right search space
	// including the mid element
	else if (x < arr[mid])
		return BinarySearch(arr, low, mid - 1, x);

	// discard all elements in the left search space
	// including the mid element
	else
		return BinarySearch(arr, mid + 1, high, x);
}

// Returns the position of target x in the given array of length n	// 지수 탐색
int ExponentialSearch(int arr[], int n, int x)
{
	int bound = 1;

	// find the range in which the target x would reside
	while (bound < n && arr[bound] < x)
		bound *= 2;	// calculate the next power of 2

	// call binary search on arr[bound/2 .. min(bound, n)]	// 숫자가 있는 것 같은 범위를 찾았다면 그 안에서 이진 탐색
	return BinarySearch(arr, bound/2, min(bound, n), x);
}

// Exponential search algorithm
int main(void)
{
	int arr[] = {2, 5, 6, 8, 9, 10};
	int target = 9;

	int n = sizeof(arr)/sizeof(arr[0]);
	int index = ExponentialSearch(arr, n, target);

	if (index != -1)
		printf("Element found at index %d", index);
	else
		printf("Element not found in the array");

	return 0;
}
