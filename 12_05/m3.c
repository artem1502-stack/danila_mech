#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(void)
{
	int x = 0;
	int *y;

	y = &x;

	*y = 5;

	x = 10;

	printf("%d\n", *y);
}