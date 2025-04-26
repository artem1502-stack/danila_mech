#include "h.h"

int main(void)
{
	int **arr, n, m;

	FILE *f = fopen("data", "r");
	arr = read_darray_special(f, &n, &m);
	fclose(f);
	check_max(arr, n, &m);
	print_darray(arr, n, m);
	f = fopen("res", "w");
	fprint_darray(f, arr, n, m);
	free(arr);
	return 0;
}
