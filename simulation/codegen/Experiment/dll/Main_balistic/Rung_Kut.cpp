//
// File: Rung_Kut.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 21:18:08
//

// Include Files
#include "Rung_Kut.h"
#include "Main_balistic.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// %% Метод Рунге-Кутты 4-го порядка
// Arguments    : const emxArray_real_T *t
//                emxArray_real_T *VECTOR
// Return Type  : void
//
void Rung_Kut(const emxArray_real_T *t, emxArray_real_T *VECTOR)
{
  int i;
  int b_i;
  int r_tmp;
  int b_r_tmp;
  double r;
  double d;
  double d1;
  double d2;
  double GM_P;
  double K1[6];
  double K1_tmp_tmp;
  double coor[6];
  double K2[6];
  double K3[6];
  double b_coor[6];
  i = t->size[1];
  for (b_i = 0; b_i <= i - 2; b_i++) {
    r_tmp = 6 * b_i + 1;
    b_r_tmp = 6 * b_i + 2;
    r = std::sqrt((VECTOR->data[6 * b_i] * VECTOR->data[6 * b_i] + VECTOR->
                   data[r_tmp] * VECTOR->data[r_tmp]) + VECTOR->data[b_r_tmp] *
                  VECTOR->data[b_r_tmp]);
    d = VECTOR->data[6 * b_i] / r;
    d1 = VECTOR->data[r_tmp] / r;
    d2 = VECTOR->data[b_r_tmp] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K1[0] = VECTOR->data[6 * b_i + 3];
    K1[1] = VECTOR->data[6 * b_i + 4];
    K1[2] = VECTOR->data[6 * b_i + 5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K1[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K1[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K1[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + K1[r_tmp] / 2.0;
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K2[0] = coor[3];
    K2[1] = coor[4];
    K2[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K2[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K2[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K2[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + K2[r_tmp] / 2.0;
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K3[0] = coor[3];
    K3[1] = coor[4];
    K3[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K3[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K3[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K3[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);

    // clear coor_2 coor_3 coor_4
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + K3[r_tmp];
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    b_coor[0] = coor[3];
    b_coor[1] = coor[4];
    b_coor[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    b_coor[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 -
      K1_tmp_tmp);
    b_coor[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    b_coor[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      VECTOR->data[r_tmp + 6 * (b_i + 1)] = VECTOR->data[r_tmp + 6 * b_i] +
        0.16666666666666666 * (((K1[r_tmp] + 2.0 * K2[r_tmp]) + 2.0 * K3[r_tmp])
        + b_coor[r_tmp]);
    }
  }
}

//
// %% Метод Рунге-Кутты 4-го порядка
// Arguments    : const emxArray_real_T *t
//                emxArray_real_T *VECTOR
//                double delta_t
// Return Type  : void
//
void b_Rung_Kut(const emxArray_real_T *t, emxArray_real_T *VECTOR, double
                delta_t)
{
  int i;
  int b_i;
  int r_tmp;
  int b_r_tmp;
  double r;
  double d;
  double d1;
  double d2;
  double GM_P;
  double K1[6];
  double K1_tmp_tmp;
  double coor[6];
  double K2[6];
  double K3[6];
  double a;
  double b_coor[6];
  i = t->size[1];
  for (b_i = 0; b_i <= i - 2; b_i++) {
    r_tmp = 6 * b_i + 1;
    b_r_tmp = 6 * b_i + 2;
    r = std::sqrt((VECTOR->data[6 * b_i] * VECTOR->data[6 * b_i] + VECTOR->
                   data[r_tmp] * VECTOR->data[r_tmp]) + VECTOR->data[b_r_tmp] *
                  VECTOR->data[b_r_tmp]);
    d = VECTOR->data[6 * b_i] / r;
    d1 = VECTOR->data[r_tmp] / r;
    d2 = VECTOR->data[b_r_tmp] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K1[0] = VECTOR->data[6 * b_i + 3];
    K1[1] = VECTOR->data[6 * b_i + 4];
    K1[2] = VECTOR->data[6 * b_i + 5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K1[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K1[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K1[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + delta_t * K1[r_tmp] / 2.0;
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K2[0] = coor[3];
    K2[1] = coor[4];
    K2[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K2[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K2[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K2[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + delta_t * K2[r_tmp] / 2.0;
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K3[0] = coor[3];
    K3[1] = coor[4];
    K3[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K3[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K3[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K3[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);

    // clear coor_2 coor_3 coor_4
    a = delta_t / 6.0;
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + delta_t * K3[r_tmp];
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    b_coor[0] = coor[3];
    b_coor[1] = coor[4];
    b_coor[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    b_coor[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 -
      K1_tmp_tmp);
    b_coor[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    b_coor[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      d = VECTOR->data[r_tmp + 6 * b_i] + a * (((K1[r_tmp] + 2.0 * K2[r_tmp]) +
        2.0 * K3[r_tmp]) + b_coor[r_tmp]);
      K1[r_tmp] = d;
      VECTOR->data[r_tmp + 6 * (b_i + 1)] = d;
    }
  }
}

//
// %% Метод Рунге-Кутты 4-го порядка
// Arguments    : const emxArray_real_T *t
//                emxArray_real_T *VECTOR
// Return Type  : void
//
void c_Rung_Kut(const emxArray_real_T *t, emxArray_real_T *VECTOR)
{
  int i;
  int b_i;
  int r_tmp;
  int b_r_tmp;
  double r;
  double d;
  double d1;
  double d2;
  double GM_P;
  double K1[6];
  double K1_tmp_tmp;
  double coor[6];
  double K2[6];
  double K3[6];
  double b_coor[6];
  i = t->size[1];
  for (b_i = 0; b_i <= i - 2; b_i++) {
    r_tmp = 6 * b_i + 1;
    b_r_tmp = 6 * b_i + 2;
    r = std::sqrt((VECTOR->data[6 * b_i] * VECTOR->data[6 * b_i] + VECTOR->
                   data[r_tmp] * VECTOR->data[r_tmp]) + VECTOR->data[b_r_tmp] *
                  VECTOR->data[b_r_tmp]);
    d = VECTOR->data[6 * b_i] / r;
    d1 = VECTOR->data[r_tmp] / r;
    d2 = VECTOR->data[b_r_tmp] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K1[0] = VECTOR->data[6 * b_i + 3];
    K1[1] = VECTOR->data[6 * b_i + 4];
    K1[2] = VECTOR->data[6 * b_i + 5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K1[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K1[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K1[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + -K1[r_tmp] / 2.0;
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K2[0] = coor[3];
    K2[1] = coor[4];
    K2[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K2[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K2[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K2[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + -K2[r_tmp] / 2.0;
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    K3[0] = coor[3];
    K3[1] = coor[4];
    K3[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    K3[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 - K1_tmp_tmp);
    K3[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    K3[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);

    // clear coor_2 coor_3 coor_4
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      coor[r_tmp] = VECTOR->data[r_tmp + 6 * b_i] + -K3[r_tmp];
    }

    r = std::sqrt((coor[0] * coor[0] + coor[1] * coor[1]) + coor[2] * coor[2]);
    d = coor[0] / r;
    d1 = coor[1] / r;
    d2 = coor[2] / r;
    GM_P = 3.986004418E+14 / (r * r);
    r = 6.378136E+6 / r;
    b_coor[0] = coor[3];
    b_coor[1] = coor[4];
    b_coor[2] = coor[5];
    r *= r;
    K1_tmp_tmp = 5.0 * (d2 * d2);
    b_coor[3] = -GM_P * d - 0.0016239386250000002 * GM_P * d * r * (1.0 -
      K1_tmp_tmp);
    b_coor[4] = -GM_P * d1 - 0.0016239386250000002 * GM_P * d1 * r * (1.0 -
      K1_tmp_tmp);
    b_coor[5] = -GM_P * d2 - 0.0016239386250000002 * GM_P * d2 * r * (3.0 -
      K1_tmp_tmp);
    for (r_tmp = 0; r_tmp < 6; r_tmp++) {
      VECTOR->data[r_tmp + 6 * (b_i + 1)] = VECTOR->data[r_tmp + 6 * b_i] +
        -0.16666666666666666 * (((K1[r_tmp] + 2.0 * K2[r_tmp]) + 2.0 * K3[r_tmp])
        + b_coor[r_tmp]);
    }
  }
}

//
// File trailer for Rung_Kut.cpp
//
// [EOF]
//
