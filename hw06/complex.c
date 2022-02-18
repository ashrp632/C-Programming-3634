#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "complex.h"


c_num c_constructor(float a, float b) {
  c_num num;
  num.real = a;
  num.imagine = b;
  return num;
}

float c_real(c_num x){
  return x.real;
}

float c_imag(c_num x){
  return x.imagine;
}

c_num c_add(c_num x, c_num y){
  c_num z;
  z.real = x.real + y.real;
  z.imagine = x.imagine + y.imagine;
  return z;
}

c_num c_sub(c_num x, c_num y){
  c_num z;
  z.real = x.real - y.real;
  z.imagine = x.imagine-y.imagine;
  return z;
}

c_num c_mul(c_num x, c_num y){
  c_num z;
  z.real = x.real*y.real - x.imagine*y.imagine;
  z.imagine = x.real*y.imagine + x.imagine*y.real;
  return z;
}

c_num c_div(c_num x, c_num y){
  c_num z;
  z.real = (x.real * y.real + x.imagine * y.imagine)/(y.real*y.real + y.imagine*y.imagine);
  z.imagine = (x.imagine * y.imagine - x.real*y.imagine)/(y.real*y.real+y.imagine*y.imagine);
  return z;
}

c_num c_conj(c_num x){
  x.imagine = -1*x.imagine;
  return x;
}

c_num c_mod(c_num x){
  x.real = x.real*x.real;
  x.imagine = x.imagine*x.imagine;
  return x;
}
