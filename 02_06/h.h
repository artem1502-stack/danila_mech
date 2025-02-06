#ifndef H_H
#define H_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_line
{
	double a;
	double b;
}		t_line;

void	swap_line(t_line *a, t_line *b);
void	swap_double(double *a, double *b);
void	print_intervals(t_line *arr, int n);
void	sort_intervals(t_line *arr, int n);
int		is_in_interavals(t_line *arr, int n, double a, double b);
t_line	*get_intervals(int n, FILE *f);
t_line	*merge_intervals(t_line *arr, int *n);

#endif
