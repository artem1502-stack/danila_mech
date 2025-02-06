#include <stdio.h>
#include <stdlib.h>

typedef struct s_our_x
{
	int a;
	float b;
	char c;
} t_our_x;

typedef int chislo;


int main(void)
{
	t_our_x t;
	chislo x = 19;

	t.a = x;
	t.b = 7.1;
	t.c = 'z';

	printf("%d %f %c\n", t.a, t.b, t.c);
}