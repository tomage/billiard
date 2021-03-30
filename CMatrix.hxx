
#ifndef CMATRIX_HXX
#define CMATRIX_HXX

// Include
#include <cmath>

// #define USECORE
#ifdef USECORE
#ifndef CORE_LEVEL
#define CORE_LEVEL 3
#endif
#include <CORE.h>
#endif

class CMatrix {
public:
  // Con- and destructors
  CMatrix();
  CMatrix(int, int);
  ~CMatrix();

  // Public access modifiers
  double getEntry(int, int);
  bool setEntry(int, int, double);

  // Public utility functions
  CMatrix operator*(CMatrix);
  CMatrix operator*(double);
  CMatrix operator/(double);
  CMatrix operator+(CMatrix);
  CMatrix operator-(CMatrix);
  // CMatrix operator = (CMatrix);

  double len();
  CMatrix transpose();
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
