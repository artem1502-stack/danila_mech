#ifndef H_H
#define H_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

#define START_LINE_MAX 4
#define START_ELEMENT_MAX 8

int	resize_elem(int ***arr, int *m, int n, int n_max, int size);
int	resize_lines(int ***arr, int **m, int n, int n_max, int size);

int		line_to_array(FILE *f, int ***arr, int *m, int n_cur, int n_max,
					int *el_cur, int *el_max);
int		**read_hard_array(FILE *f, int *n);

void	work_with_middle(int **arr, int *n);

void	print_hard(int **arr, int n);
void	fprint_hard(FILE *f, int **arr, int n);

#endif
