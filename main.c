#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

int main()
{
    //float px, py     = 0; // 2d screen resolution
    float ax=0, ay=0, az=0; // 3d coords (run for each point in cube)
    float cx=0, cy=0, cz=0; // Position of the camera
    float rx=0, ry=0, rz=0; // Orientation of the camera
    float ex=0, ey=0, ez=0; // Display surface
    float bx=0, by=0;       // 2d coordinates of point (to solve for)

    float rpd[] = {
        ax - cx,
        ay - cy,
        az - cz
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

    matrix d = matrix_multiply(rotx, matrix_multiply(roty, matrix_multiply(rotz, pos)));
    float dx = matrix_get(d, 0, 0);
    float dy = matrix_get(d, 1, 0);
    float dz = matrix_get(d, 2, 0);

    bx = ez/dz * dx + ex;
    by = ez/dz * dy + ey;

    return 0;
}
