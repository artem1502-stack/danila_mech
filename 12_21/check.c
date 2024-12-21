#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *f;
	double a = 0.001;

	f = fopen("data", "w");
	fprintf(f, "Hello world %lf\n", a);
	fclose(f);
}