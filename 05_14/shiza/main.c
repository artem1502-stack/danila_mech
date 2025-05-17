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
	int **arr, n;

	FILE *f = fopen("data", "r");
	if (!f)
	{
		printf("Error\n");
		return -1;
	}
	arr = read_hard_array(f, &n);

	if (!arr)
	{
		fclose(f);
		return -1;
	}
	fclose(f);
	print_hard(arr, n);
	
	work_with_middle(arr, &n);

	f = fopen("res", "w");
	fprint_hard(f, arr, n);
	fclose(f);
	free(arr);
	return 0;
}
