#include <stdio.h>
#include <stdlib.h>

/*

15. Заменить все локальные минимумы в массиве одним 
элементом, значение которого равно элементу массива 
с минимальным значением. Функция должна возвращать
количество элементов в получившемся массиве.

*/

double *get_array(FILE *f, int *n)
{

}

int main(void)
{
	FILE *f;
	double x;
	double mas[20];
	int i, n = 0; 



	f = fopen("data", "r");

	while (fscanf(f, "%lf", &x) == 1)
	{
		mas[n] = x;
		n++;
	}

	for (i = 0; i < n; i++)
		printf("%lf\n", mas[i]);

	fclose(f);

	return 0;
}
