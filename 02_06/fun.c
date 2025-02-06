#include "h.h"

void swap_line(t_line *a, t_line *b)
{
	t_line t = *a;
	*a = *b;
	*b = t;
}

void swap_double(double *a, double *b)
{
	double t = *a;
	*a = *b;
	*b = t;
}

t_line *get_intervals(int n, FILE *f)
{
	t_line *arr;
	double a, b;
	int i;

	arr = (t_line *)malloc(n * sizeof(t_line));

	for(i = 0; i < n; ++i)
	{
		if ((fscanf(f, "%lf", &a) != 1) || (fscanf(f, "%lf", &b) != 1))
		{
			printf("Error: incorrect input");
			free(arr);
			return NULL;
		}
		if (b < a)
			swap_double(&a, &b);
		arr[i].a = a;
		arr[i].b = b;
	}
	return arr;
}

void print_intervals(t_line *arr, int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		printf("[%.3lf, %.3lf] ", arr[i].a, arr[i].b);
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

void sort_intervals(t_line *arr, int n)
{
	int i, j;

	for(i = 0; i < n; ++i)
		for (j = 0; j < n - 1; ++j)
		{
			if (arr[j].a > arr[j + 1].a)
				swap_line(&arr[j], &arr[j + 1]);
		}
}

t_line *merge_intervals(t_line *arr, int *n)
{
	t_line *arr_new;
	int i, j;

	arr_new = (t_line *)malloc((*n) * sizeof(t_line));
	
	arr_new[0] = arr[0];
	for(i = 1, j = 0; i < *n; ++i)
	{
		if (arr_new[j].b >= arr[i].a)
		{
			if (arr_new[j].b < arr[i].b) 
				arr_new[j].b = arr[i].b;
		}
		else
		{
			j++;
			arr_new[j] = arr[i];
		}
	}
	*n = j + 1;
	free(arr);
	return arr_new;
}

int is_in_interavals(t_line *arr, int n, double a, double b)
{
	int i;

	for (i = 0; i < n; ++i)
	{
		if ((arr[i].a <= a) && (arr[i].b >= b))
			return 1;
	}
	return 0;
}
