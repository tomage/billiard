
#include "CVector.hxx"

CVector::CVector() {}

CVector::CVector(double a, double b, double c) {
  x = a;
  y = b;
  z = c;
}

CVector CVector::operator+(CVector param) {
  CVector temp;
  temp.x = x + param.x;
  temp.y = y + param.y;
  temp.z = z + param.z;
  return (temp);
}
CVector CVector::operator-(CVector param) {
  CVector temp;
  temp.x = x - param.x;
  temp.y = y - param.y;
  temp.z = z - param.z;
  return (temp);
}
CVector CVector::operator*(double d) {
  CVector temp;
  temp.x = x * d;
  temp.y = y * d;
  temp.z = z * d;
  return (temp);
}
CVector CVector::operator/(double d) {
  CVector temp;
  temp.x = x / d;
  temp.y = y / d;
  temp.z = z / d;
  return (temp);
}

double CVector::dot(CVector param) {
  return x * param.x + y * param.y + z * param.z;
}
CVector CVector::cross(CVector param) {
  CVector temp;
  temp.x = y * param.z - z * param.y;
  temp.y = -x * param.z + z * param.x;
  temp.z = x * param.y - y * param.x;
  return (temp);
}

void CVector::normalize() {
  double len = sqrt(x * x + y * y + z * z);
  x /= len;
  y /= len;
  z /= len;
}

void CVector::setLength(double d) {

  // First normalize
  normalize();

  // Then multiply factors by length
  x *= d;
  y *= d;
  z *= d;
}
