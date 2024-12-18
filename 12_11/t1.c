#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//	1 1 2 3 5 8 13 21

int fib(int n)
{
	if (n <= 1)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

int main(void)
{
	int i, n = 20;

	for(i = 0; i < n; ++i)
		printf("%d\n", fib(i));
	return 0;
}
