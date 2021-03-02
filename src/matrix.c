#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"

void err_outb(int er, int ec, int r, int c)
{
    printf("ERROR: index (%d, %d) out of bounds of matrix (%d, %d)\n ",
        er, ec, r, c);
}

matrix matrix_init(int rows, int cols)
{
    matrix m = { .rows = rows, .cols = cols };
    m.data = calloc(rows*cols, sizeof(float));
    return m;
}

//matrix matrix_from_array(float data[][], int rows, int cols);

void matrix_print(matrix m)
{
    printf("\n");
    for (int i = 0; i < m.rows; i++) {
        printf("| ");
        for (int j = 0; j < m.cols; j++) {
            printf("%07.3f ", matrix_get(m, i, j));
        }
        printf("|\n");
    }
    printf("\n");
}

float matrix_get(matrix m, int row, int col)
{
    if (row < m.rows && col < m.cols) {
        return m.data[m.cols * row + col];
    }
    err_outb(row, col, m.rows, m.cols);
    return 0.0;
}

void matrix_set(matrix m, float val, int row, int col)
{
    if (row < m.rows && col < m.cols) {
        m.data[m.cols * row + col] = val;
    }
    err_outb(row, col, m.rows, m.cols);
}

matrix matrix_multiply(matrix m1, matrix m2)
{
    if (m1.cols != m2.rows) {
        printf("ERROR: cannot multiply (%d, %d) by (%d, %d)\n", m1.rows, m1.cols, m2.rows, m2.cols);
        return (matrix) {};
    }
    matrix mm = { .rows = m1.rows, .cols = m2.cols };

    // Please don't just me for this
    for (int i = 0; i < m1.rows; ++i) {
        for (int j = 0; j < m2.cols; ++j) {
            for (int k = 0; k < m1.cols; ++k) {
                // mm[i][j] += m1[i][k] * m2[k][j];
                mm.data[mm.cols*i+j] += m1.data[mm.cols*i+k] * m2.data[mm.cols*k+j];
            }
        }
    }

    return mm;
}

void matrix_destroy(matrix m)
{
    free(m.data);
}

