#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 1.e-8

/*

Простая сортировка обменами

*/

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
	if (low < high)
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
	FILE *f;
	int *arr;
	int n;

	f = fopen("data", "r");

	arr = get_array(f, &n);
	print_arr(arr, n);
	quick_sort(arr, n);
	print_arr(arr, n);

	fclose(f);
	free(arr);

	return 0;
}
