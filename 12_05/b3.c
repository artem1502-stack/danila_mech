#include <stdio.h>
#include <stdlib.h>

//	7. Написать функции, записывающие 0 или 1 в указанный бит
//	данного целого числа и оставляющие остальные биты
//	без изменения.

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

int change_bit(int x, int bit_index, int bit)
{
	if (((x >> bit_index) & 1) != bit)
		x ^= (1 << bit_index);
	return x;
}
/*
-2^31 : 2^31 - 1 

1 бит - знак
31 бит - число

инверсия : ~

0b000000 ... 101010
1b111111 ... 010101

*/
int main(void)
{
	int x = 0b101011, y, bit_index, bit;


	print_binary(x);
	scanf("%d", &bit_index);
	scanf("%d", &bit);
	y = change_bit(x, bit_index, bit);
	print_binary(y);
	printf("x = %d, y = %d\n", x, y);
}
