#include <stdio.h>
#include <stdlib.h>

#define STANDART_SIZE 1024

int main(void)
{
	FILE *f;
	double a = 0.01;
	int arr[STANDART_SIZE];

	f = fopen("data", "w");
	fprintf(f, "Hello world %lf\n", a);
	fclose(f);
}