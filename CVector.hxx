
#ifndef CVECTOR_HXX
#define CVECTOR_HXX

#include "math.h"
#include <iostream>
using namespace std;

class CVector {
public:
  double x, y, z;
  CVector();
  CVector(double, double, double);
  CVector operator+(CVector);
  CVector operator-(CVector);
  CVector operator*(double);
  CVector operator/(double);
  double dot(CVector);    // Cross product
  CVector cross(CVector); // Cross product

  void normalize();
  void setLength(double);
};

#endif
