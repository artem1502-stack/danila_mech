#include <stdio.h>
#include <stdlib.h>

//100

void print_binary(int x)
{
	int i = 1, temp;

	if (x == 0)
	{
		printf("0\n");
		return ;
	}

	while (x >> i != 0)
		i++;
	
	i--;
	while (i >= 0)
	{
		temp = x >> i;
		printf("%d", temp & 1);
		i--;
	}
	printf("\n");
}

int main(void)
{
	int x = 0b10101011, y = 0b10000011, z;

	z = x ^ y;

	print_binary(x);
	print_binary(y);
	printf("  ");
	print_binary(z);
	printf("x = %d, y = %d, z = %d\n", x, y, z);

}
