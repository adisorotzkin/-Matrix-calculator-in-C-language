#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 4

typedef double matrix[SIZE][SIZE];

void add_mat(matrix, matrix, matrix);
void sub_mat(matrix, matrix, matrix);
void mul_scalar(matrix, double, matrix);
void mul_mat(matrix, matrix, matrix);
void trans_mat(matrix, matrix);
