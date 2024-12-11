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

void change_sort(int *arr, int n)
{
	int i, j;

	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < n - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}
}

int main(void)
{
	FILE *f;
	int *arr;
	int n;

	f = fopen("data", "r");

	arr = get_array(f, &n);
	print_arr(arr, n);
	change_sort(arr, n);
	print_arr(arr, n);

	fclose(f);
	free(arr);

	return 0;
}
