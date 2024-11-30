#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 1.e-8

/*

15. Заменить все локальные минимумы в массиве одним 
элементом, значение которого равно элементу массива 
с минимальным значением. Функция должна возвращать
количество элементов в получившемся массиве.

*/

void print_arr(double *arr, int n)
{
	int i;

	for(i = 0; i < n; i++)
		printf("%.0lf ", arr[i]);
	printf("\n");
}

double *get_array(FILE *f, int *len)
{
	double *arr;
	double x;
	int n = 0, cur_max_len = 20;

	arr = (double *)malloc(cur_max_len * sizeof(double));

	while (fscanf(f, "%lf", &x) == 1)
	{
		arr[n] = x;
		n++;
		if (n >= cur_max_len)
		{
			cur_max_len *= 2;
			arr = (double *)realloc(arr, cur_max_len * sizeof(double));
		}
	}

	*len = n;
	return arr;
}


int change_arr(double *arr, int n)
{
	double arr_min = arr[0];
	int i, j;

	for (i = 1; i < n; i++)
	{
		if (arr[i] < arr_min)
			arr_min = arr[i];
	}

	i = 1;
	
	if (arr[0] <= arr[1])
		while ((i < n) && (fabs(arr[0] - arr[i]) < EPS))
			i++;

	if (i == n)
		return n;

	memmove(arr + 1, arr + i, (n - i)*sizeof(double));
	arr[0] = arr_min;

	n -= i - 1;

	
	for (i = 1; i < n - 1; i++)
	{
		if (arr[i] < arr[i - 1])
			for (j = 1; i + j < n; j++)
			{
				if (fabs(arr[i + j] - arr[i]) < EPS)
				{
					if (i + j + 1 == n)
					{
						arr[i] = arr_min;
						n -= j;
						break;
					}
					continue ;
				}
				if (arr[i + j] < arr[i])
				{
					i = i + j;
					j = 0;
				}
				else if (arr[i + j] > arr[i])
				{
					memmove(arr + i + 1, arr + i + j, (n - i - j) * sizeof(double));
					arr[i] = arr_min;
					n -= j - 1;
					break;
				}

			}
	}
	return n;

}


int main(void)
{
	FILE *f;
	double x;
	double *arr;
	int i, n;

	f = fopen("data", "r");

	arr = get_array(f, &n);
	print_arr(arr, n);
	printf("\n\n");
	n = change_arr(arr, n);
	print_arr(arr, n);


	fclose(f);
	free(arr);
	return 0;
}
