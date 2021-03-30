
#ifndef MATRIX_HPP
#define MATRIX_HPP

// Include
#include <cmath>

// #define USECORE
#ifdef USECORE
#ifndef CORE_LEVEL
#define CORE_LEVEL 3
#endif
#include <CORE.h>
#endif

class Matrix {
public:
  // Con- and destructors
  Matrix();
  Matrix(int, int);
  ~Matrix();

  // Public access modifiers
  double getEntry(int, int);
  bool setEntry(int, int, double);

  // Public utility functions
  Matrix operator*(Matrix);
  Matrix operator*(double);
  Matrix operator/(double);
  Matrix operator+(Matrix);
  Matrix operator-(Matrix);
  // Matrix operator = (Matrix);

  double len();
  Matrix transpose();
  void print();

  double *inverse(double *);

private:
  // Private access modifiers
  //

  // Private utility functions
  //

  // Private variables
  int m, n;
  double **a;
};

#endif
