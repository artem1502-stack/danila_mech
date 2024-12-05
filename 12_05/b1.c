#include <stdio.h>
#include <stdlib.h>

//100

void print_binary(int x)
{
	int i = 0;
	if (!x)
	{
		printf("0\n");
		return ;
	}
	while (x >> i)
		i++;
	i--;
	while (i >= 0)
		printf("%d", (x >> (i--)) & 1);
	printf("\n");
}

int main(void)
{
	int x = 0b10101011, y, z;

	y = x << 3;
	z = x >> 3;


	print_binary(x);
	print_binary(y);
	print_binary(z);
	printf("x = %d, y = %d, z = %d\n", x, y, z);

}
