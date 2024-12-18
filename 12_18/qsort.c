#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define EPS 1.e-8
#define MAX_NUMBER 1000000


/*

Quick sort

*/

int *get_random_array(int n)
{
	int *arr, i;

	arr = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		arr[i] = rand() % (2 * MAX_NUMBER + 1) - MAX_NUMBER;
	return arr;
}

int is_sorted(int *arr, int start, int end)
{
	int i;

	for (i = start; i <= end - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return 0;
	}
	return 1;
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void print_arr(int *arr, int n)
{
	int i;

	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int *get_array(FILE *f, int *len)
{
	int *arr;
	int x;
	int n = 0, cur_max_len = 20;

	arr = (int *)malloc(cur_max_len * sizeof(int));
	while (fscanf(f, "%d", &x) == 1)
	{
		arr[n] = x;
		n++;
		if (n >= cur_max_len)
		{
			cur_max_len *= 2;
			arr = (int *)realloc(arr, cur_max_len * sizeof(int));
		}
	}
	*len = n;
	return arr;
}
/*
|
V
5 0 7 9 2 1

arr[i]=7
arr[j]=1
swap
    i     j
5 0 1 9 2 7

arr[i] = 9
arr[j] = 2
swap
      i j
5 0 1 2 9 7

arr[i] = 9
arr[j] = 2

      j i
5 0 1 2 9 7

swap (arr[low], arr[j])
      |
      V
2 0 1 5 9 7

*/
int partition(int *arr, int low, int high)
{
	int p = arr[low];
	int i = low, j = high;

	while(i < j)
	{

		while((arr[i] <= p) && (i <= high - 1))
		{
			i++;
		}

		while((arr[j] > p) && (j >= low + 1))
		{
			j--;
		}
		if (i < j)
			swap(&arr[i], &arr[j]);
	}
	swap(&arr[low], &arr[j]);
	return j;
}

void quick_sort_recursion(int *arr, int low, int high)
{
	if ((low < high) && (!is_sorted(arr, low, high)))
	{
		int p = partition(arr, low, high);

		quick_sort_recursion(arr, low, p - 1);
		quick_sort_recursion(arr, p + 1, high);
	}
}

void quick_sort(int *arr, int n)
{
	quick_sort_recursion(arr, 0, n - 1);
}

int main(void)
{
	int *arr;
	int n;
	time_t t;

	printf("Enter array len:\n");
	scanf("%d", &n);
	arr = get_random_array(n);
	t = time(NULL);
	quick_sort(arr, n);
	printf("Time spended = %ld seconds\n", time(NULL) - t);
	if (is_sorted(arr, 0, n - 1))
		printf("Array is sorted\n");
	else
		printf("Array not sorted\n");

	free(arr);

	return 0;
}
