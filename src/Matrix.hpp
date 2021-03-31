
#ifndef MATRIX_HPP
#define MATRIX_HPP

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
  int m, n;
  double **a;
};

#endif
