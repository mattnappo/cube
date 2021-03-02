#include <stdio.h>
#include "matrix.h"

void simple()
{
    matrix m1 = matrix_init(2, 3);
    matrix_print(m1);
    matrix_set(m1, 2, 0, 0);
    matrix_set(m1, 1, 0, 1);
    matrix_set(m1, 4, 0, 2);
    matrix_set(m1, 0, 1, 0);
    matrix_set(m1, 1, 1, 1);
    matrix_set(m1, 1, 1, 2);
    // matrix_print(m1);

    printf("%f\n", matrix_get(m1, 0, 0));
    printf("%f\n", matrix_get(m1, 1, 2));

    matrix_destroy(m1);
}

void other()
{
    matrix m1 = matrix_init(2, 3);
    matrix_print(m1);
    matrix_set(m1, 2, 0, 0);
    matrix_set(m1, 1, 0, 1);
    matrix_set(m1, 4, 0, 2);
    matrix_set(m1, 0, 1, 0);
    matrix_set(m1, 1, 1, 1);
    matrix_set(m1, 1, 1, 2);
    matrix_print(m1);

    float m2d[] = {
        4, 3, 2, 1,
        1, 2, 3, 4,
        5, 6, 7, 8
    };
    matrix m2 = matrix_from_array(m2d, 3, 4);
    matrix_print(m2);

    matrix m3 = matrix_multiply(m1, m2);
    matrix_print(m3);

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);

    float m4d[] = {
        2, 1, 4,
        0, 1, 1
    };
    matrix m4 = matrix_from_array(m4d, 2, 3);
    float m5d[] = {
        6, 3, -1, 0,
        1, 1,  0, 4,
       -2, 5,  0, 2
    };
    matrix m5 = matrix_from_array(m5d, 3, 4);
    matrix m6 = matrix_multiply(m4, m5);
    matrix_print(m6);

    matrix_destroy(m4);
    matrix_destroy(m5);
    matrix_destroy(m6);
}

int main()
{
    simple();
    other();

    return 0;
}

