#include "h.h"

int main(void)
{
	FILE *f;
	int n;
	t_line *arr;
	double a, b;

	f = fopen("data", "r");
	fscanf(f, "%d", &n);
	arr = get_intervals(n, f);
	
	sort_intervals(arr, n);
	
	arr = merge_intervals(arr, &n);
	
	print_intervals(arr, n);

	scanf("%lf", &a);
	scanf("%lf", &b);

	if (is_in_interavals(arr, n, a, b))
		printf("Yes\n");
	else
		printf("No\n");
	free(arr);
	fclose(f);
	return 0;
}
