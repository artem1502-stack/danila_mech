#include <stdio.h>
#include <stdlib.h>

void swap(double *a, double *b)
{
	double t = *a;
	*a = *b;
	*b = t;
}

double *get_intervals(int n, FILE *f)
{
	double *arr;
	double a, b;
	int i;

	arr = (double *)malloc(2 * n * sizeof(double));

	for(i = 0; i < n; ++i)
	{
		fscanf(f, "%lf", &a);
		fscanf(f, "%lf", &b);
		if (b < a)
			swap(&a, &b);
		arr[2 * i] = a;
		arr[2 * i + 1] = b;
	}
	return arr;
}

void print_intervals(double *arr, int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		printf("[%.3lf, %.3lf] ", arr[2 * i], arr[2 * i + 1]);
	}
	printf("\n");
}

/*
i = 2
arr[0] = a1
arr[1] = b1
arr[2] = a2
arr[3] = b2

arr[4] = a3
arr[5] = b3

arr[6] = a4
arr[7] = b4

a1 a2 b1 b2 

a1 b2
a1 b1
a <= b


1) a1 b1 a2 b2
2) a1 a2 b1 b2
3) a1 a2 b2 b1


*/

void sort_intervals(double *arr, int n)
{
	int i, j;

	for(i = 0; i < n; ++i)
		for (j = 0; j < n - 1; ++j)
		{
			if (arr[2 * j] > arr[2 * j + 2])
			{
				swap(&arr[2 * j], &arr[2 * j + 2]);
				swap(&arr[2 * j + 1], &arr[2 * j + 3]);
			}
		}
}

double *merge_intervals(double *arr, int *n)
{
	double *arr_new;
	int i, j;

	arr_new = (double *)malloc(2 * (*n) * sizeof(double));
	
	arr_new[0] = arr[0];
	arr_new[1] = arr[1];
	for(i = 1, j = 0; i < *n; ++i)
	{
		if (arr_new[2 * j + 1] >= arr[2 * i])
		{
			if (arr_new[2 * j + 1] < arr[2 * i + 1]) 
				arr_new[2 * j + 1] = arr[2 * i + 1];
		}
		else
		{
			j++;
			arr_new[2 * j] = arr[2 * i];
			arr_new[2 * j + 1] = arr[2 * i + 1];
		}
	}
	*n = j + 1;
	free(arr);
	return arr_new;
}

int is_in_interavals(double *arr, int n, double a, double b)
{
	int i;

	for (i = 0; i < n; ++i)
	{
		if ((arr[2 * i] <= a) && (arr[2 * i + 1] >= b))
			return 1;
	}
	return 0;
}

int main(void)
{
	FILE *f;
	int n;
	double *arr;
	double a, b;

	scanf("%lf", &a);
	scanf("%lf", &b);

	f = fopen("data", "r");
	fscanf(f, "%d", &n);
	arr = get_intervals(n, f);
	print_intervals(arr, n);
	sort_intervals(arr, n);
	print_intervals(arr, n);
	arr = merge_intervals(arr, &n);
	print_intervals(arr, n);
	if (is_in_interavals(arr, n, a, b))
		printf("Yes\n");
	else
		printf("No\n");
	free(arr);
	fclose(f);
	return 0;
}
