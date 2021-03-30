#include <iostream>

// Header
#include "CMatrix.hxx"

// CORE library fix
#ifdef USECORE
#define pow(x, y) pow((x).doubleValue(), (y).doubleValue())
#define cos(x) cos((x).doubleValue())
#define sin(x) sin((x).doubleValue())
// #define rotateX(x, y, z, a) rotateX(x, y, z, a.doubleValue())
// #define rotateY(x, y, z, a) rotateY(x, y, z, a.doubleValue())
// #define rotateZ(x, y, z, a) rotateZ(x, y, z, a.doubleValue())
#endif

// Con- and destructors ==================================================== //

CMatrix::CMatrix() {
#ifdef USECORE
  setDefaultInputDigits(CORE_INFTY);
  setDefaultRelPrecision(120);
#endif
  CMatrix(3, 3);
}
CMatrix::CMatrix(int i, int j) {
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

CMatrix::~CMatrix() {
  // Nothing...
}

// Public access modifiers ================================================= //

double CMatrix::getEntry(int i, int j) { return this->a[i][j]; }
bool CMatrix::setEntry(int i, int j, double d) {
  a[i][j] = d;
  return true;
}

// Public utility functions ================================================ //

CMatrix CMatrix::operator*(CMatrix _CMatrix) {
  CMatrix temp = CMatrix(m, _CMatrix.n);
  if (n != _CMatrix.m) {
    std::cout << "ERROR: Matrices not compatible! Product between " << m << "x"
              << n << " matrix and " << _CMatrix.m << "x" << _CMatrix.n
              << " matrix." << std::endl;
    return temp;
  }

  double e;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < _CMatrix.n; j++) {
      e = 0.0;
      for (int k = 0; k < n; k++)
        e += getEntry(i, k) * _CMatrix.getEntry(k, j);
      temp.setEntry(i, j, e);
    }
  }
  return temp;
}

CMatrix CMatrix::operator*(double d) {
  CMatrix temp = CMatrix(m, n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      temp.setEntry(i, j, getEntry(i, j) * d);
    }
  }
  return temp;
}
CMatrix CMatrix::operator/(double d) {
  CMatrix temp = CMatrix(m, n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      temp.setEntry(i, j, getEntry(i, j) / d);
    }
  }
  return temp;
}

CMatrix CMatrix::operator+(CMatrix _CMatrix) {
  CMatrix temp = CMatrix(m, n);
  if (n != _CMatrix.n || m != _CMatrix.m) {
    std::cout << "ERROR: Matrices not compatible! + operator"
              << " n=" << n << " != _n=" << _CMatrix.n << " and m=" << m
              << " != _m=" << _CMatrix.m << std::endl;
    return temp;
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < _CMatrix.n; j++) {
      temp.setEntry(i, j, getEntry(i, j) + _CMatrix.getEntry(i, j));
    }
  }
  return temp;
}

CMatrix CMatrix::operator-(CMatrix _CMatrix) {
  CMatrix temp = CMatrix(m, n);
  if (n != _CMatrix.n || m != _CMatrix.m) {
    std::cout << "ERROR: Matrices not compatible! - operator"
              << " n=" << n << " != _n=" << _CMatrix.n << " and m=" << m
              << " != _m=" << _CMatrix.m << std::endl;
    return temp;
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < _CMatrix.n; j++) {
      temp.setEntry(i, j, getEntry(i, j) - _CMatrix.getEntry(i, j));
    }
  }
  return temp;
}

double CMatrix::len() {
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

CMatrix CMatrix::transpose() {
  CMatrix temp = CMatrix(n, m);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      temp.setEntry(j, i, getEntry(i, j));
    }
  }
  return temp;
}

void CMatrix::print() {
  std::cout << "Matrix:" << std::endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}

double *CMatrix::inverse(double *d) {
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

// Private access modifiers ================================================ //

//

// Private utility functions =============================================== //

//
