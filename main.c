#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

#define PX 100
#define PY 40

float cubed[] = {
    -1, -1,  1, /* front verts */
     1, -1,  1,
    -1,  1,  1,
     1,  1,  1,
    -1, -1, -1, /* back verts */
     1, -1, -1,
    -1,  1, -1,
     1,  1, -1
};

float cx=0, cy=0, cz=5; // Position of the camera
float rx=0, ry=0, rz=0; // Orientation of the camera

float s = 0, f = 0.05;

float ex=0.06, ey=0.048; // Display surface

// Transpose a 3d point into a 2d point
vec2d transpose_point(float ax, float ay, float az)
{
    float rpd[] = {
        2*ax - cx,
        2*ay - cy,
        2*az - cz
    };
    matrix pos = matrix_from_array(rpd, 3, 1);

    float rotxd[] = {
        1,        0,       0,
        0,  cos(rz), sin(rx),
        0, -sin(rx), cos(rx)
    };
    matrix rotx = matrix_from_array(rotxd, 3, 3);

    float rotyd[] = {
        cos(ry), 0, -sin(ry),
        0,       1,        0,
        sin(ry), 0,  cos(ry)
    };
    matrix roty = matrix_from_array(rotyd, 3, 3);

    float rotzd[] = {
        cos(rz), sin(rz), 0,
       -sin(rz), cos(rz), 0,
       0,        0,       1
    };
    matrix rotz = matrix_from_array(rotzd, 3, 3);

    float projd[] = {
        (f*PX)/(2*ex), s,             0,
        0,             (f*PY)/(2*ey), 0,
        0,             -1,            0
    };
    matrix proj = matrix_from_array(projd, 3, 3);

    matrix d = matrix_multiply(proj, matrix_multiply(rotx, matrix_multiply(roty, matrix_multiply(rotz, pos))));
    float dx = matrix_get(d, 0, 0);
    float dy = matrix_get(d, 1, 0);
    float dz = matrix_get(d, 2, 0);

    float bx = dx/dz;
    float by = dy/dz;
    return (vec2d) { .x = round(bx), .y = round(by) };
}

void print_scr(char scr[PY][PX])
{
    //system("clear");
    for (int i = 0; i < PY; i++) {
        for (int j = 0; j < PX; j++) {
            // Make the origin at the center of the array
            printf("%c", scr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char scr[PY][PX];
    memset(scr, ' ', PX*PY);

    matrix cube_verts = matrix_from_array(cubed, 8, 3);
    for (int i = 0; i < cube_verts.rows; i++) {
        vec2d t = transpose_point(
            matrix_get(cube_verts, i, 0),
            matrix_get(cube_verts, i, 1),
            matrix_get(cube_verts, i, 2)
        );
        vec2d_print(t);
        //memset(&scr[t.y][t.x], '*', 1);
        int tmx = t.x + PX/2;
        int tmy = t.y + PY/2 + 1;
        printf("mapped coords: %d, %d\n", tmx, tmy);
        memset(scr[tmy]+tmx, '*', 1);
        //printf("thing: %c\n", scr[t.y][t.x]);
        //printf("thing: %c\n", scr[t.y-1][t.x]);
    }
    
    print_scr(scr);

    return 0;
}
