#include "h.h"

static void t_fun(char **s)
{
	static int x = 0;

	if (x == 0)
		(*s) = (char *)malloc(BUFFER_SIZE);
	x++;
}

int line_to_array(FILE *f, int ***arr, int *m, int n_cur, int n_max, int *el_cur, int *el_max)
{
	static char *line;
	char *cur_line;
	size_t len = 0, index = 0;


	t_fun(&line);
	if (!f)
		return -1;
//	Считывание строки до \n
	len = getline(&line, &len, f);

//	Когда он не считывает строку - он кладёт в len максимум
//	Максимум size_t можно получить, если из 0 вычесть 1
//	т.к. он циклический
	if (len == ((size_t)0 - 1))
	{
		//free(line);
		return 0;
	}
//	Откусывает от строки куски слева до разделителя
	cur_line = strtok(line, " ");
	while (cur_line)
	{
		if (*el_cur >= *el_max)
		{
			*el_max = resize_elem(arr, m, n_cur, n_max, *el_max);
		}
//		Перевод строки в int
		(*arr)[n_cur][index] = atoi(cur_line);
		index++;
		(*el_cur)++;
		cur_line = strtok(NULL, " ");
	}

	//free(line);
	m[n_cur] = index;
	return 1;
}

int resize_elem(int ***arr, int *m, int n, int n_max, int size)
{
	int i;

	size *= 2;
	*arr = (int **)realloc(*arr, n_max * sizeof(int *) + size * sizeof(int));
	(*arr)[0] = (int *)(((unsigned char *)(*arr)) + n_max * sizeof(int *));
	for (i = 1; i <= n; i++)
		(*arr)[i] = (*arr)[i - 1] + m[i - 1];

	return size;
}

int resize_lines(int ***arr, int **m, int n, int n_max, int size)
{
	int i, j;
	int **new_arr;

	n_max *= 2;

	new_arr = (int **)malloc(n_max * sizeof(int *) + size * sizeof(int));
	*m = (int *)realloc(*m, n_max * sizeof(int));

	new_arr[0] = (int *)(((unsigned char *)(new_arr)) + n_max * sizeof(int *));
	for (i = 1; i <= n; i++)
		new_arr[i] = new_arr[i - 1] + (*m)[i - 1];

	/*
		memcpy(new_arr[0], (*arr)[0], size * sizeof(int));
	*/

	for (i = 0; i <= n; i++)
		for (j = 0; j < (*m)[i]; j++)
			new_arr[i][j] = (*arr)[i][j];

	free(*arr);
	*arr = new_arr;
	return n_max;
}

int **read_hard_array(FILE *f, int *n)
{
	int n_cur = 0, n_max = START_LINE_MAX, el_cur = 0, el_max = START_ELEMENT_MAX, res;
	int *m;
	int **arr, *line;

	arr = (int **)malloc(n_max * sizeof(int *) + el_max * sizeof(int));
	m = (int *)malloc(n_max * sizeof(int));

	arr[0] = (int *)(((unsigned char *)arr) + n_max * sizeof(int *));
	
	res = line_to_array(f, &arr, m, n_cur, n_max, &el_cur, &el_max);
	
	n_cur++;
	if (res != 1)
	{
		*n = 0;
		free(arr);
		free(m);
		return NULL;
	}
	
	arr[n_cur] = arr[n_cur - 1] + m[n_cur - 1];

	while (1)
	{
		if (n_cur >= n_max - 1)
		{
			n_max = resize_lines(&arr, &m, n_cur, n_max, el_max);
		}
		res = line_to_array(f, &arr, m, n_cur, n_max, &el_cur, &el_max);
		if (res != 1)
			break ;
		n_cur++;
		arr[n_cur] = arr[n_cur - 1] + m[n_cur - 1];
	}
	/*
	for (int i = 0; i < n_cur; i++)
		printf("m[%d] = %d\n", i, m[i]);
	*/
	free(m);
	*n = n_cur;
	return arr;
}

void print_hard(int **arr, int n)
{
	int i, j;

	for(i = 0; i < n; ++i)
	{
		for (j = 0; j < (int)(arr[i + 1] - arr[i]); ++j)
			printf("%d\t", arr[i][j]);
		printf("\n");
	}
}

void fprint_hard(FILE *f, int **arr, int n)
{
	int i, j;

	for(i = 0; i < n; ++i)
	{
		for (j = 0; j < (int)(arr[i + 1] - arr[i]); ++j)
			fprintf(f, "%d\t", arr[i][j]);
		fprintf(f, "\n");
	}
}


/*

1 1 1
2 2 2 2
3 3 3 3 3
4 4

index = 2
					 p    p + len
		   *0  *1   *2    *3
*0 *1 *2 *3|012 0123 01234 01

1)
		   *0  *1   *2    *3
*0 *1 *2 *3|012 0123 01

2)
		    *0   *1   *3
*0 *1 *2 *3| 012 0123 01

3)
		 *0  *1   *3
*0 *1 *3|012 0123 01

*/


void delete_line(int **arr, int n, int index)
{
	int len = (int)(arr[index + 1] - arr[index]), i, remain = 0;
	int *pointer = arr[index];

	for (i = index + 1; i < n; i++)
		remain += (int)(arr[i + 1] - arr[i]);

	// Сдвиг элементов
	for (i = 0; i < remain; i++)
		pointer[i] = pointer[i + len];

	// Переназначение указателей
	for (i = index + 1; i < n + 1; i++)
	{
		arr[i] -= len;
	}

	// Сдвиг массива указателей
	for (i = index; i < n; i++)
	{
		arr[i] = arr[i + 1];
	}
}

void work_with_middle(int **arr, int *n)
{
	int middle = 0, n_elem = 0, i, j, k, m;

	for (i = 0; i < *n; i++)
	{
		m = (int)(arr[i + 1] - arr[i]);
		n_elem += m;
		for (j = 0; j < m; j++)
			middle += arr[i][j];

	}
	//printf("%d_%d\n", middle, n_elem);
	if (middle % n_elem != 0)
		return ;
	middle /= n_elem;
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < (int)(arr[i + 1] - arr[i]); j++)
			if (arr[i][j] == middle)
			{
				delete_line(arr, *n, i);
				(*n)--;
				return ;
			}
	}
}
