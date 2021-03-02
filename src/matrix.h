#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix
{
    int rows;
    int cols;
    float *data;
} matrix;

typedef struct vec2d {
    int x;
    int y;
} vec2d;

void vec2d_print(vec2d v);
matrix matrix_init(int rows, int cols);
matrix matrix_from_array(float data[], int rows, int cols);
void matrix_print(matrix m);
float matrix_get(matrix m, int row, int col);
void matrix_set(matrix m, float val, int row, int col);
matrix matrix_multiply(matrix m1, matrix m2);
void matrix_destroy(matrix m);

#endif
