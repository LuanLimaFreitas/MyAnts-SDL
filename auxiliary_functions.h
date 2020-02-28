#ifndef AUXILIARY_FUNCTIONS_H
#define AUXILIARY_FUNCTIONS_H

#include "parameters.h"
#include<random>
#include<cmath>
#include<iostream>
using namespace std;

//  Randoms
extern double Normal();
extern double SmallNormal();
extern double UniformAngle();
extern double Uniform();
extern double UniformInteger();
extern int Geometric();

extern float Angle(float X, float Y);
/// Computes arctan(Y/X)
extern float AngleBetween(float x1, float y1, float x2, float y2);
/// Computes angle between vectors (x1,y1) and (x2,y2)

extern float Heat(float XX, float YY, float elapsed_time, float amount);
/// Heat Equation Fundamental Solution

extern double Sign(double aa);

extern void Periodify(float& x, float& y);

#endif // AUXILIARY_FUCNTIONS_H
