#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS 1.e-8

/*

23. Удалить из массива элементы, содержащиеся во всех 
интервалах строгого возрастания с длиной не более 3. 
Функция должна возвращать количество элементов в 
получившемся массиве.

*/

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

void find_inter(int *arr, int n, int begin_index, int *start, int *end)
{
	int i;
	int counter;

	for (i = begin_index; i < n - 1; i++)
	{
		if (arr[i] < arr[i + 1])
		{
			for (counter = 0; (arr[i + counter] < arr[i + 1 + counter]) && (i + counter < n - 1); counter++)
				;
			if ((counter <= 4) && (counter > 1))
			{
				*start = i;
				*end = i + counter;
				return ;
			}
		}
	}
	*start = -1;
	*end = -1;
}

void delete_element(int *arr, int n, int index)
{
	int i;

	for (i = index; i < n - 1; i++)
		arr[i] = arr[i + 1];
}

int change_arr(int *arr, int n)
{
	// Инициализация переменных
	int els[3][2];
	int flag[3];

	int start, end, i, j;

	els[0][1] = 0;
	els[1][1] = 0;
	els[2][1] = 0;

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;

	// Первое заполнение элементов els
	find_inter(arr, n, 0, &start, &end);

	if (start == -1)
		return n;

	for (i = 0; i + start + 1 < end; i++)
	{
		els[i][0] = arr[i + start + 1];
		els[i][1] = 1;
	}

	// Основной цикл, где мы пробегаем интервалами и ищем элементы
	for (find_inter(arr, n, end + 1, &start, &end); start != -1; find_inter(arr, n, end + 1, &start, &end))
	{
		for (i = 0; i + start + 1 < end; i++)
		{
			for (j = 0; j < 3; j++)
				if (els[j][1] && arr[i + start + 1] == els[j][0])
					flag[j] = 1;
		}
		for (j = 0; j < 3; j++)
		{
			els[j][1] = flag[j];
			flag[j] = 0;
		}
	}
	if (els[0][1] + els[1][1] + els[2][1] == 0)
		return n;

	// Второй проход, где мы удаляем найденные элементы
	for (find_inter(arr, n, 0, &start, &end); start != -1; find_inter(arr, n, end + 1, &start, &end))
	{
		for (i = 0; i + start + 1 < end; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (els[j][1] && arr[i + start + 1] == els[j][0])
				{
					delete_element(arr, n, i + start + 1);
					n--;
					end--;
				}
			}
		}
	}
	return n;
}


int main(void)
{
	FILE *f;
	int *arr;
	int n;

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
