#include "h.h"

/*
В файле data.dat задан двумерный массив целых чисел
с различным количеством элементов в каждой строке.
Элементы массива задаются через пробел. 
Ограничения на количество строк в массиве нет.
Ввести двумерный массив из файла в массив в 
программе, отведя соответствующим образом память. 

Определить, существует ли элемент равный среднему 
арифметическому всех. Если да - удалить строку

*/



int main(void)
{
	int **arr, *m, n, i, j;

	FILE *f = fopen("data", "r");
	if (!f)
		printf("Error\n");
	arr = read_hard_array(f, &n, &m);
	fclose(f);
	print_hard(arr, n, m);
	work_with_middle(arr, &n, m);
	f = fopen("res", "w");
	fprint_hard(f, arr, n, m);
	fclose(f);
	free_hard(arr, n, m);
	return 0;
}
