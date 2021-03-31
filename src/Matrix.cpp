#include <iostream>

// Header
#include "Matrix.hpp"
#include <cmath>

// Con- and destructors ==================================================== //

Matrix::Matrix() {
#ifdef USECORE
  setDefaultInputDigits(CORE_INFTY);
  setDefaultRelPrecision(120);
#endif
  Matrix(3, 3);
}
Matrix::Matrix(int i, int j) {
#ifdef USECORE
  setDefaultInputDigits(CORE_INFTY);
  setDefaultRelPrecision(120);
#endif

  m = i;
  n = j;
  a = new double *[m];
  for (int i = 0; i < m; i++)
    a[i] = new double[n];

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      a[i][j] = 0.0;
}

Matrix::~Matrix() {
  // Nothing...
}

// Public access modifiers ================================================= //

double Matrix::getEntry(int i, int j) { return this->a[i][j]; }
bool Matrix::setEntry(int i, int j, double d) {
  a[i][j] = d;
  return true;
}

// Public utility functions ================================================ //

Matrix Matrix::operator*(Matrix _Matrix) {
  Matrix temp = Matrix(m, _Matrix.n);
  if (n != _Matrix.m) {
    std::cout << "ERROR: Matrices not compatible! Product between " << m << "x"
              << n << " matrix and " << _Matrix.m << "x" << _Matrix.n
              << " matrix." << std::endl;
    return temp;
  }

  double e;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < _Matrix.n; j++) {
      e = 0.0;
      for (int k = 0; k < n; k++)
        e += getEntry(i, k) * _Matrix.getEntry(k, j);
      temp.setEntry(i, j, e);
    }
  }
  return temp;
}

Matrix Matrix::operator*(double d) {
  Matrix temp = Matrix(m, n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      temp.setEntry(i, j, getEntry(i, j) * d);
    }
  }
  return temp;
}
Matrix Matrix::operator/(double d) {
  Matrix temp = Matrix(m, n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      temp.setEntry(i, j, getEntry(i, j) / d);
    }
  }
  return temp;
}

Matrix Matrix::operator+(Matrix _Matrix) {
  Matrix temp = Matrix(m, n);
  if (n != _Matrix.n || m != _Matrix.m) {
    std::cout << "ERROR: Matrices not compatible! + operator"
              << " n=" << n << " != _n=" << _Matrix.n << " and m=" << m
              << " != _m=" << _Matrix.m << std::endl;
    return temp;
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < _Matrix.n; j++) {
      temp.setEntry(i, j, getEntry(i, j) + _Matrix.getEntry(i, j));
    }
  }
  return temp;
}

Matrix Matrix::operator-(Matrix _Matrix) {
  Matrix temp = Matrix(m, n);
  if (n != _Matrix.n || m != _Matrix.m) {
    std::cout << "ERROR: Matrices not compatible! - operator"
              << " n=" << n << " != _n=" << _Matrix.n << " and m=" << m
              << " != _m=" << _Matrix.m << std::endl;
    return temp;
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < _Matrix.n; j++) {
      temp.setEntry(i, j, getEntry(i, j) - _Matrix.getEntry(i, j));
    }
  }
  return temp;
}

double Matrix::len() {
  //	std::cout << "len:" << m << " " << n << std::endl;
  double dRet = 0.0;
  if (n == 1) {
    for (int i = 0; i < m; i++) {
      dRet += pow(a[i][0], (double)2.0);
    }
  } else if (m == 1) {
    for (int i = 0; i < n; i++) {
      dRet += pow(a[0][i], (double)2.0);
    }
  } else {
    std::cout << "ERROR: len() not used correctly" << std::endl;
    return 0;
  }
  return sqrt(dRet);
}

Matrix Matrix::transpose() {
  Matrix temp = Matrix(n, m);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      temp.setEntry(j, i, getEntry(i, j));
    }
  }
  return temp;
}

void Matrix::print() {
  std::cout << "Matrix:" << std::endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}

double *Matrix::inverse(double *d) {
  double detA = d[0] * (d[4] * d[8] - d[5] * d[7]) +
                d[1] * (d[5] * d[6] - d[3] * d[8]) +
                d[2] * (d[3] * d[7] - d[4] * d[6]);
  if (detA != 0 && 1 / detA != 0) {
    double *dT = new double[9];
    dT[0] = detA * (d[4] * d[8] - d[5] * d[7]);
    dT[1] = detA * (d[2] * d[7] - d[1] * d[8]);
    dT[2] = detA * (d[1] * d[5] - d[2] * d[4]);
    dT[3] = detA * (d[5] * d[6] - d[3] * d[8]);
    dT[4] = detA * (d[0] * d[8] - d[2] * d[6]);
    dT[5] = detA * (d[2] * d[3] - d[0] * d[5]);
    dT[6] = detA * (d[3] * d[7] - d[4] * d[6]);
    dT[7] = detA * (d[1] * d[6] - d[0] * d[7]);
    dT[8] = detA * (d[0] * d[4] - d[1] * d[3]);
    return dT;
  } else {
    std::cerr << "Could not invert matrix:";
    // print3x3 (d);
    return d;
  }
}
