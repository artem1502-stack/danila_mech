#include "h.h"

int **read_darray_special(FILE *f, int *n, int *m)
{
	int **array, i, j;

	fscanf(f, "%d", n);
	fscanf(f, "%d", m);

	array = (int **)malloc((*n) * sizeof(int *) + (*n) * (*m) * sizeof(int));
	
	for(i = 0; i < *m; ++i) 
		array[i] = (int *)((unsigned char*)array + sizeof(int *)*(*n)+i*sizeof(int)*(*m));

	for (i = 0; i < *n; ++i)
		for (j = 0; j < *m; ++j)
			fscanf(f, "%d", &(array[i][j]));
	return array;
}

void print_darray(int **array, int n, int m)
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}	
}

void fprint_darray(FILE *f, int **array, int n, int m)
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
			fprintf(f, "%d ", array[i][j]);
		fprintf(f, "\n");
	}		
}
4 1 5 6 
7 4 8 9 
10 7 11 12 

index = 3
i, j = 0

i = 0	|4 1 5 6 7 4 8 9 10 7 11 12| j = 0
i = 1	|4 1 5 6 7 4 8 9 10 7 11 12| j = 1
i = 2	|4 1 5 6 7 4 8 9 10 7 11 12| j = 2
i = 3	|4 1 5 6 7 4 8 9 10 7 11 12| j = 3
i = 4	|4 1 5 7 7 4 8 9 10 7 11 12| j = 3
i = 5	|4 1 5 7 4 4 8 9 10 7 11 12| j = 4
i = 6	|4 1 5 7 4 8 8 9 10 7 11 12| j = 5
i = 7	|4 1 5 7 4 8 8 9 10 7 11 12| j = 6
i = 8	|4 1 5 7 4 8 10 9 10 7 11 12| j = 6
i = 9	|4 1 5 7 4 8 10 7 10 7 11 12| j = 7
i = 10	|4 1 5 7 4 8 10 7 11 7 11 12| j = 8
i = 11	|4 1 5 7 4 8 10 7 11 7 11 12| j = 8

4 1 5
7 4 8 
10 7 11

void	delete_column_special(int **array, int n, int m, int index)
{
	int j = 0;

	for (int i = 0; i < n*m; i++)
	{
		if (i % m != index)
		{
			array[0][j] = array[0][i];
			j++;
		}
	}
}

int find_max_absolute(int *array, int n)
{
	int flag1 = 0, i, cur_max = array[0], cur_max_index = 0;

	for (i = 1; i < n; ++i)
	{
		if (array[i] == cur_max)
			flag1 = 1;
		else if (array[i] > cur_max)
		{
			flag1 = 0;
			cur_max = array[i];
			cur_max_index = i;
		}
	}
	if (flag1)
		return -1;
	return cur_max_index;
}

int check_max(int **array, int n, int *m)
{
	int i, index;

	index = find_max_absolute(array[0], *m);
	if (index == -1)
		return 0;

	for (i = 1; i < n; ++i)
		if (find_max_absolute(array[i], *m) != index)
			return 0;
	delete_column_special(array, n, *m, index);
	(*m)--;
	return 1;
}
