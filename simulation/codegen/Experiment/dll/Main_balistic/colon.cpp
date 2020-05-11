//
// File: colon.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 21:18:08
//

// Include Files
#include "colon.h"
#include "Main_balistic.h"
#include "Main_balistic_emxutil.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double a
//                double b
//                emxArray_real_T *y
// Return Type  : void
//
void b_eml_float_colon(double a, double b, emxArray_real_T *y)
{
  double ndbl;
  double apnd;
  double cdiff;
  double u0;
  double u1;
  int n;
  int nm1d2;
  int k;
  int y_tmp;
  ndbl = std::floor((b - a) / -1.0 + 0.5);
  apnd = a + -ndbl;
  cdiff = b - apnd;
  u0 = std::abs(a);
  u1 = std::abs(b);
  if ((u0 > u1) || rtIsNaN(u1)) {
    u1 = u0;
  }

  if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + -(ndbl - 1.0);
  } else {
    ndbl++;
  }

  if (ndbl >= 0.0) {
    n = static_cast<int>(ndbl);
  } else {
    n = 0;
  }

  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, nm1d2);
  if (n > 0) {
    y->data[0] = a;
    if (n > 1) {
      y->data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        y_tmp = -(k + 1);
        y->data[k + 1] = a + static_cast<double>(y_tmp);
        y->data[(n - k) - 2] = apnd - static_cast<double>(y_tmp);
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y->data[nm1d2] = a + -static_cast<double>(nm1d2);
        y->data[nm1d2 + 1] = apnd - (-static_cast<double>(nm1d2));
      }
    }
  }
}

//
// Arguments    : double a
//                double b
//                emxArray_real_T *y
// Return Type  : void
//
void eml_float_colon(double a, double b, emxArray_real_T *y)
{
  double ndbl;
  double apnd;
  double cdiff;
  double u0;
  double u1;
  int n;
  int nm1d2;
  int k;
  int y_tmp;
  ndbl = std::floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  u0 = std::abs(a);
  u1 = std::abs(b);
  if ((u0 > u1) || rtIsNaN(u1)) {
    u1 = u0;
  }

  if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }

  if (ndbl >= 0.0) {
    n = static_cast<int>(ndbl);
  } else {
    n = 0;
  }

  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, nm1d2);
  if (n > 0) {
    y->data[0] = a;
    if (n > 1) {
      y->data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        y_tmp = k + 1;
        y->data[k + 1] = a + static_cast<double>(y_tmp);
        y->data[(n - k) - 2] = apnd - static_cast<double>(y_tmp);
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y->data[nm1d2] = a + static_cast<double>(nm1d2);
        y->data[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
      }
    }
  }
}

//
// File trailer for colon.cpp
//
// [EOF]
//
