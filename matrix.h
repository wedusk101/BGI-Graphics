//matrix.h
#ifndef MATRIX__H_
#define MATRIX__H_

#include <cmath>
#include "primitives.h"

void rotate(Point &, const double &); // rotates a ray about the origin by an angle of theta radians
void translate(Point &, const int &, const int &); // translates a point P(x,y) by tx and ty 
void scale(Point &, const int &, const int &); // scales a point P(x,y) by sx and sy

#endif