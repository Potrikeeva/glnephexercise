//
// File: Optimization.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 21:18:08
//

// Include Files
#include "Optimization.h"
#include "Main_balistic.h"
#include "Main_balistic_emxutil.h"
#include "Rung_Kut.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double x
//                double y
//                double z
//                double V_x
//                double V_y
//                double V_z
//                double JJ_x
//                double JJ_y
//                double JJ_z
//                double t_start
//                double t_e
//                double t_end
//                emxArray_real_T *Optim
// Return Type  : void
//
void Optimization(double x, double y, double z, double V_x, double V_y, double
                  V_z, double JJ_x, double JJ_y, double JJ_z, double t_start,
                  double t_e, double t_end, emxArray_real_T *Optim)
{
  emxArray_real_T *t;
  emxArray_real_T *VECTOR;
  int i;
  emxArray_real_T *t1;
  emxArray_real_T *VECTOR1;
  emxArray_real_T *t2;
  emxArray_real_T *VECTOR2;
  emxArray_real_T *B;
  emxArray_real_T *b_B;
  emxArray_real_T *c_B;
  emxArray_real_T *d_B;
  emxArray_real_T *e_B;
  emxArray_real_T *f_B;
  emxArray_real_T *g_B;
  int loop_ub;
  double VECTOR1_tmp[6];
  int nx;
  int n;
  double d;
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  boolean_T empty_non_axis_sizes;
  signed char input_sizes_idx_0;
  signed char sizes_idx_0;
  emxInit_real_T(&t, 2);
  emxInit_real_T(&VECTOR, 2);
  i = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = 1;
  emxEnsureCapacity_real_T(t, i);
  t->data[0] = 0.0;
  i = VECTOR->size[0] * VECTOR->size[1];
  VECTOR->size[0] = 1;
  VECTOR->size[1] = 1;
  emxEnsureCapacity_real_T(VECTOR, i);
  VECTOR->data[0] = 0.0;
  emxInit_real_T(&t1, 2);
  emxInit_real_T(&VECTOR1, 2);
  emxInit_real_T(&t2, 2);
  emxInit_real_T(&VECTOR2, 2);
  emxInit_real_T(&B, 1);
  emxInit_real_T(&b_B, 2);
  emxInit_real_T(&c_B, 2);
  emxInit_real_T(&d_B, 2);
  emxInit_real_T(&e_B, 2);
  emxInit_real_T(&f_B, 2);
  emxInit_real_T(&g_B, 2);
  if (((t_e == t_start) && (t_end > t_e)) || ((t_e < t_start) && (t_end > t_e)))
  {
    if (t_end - 1.0 < t_start) {
      t->size[0] = 1;
      t->size[1] = 0;
    } else if ((rtIsInf(t_start) || rtIsInf(t_end - 1.0)) && (t_start == t_end -
                1.0)) {
      i = t->size[0] * t->size[1];
      t->size[0] = 1;
      t->size[1] = 1;
      emxEnsureCapacity_real_T(t, i);
      t->data[0] = rtNaN;
    } else if (std::floor(t_start) == t_start) {
      i = t->size[0] * t->size[1];
      t->size[0] = 1;
      loop_ub = static_cast<int>(std::floor((t_end - 1.0) - t_start));
      t->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(t, i);
      for (i = 0; i <= loop_ub; i++) {
        t->data[i] = t_start + static_cast<double>(i);
      }
    } else {
      eml_float_colon(t_start, t_end - 1.0, t);
    }

    //  временной ветор прогноза
    i = VECTOR->size[0] * VECTOR->size[1];
    VECTOR->size[0] = 6;
    VECTOR->size[1] = t->size[1];
    emxEnsureCapacity_real_T(VECTOR, i);
    loop_ub = 6 * t->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[i] = 0.0;
    }

    VECTOR->data[0] = x;
    VECTOR->data[1] = y;
    VECTOR->data[2] = z;
    VECTOR->data[3] = V_x;
    VECTOR->data[4] = V_y;
    VECTOR->data[5] = V_z;
    i = VECTOR1->size[0] * VECTOR1->size[1];
    VECTOR1->size[0] = VECTOR->size[0];
    VECTOR1->size[1] = VECTOR->size[1];
    emxEnsureCapacity_real_T(VECTOR1, i);
    loop_ub = VECTOR->size[0] * VECTOR->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR1->data[i] = VECTOR->data[i];
    }

    Rung_Kut(t, VECTOR1);
    i = VECTOR->size[0] * VECTOR->size[1];
    VECTOR->size[0] = 6;
    VECTOR->size[1] = VECTOR1->size[1];
    emxEnsureCapacity_real_T(VECTOR, i);
    loop_ub = VECTOR1->size[0] * VECTOR1->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[i] = VECTOR1->data[i];
    }
  } else if ((t_e > t_start) && (t_end > t_e)) {
    if (t_end - 1.0 < t_e) {
      t1->size[0] = 1;
      t1->size[1] = 0;
    } else if (rtIsInf(t_end - 1.0) && (t_e == t_end - 1.0)) {
      i = t1->size[0] * t1->size[1];
      t1->size[0] = 1;
      t1->size[1] = 1;
      emxEnsureCapacity_real_T(t1, i);
      t1->data[0] = rtNaN;
    } else if (std::floor(t_e) == t_e) {
      i = t1->size[0] * t1->size[1];
      t1->size[0] = 1;
      loop_ub = static_cast<int>(std::floor((t_end - 1.0) - t_e));
      t1->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(t1, i);
      for (i = 0; i <= loop_ub; i++) {
        t1->data[i] = t_e + static_cast<double>(i);
      }
    } else {
      eml_float_colon(t_e, t_end - 1.0, t1);
    }

    i = VECTOR1->size[0] * VECTOR1->size[1];
    VECTOR1->size[0] = 6;
    VECTOR1->size[1] = t1->size[1];
    emxEnsureCapacity_real_T(VECTOR1, i);
    loop_ub = 6 * t1->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR1->data[i] = 0.0;
    }

    VECTOR1_tmp[0] = x;
    VECTOR1_tmp[1] = y;
    VECTOR1_tmp[2] = z;
    VECTOR1_tmp[3] = V_x;
    VECTOR1_tmp[4] = V_y;
    VECTOR1_tmp[5] = V_z;
    for (i = 0; i < 6; i++) {
      VECTOR1->data[i] = VECTOR1_tmp[i];
    }

    b_Rung_Kut(t1, VECTOR1, 1.0);
    if (t_e < t_start) {
      t2->size[0] = 1;
      t2->size[1] = 0;
    } else if (rtIsInf(t_start) && (t_e == t_start)) {
      i = t2->size[0] * t2->size[1];
      t2->size[0] = 1;
      t2->size[1] = 1;
      emxEnsureCapacity_real_T(t2, i);
      t2->data[0] = rtNaN;
    } else if (std::floor(t_e) == t_e) {
      i = t2->size[0] * t2->size[1];
      t2->size[0] = 1;
      loop_ub = static_cast<int>(std::floor(-(t_start - t_e)));
      t2->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(t2, i);
      for (i = 0; i <= loop_ub; i++) {
        t2->data[i] = t_e - static_cast<double>(i);
      }
    } else {
      b_eml_float_colon(t_e, t_start, t2);
    }

    i = VECTOR2->size[0] * VECTOR2->size[1];
    VECTOR2->size[0] = 6;
    VECTOR2->size[1] = t2->size[1];
    emxEnsureCapacity_real_T(VECTOR2, i);
    loop_ub = 6 * t2->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR2->data[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      VECTOR2->data[i] = VECTOR1_tmp[i];
    }

    b_Rung_Kut(t2, VECTOR2, -1.0);
    if (2 > VECTOR1->size[1]) {
      i = 0;
      b_loop_ub = 0;
    } else {
      i = 1;
      b_loop_ub = VECTOR1->size[1];
    }

    n = VECTOR2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = VECTOR2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1)];
    }

    n = B->size[0];
    nx = b_B->size[0] * b_B->size[1];
    b_B->size[0] = 1;
    b_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(b_B, nx);
    for (nx = 0; nx < n; nx++) {
      b_B->data[nx] = B->data[nx];
    }

    n = VECTOR2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = VECTOR2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 1];
    }

    n = B->size[0];
    nx = c_B->size[0] * c_B->size[1];
    c_B->size[0] = 1;
    c_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(c_B, nx);
    for (nx = 0; nx < n; nx++) {
      c_B->data[nx] = B->data[nx];
    }

    n = VECTOR2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = VECTOR2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 2];
    }

    n = B->size[0];
    nx = d_B->size[0] * d_B->size[1];
    d_B->size[0] = 1;
    d_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(d_B, nx);
    for (nx = 0; nx < n; nx++) {
      d_B->data[nx] = B->data[nx];
    }

    n = VECTOR2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = VECTOR2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 3];
    }

    n = B->size[0];
    nx = e_B->size[0] * e_B->size[1];
    e_B->size[0] = 1;
    e_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(e_B, nx);
    for (nx = 0; nx < n; nx++) {
      e_B->data[nx] = B->data[nx];
    }

    n = VECTOR2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = VECTOR2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 4];
    }

    n = B->size[0];
    nx = f_B->size[0] * f_B->size[1];
    f_B->size[0] = 1;
    f_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(f_B, nx);
    for (nx = 0; nx < n; nx++) {
      f_B->data[nx] = B->data[nx];
    }

    n = VECTOR2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = VECTOR2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 5];
    }

    n = B->size[0];
    nx = g_B->size[0] * g_B->size[1];
    g_B->size[0] = 1;
    g_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(g_B, nx);
    for (nx = 0; nx < n; nx++) {
      g_B->data[nx] = B->data[nx];
    }

    nx = VECTOR->size[0] * VECTOR->size[1];
    VECTOR->size[0] = 6;
    VECTOR->size[1] = (b_B->size[1] + b_loop_ub) - i;
    emxEnsureCapacity_real_T(VECTOR, nx);
    loop_ub = b_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      VECTOR->data[VECTOR->size[0] * nx] = b_B->data[nx];
    }

    loop_ub = c_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      VECTOR->data[VECTOR->size[0] * nx + 1] = c_B->data[nx];
    }

    loop_ub = d_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      VECTOR->data[VECTOR->size[0] * nx + 2] = d_B->data[nx];
    }

    loop_ub = e_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      VECTOR->data[VECTOR->size[0] * nx + 3] = e_B->data[nx];
    }

    loop_ub = f_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      VECTOR->data[VECTOR->size[0] * nx + 4] = f_B->data[nx];
    }

    loop_ub = g_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      VECTOR->data[VECTOR->size[0] * nx + 5] = g_B->data[nx];
    }

    loop_ub = b_loop_ub - i;
    for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
      for (nx = 0; nx < 6; nx++) {
        VECTOR->data[nx + VECTOR->size[0] * (b_loop_ub + b_B->size[1])] =
          VECTOR1->data[nx + 6 * (i + b_loop_ub)];
      }
    }

    if (2 > t1->size[1]) {
      i = 0;
      b_loop_ub = 0;
    } else {
      i = 1;
      b_loop_ub = t1->size[1];
    }

    n = t2->size[1] - 1;
    nx = B->size[0];
    B->size[0] = t2->size[1];
    emxEnsureCapacity_real_T(B, nx);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = t2->data[n - nx];
    }

    n = B->size[0];
    nx = b_B->size[0] * b_B->size[1];
    b_B->size[0] = 1;
    b_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(b_B, nx);
    for (nx = 0; nx < n; nx++) {
      b_B->data[nx] = B->data[nx];
    }

    nx = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = (b_B->size[1] + b_loop_ub) - i;
    emxEnsureCapacity_real_T(t, nx);
    loop_ub = b_B->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      t->data[nx] = b_B->data[nx];
    }

    loop_ub = b_loop_ub - i;
    for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
      t->data[b_loop_ub + b_B->size[1]] = t1->data[i + b_loop_ub];
    }
  } else if (((t_e > t_start) && (t_end < t_e)) || ((t_e == t_start) && (t_end <
    t_e))) {
    if (t_start < t_end - 1.0) {
      t->size[0] = 1;
      t->size[1] = 0;
    } else if ((rtIsInf(t_start) || rtIsInf(t_end - 1.0)) && (t_start == t_end -
                1.0)) {
      i = t->size[0] * t->size[1];
      t->size[0] = 1;
      t->size[1] = 1;
      emxEnsureCapacity_real_T(t, i);
      t->data[0] = rtNaN;
    } else if (std::floor(t_start) == t_start) {
      i = t->size[0] * t->size[1];
      t->size[0] = 1;
      loop_ub = static_cast<int>(std::floor(-((t_end - 1.0) - t_start)));
      t->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(t, i);
      for (i = 0; i <= loop_ub; i++) {
        t->data[i] = t_start - static_cast<double>(i);
      }
    } else {
      b_eml_float_colon(t_start, t_end - 1.0, t);
    }

    //  временной ветор прогноза
    i = VECTOR->size[0] * VECTOR->size[1];
    VECTOR->size[0] = 6;
    VECTOR->size[1] = t->size[1];
    emxEnsureCapacity_real_T(VECTOR, i);
    loop_ub = 6 * t->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[i] = 0.0;
    }

    VECTOR->data[0] = x;
    VECTOR->data[1] = y;
    VECTOR->data[2] = z;
    VECTOR->data[3] = V_x;
    VECTOR->data[4] = V_y;
    VECTOR->data[5] = V_z;
    i = VECTOR1->size[0] * VECTOR1->size[1];
    VECTOR1->size[0] = VECTOR->size[0];
    VECTOR1->size[1] = VECTOR->size[1];
    emxEnsureCapacity_real_T(VECTOR1, i);
    loop_ub = VECTOR->size[0] * VECTOR->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR1->data[i] = VECTOR->data[i];
    }

    c_Rung_Kut(t, VECTOR1);
    i = VECTOR->size[0] * VECTOR->size[1];
    VECTOR->size[0] = 6;
    VECTOR->size[1] = VECTOR1->size[1];
    emxEnsureCapacity_real_T(VECTOR, i);
    loop_ub = VECTOR1->size[0] * VECTOR1->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[i] = VECTOR1->data[i];
    }

    n = VECTOR->size[1] - 1;
    i = B->size[0];
    B->size[0] = VECTOR->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR->data[VECTOR->size[0] * ((VECTOR->size[1] - nx) - 1)];
    }

    n = B->size[0];
    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = 1;
    b_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(b_B, i);
    for (nx = 0; nx < n; nx++) {
      b_B->data[nx] = B->data[nx];
    }

    n = VECTOR->size[1] - 1;
    i = B->size[0];
    B->size[0] = VECTOR->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR->data[VECTOR->size[0] * ((VECTOR->size[1] - nx) - 1)
        + 1];
    }

    n = B->size[0];
    i = c_B->size[0] * c_B->size[1];
    c_B->size[0] = 1;
    c_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(c_B, i);
    for (nx = 0; nx < n; nx++) {
      c_B->data[nx] = B->data[nx];
    }

    n = VECTOR->size[1] - 1;
    i = B->size[0];
    B->size[0] = VECTOR->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR->data[VECTOR->size[0] * ((VECTOR->size[1] - nx) - 1)
        + 2];
    }

    n = B->size[0];
    i = d_B->size[0] * d_B->size[1];
    d_B->size[0] = 1;
    d_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(d_B, i);
    for (nx = 0; nx < n; nx++) {
      d_B->data[nx] = B->data[nx];
    }

    n = VECTOR->size[1] - 1;
    i = B->size[0];
    B->size[0] = VECTOR->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR->data[VECTOR->size[0] * ((VECTOR->size[1] - nx) - 1)
        + 3];
    }

    n = B->size[0];
    i = e_B->size[0] * e_B->size[1];
    e_B->size[0] = 1;
    e_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(e_B, i);
    for (nx = 0; nx < n; nx++) {
      e_B->data[nx] = B->data[nx];
    }

    n = VECTOR->size[1] - 1;
    i = B->size[0];
    B->size[0] = VECTOR->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR->data[VECTOR->size[0] * ((VECTOR->size[1] - nx) - 1)
        + 4];
    }

    n = B->size[0];
    i = f_B->size[0] * f_B->size[1];
    f_B->size[0] = 1;
    f_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(f_B, i);
    for (nx = 0; nx < n; nx++) {
      f_B->data[nx] = B->data[nx];
    }

    n = VECTOR->size[1] - 1;
    i = B->size[0];
    B->size[0] = VECTOR->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = VECTOR->data[VECTOR->size[0] * ((VECTOR->size[1] - nx) - 1)
        + 5];
    }

    n = B->size[0];
    i = g_B->size[0] * g_B->size[1];
    g_B->size[0] = 1;
    g_B->size[1] = B->size[0];
    emxEnsureCapacity_real_T(g_B, i);
    for (nx = 0; nx < n; nx++) {
      g_B->data[nx] = B->data[nx];
    }

    i = VECTOR->size[0] * VECTOR->size[1];
    VECTOR->size[0] = 6;
    VECTOR->size[1] = b_B->size[1];
    emxEnsureCapacity_real_T(VECTOR, i);
    loop_ub = b_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[VECTOR->size[0] * i] = b_B->data[i];
    }

    loop_ub = c_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[VECTOR->size[0] * i + 1] = c_B->data[i];
    }

    loop_ub = d_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[VECTOR->size[0] * i + 2] = d_B->data[i];
    }

    loop_ub = e_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[VECTOR->size[0] * i + 3] = e_B->data[i];
    }

    loop_ub = f_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[VECTOR->size[0] * i + 4] = f_B->data[i];
    }

    loop_ub = g_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      VECTOR->data[VECTOR->size[0] * i + 5] = g_B->data[i];
    }

    n = t->size[1] - 1;
    i = B->size[0];
    B->size[0] = t->size[1];
    emxEnsureCapacity_real_T(B, i);
    for (nx = 0; nx <= n; nx++) {
      B->data[nx] = t->data[n - nx];
    }

    n = B->size[0];
    i = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = B->size[0];
    emxEnsureCapacity_real_T(t, i);
    for (nx = 0; nx < n; nx++) {
      t->data[nx] = B->data[nx];
    }
  } else {
    if ((t_e < t_start) && (t_end < t_e)) {
      if (t_e - 1.0 < t_start) {
        t1->size[0] = 1;
        t1->size[1] = 0;
      } else if (std::floor(t_start) == t_start) {
        i = t1->size[0] * t1->size[1];
        t1->size[0] = 1;
        loop_ub = static_cast<int>(std::floor((t_e - 1.0) - t_start));
        t1->size[1] = loop_ub + 1;
        emxEnsureCapacity_real_T(t1, i);
        for (i = 0; i <= loop_ub; i++) {
          t1->data[i] = t_start + static_cast<double>(i);
        }
      } else {
        eml_float_colon(t_start, t_e - 1.0, t1);
      }

      i = VECTOR1->size[0] * VECTOR1->size[1];
      VECTOR1->size[0] = 6;
      VECTOR1->size[1] = t1->size[1];
      emxEnsureCapacity_real_T(VECTOR1, i);
      loop_ub = 6 * t1->size[1];
      for (i = 0; i < loop_ub; i++) {
        VECTOR1->data[i] = 0.0;
      }

      VECTOR1->data[0] = x;
      VECTOR1->data[1] = y;
      VECTOR1->data[2] = z;
      VECTOR1->data[3] = V_x;
      VECTOR1->data[4] = V_y;
      VECTOR1->data[5] = V_z;
      b_Rung_Kut(t1, VECTOR1, 1.0);
      if (t_e < t_end) {
        t2->size[0] = 1;
        t2->size[1] = 0;
      } else if (rtIsInf(t_end) && (t_e == t_end)) {
        i = t2->size[0] * t2->size[1];
        t2->size[0] = 1;
        t2->size[1] = 1;
        emxEnsureCapacity_real_T(t2, i);
        t2->data[0] = rtNaN;
      } else if (std::floor(t_e) == t_e) {
        i = t2->size[0] * t2->size[1];
        t2->size[0] = 1;
        loop_ub = static_cast<int>(std::floor(-(t_end - t_e)));
        t2->size[1] = loop_ub + 1;
        emxEnsureCapacity_real_T(t2, i);
        for (i = 0; i <= loop_ub; i++) {
          t2->data[i] = t_e - static_cast<double>(i);
        }
      } else {
        b_eml_float_colon(t_e, t_end, t2);
      }

      i = VECTOR2->size[0] * VECTOR2->size[1];
      VECTOR2->size[0] = 6;
      VECTOR2->size[1] = t2->size[1];
      emxEnsureCapacity_real_T(VECTOR2, i);
      loop_ub = 6 * t2->size[1];
      for (i = 0; i < loop_ub; i++) {
        VECTOR2->data[i] = 0.0;
      }

      VECTOR2->data[0] = x;
      VECTOR2->data[1] = y;
      VECTOR2->data[2] = z;
      VECTOR2->data[3] = V_x;
      VECTOR2->data[4] = V_y;
      VECTOR2->data[5] = V_z;
      b_Rung_Kut(t2, VECTOR2, -1.0);
      if (2 > VECTOR1->size[1]) {
        i = 0;
        b_loop_ub = 0;
      } else {
        i = 1;
        b_loop_ub = VECTOR1->size[1];
      }

      n = VECTOR2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = VECTOR2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1)];
      }

      n = B->size[0];
      nx = b_B->size[0] * b_B->size[1];
      b_B->size[0] = 1;
      b_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(b_B, nx);
      for (nx = 0; nx < n; nx++) {
        b_B->data[nx] = B->data[nx];
      }

      n = VECTOR2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = VECTOR2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 1];
      }

      n = B->size[0];
      nx = c_B->size[0] * c_B->size[1];
      c_B->size[0] = 1;
      c_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(c_B, nx);
      for (nx = 0; nx < n; nx++) {
        c_B->data[nx] = B->data[nx];
      }

      n = VECTOR2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = VECTOR2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 2];
      }

      n = B->size[0];
      nx = d_B->size[0] * d_B->size[1];
      d_B->size[0] = 1;
      d_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(d_B, nx);
      for (nx = 0; nx < n; nx++) {
        d_B->data[nx] = B->data[nx];
      }

      n = VECTOR2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = VECTOR2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 3];
      }

      n = B->size[0];
      nx = e_B->size[0] * e_B->size[1];
      e_B->size[0] = 1;
      e_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(e_B, nx);
      for (nx = 0; nx < n; nx++) {
        e_B->data[nx] = B->data[nx];
      }

      n = VECTOR2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = VECTOR2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 4];
      }

      n = B->size[0];
      nx = f_B->size[0] * f_B->size[1];
      f_B->size[0] = 1;
      f_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(f_B, nx);
      for (nx = 0; nx < n; nx++) {
        f_B->data[nx] = B->data[nx];
      }

      n = VECTOR2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = VECTOR2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = VECTOR2->data[6 * ((VECTOR2->size[1] - nx) - 1) + 5];
      }

      n = B->size[0];
      nx = g_B->size[0] * g_B->size[1];
      g_B->size[0] = 1;
      g_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(g_B, nx);
      for (nx = 0; nx < n; nx++) {
        g_B->data[nx] = B->data[nx];
      }

      nx = VECTOR->size[0] * VECTOR->size[1];
      VECTOR->size[0] = 6;
      VECTOR->size[1] = (b_B->size[1] + b_loop_ub) - i;
      emxEnsureCapacity_real_T(VECTOR, nx);
      loop_ub = b_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        VECTOR->data[VECTOR->size[0] * nx] = b_B->data[nx];
      }

      loop_ub = c_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        VECTOR->data[VECTOR->size[0] * nx + 1] = c_B->data[nx];
      }

      loop_ub = d_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        VECTOR->data[VECTOR->size[0] * nx + 2] = d_B->data[nx];
      }

      loop_ub = e_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        VECTOR->data[VECTOR->size[0] * nx + 3] = e_B->data[nx];
      }

      loop_ub = f_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        VECTOR->data[VECTOR->size[0] * nx + 4] = f_B->data[nx];
      }

      loop_ub = g_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        VECTOR->data[VECTOR->size[0] * nx + 5] = g_B->data[nx];
      }

      loop_ub = b_loop_ub - i;
      for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
        for (nx = 0; nx < 6; nx++) {
          VECTOR->data[nx + VECTOR->size[0] * (b_loop_ub + b_B->size[1])] =
            VECTOR1->data[nx + 6 * (i + b_loop_ub)];
        }
      }

      if (2 > t1->size[1]) {
        i = 0;
        b_loop_ub = 0;
      } else {
        i = 1;
        b_loop_ub = t1->size[1];
      }

      n = t2->size[1] - 1;
      nx = B->size[0];
      B->size[0] = t2->size[1];
      emxEnsureCapacity_real_T(B, nx);
      for (nx = 0; nx <= n; nx++) {
        B->data[nx] = t2->data[n - nx];
      }

      n = B->size[0];
      nx = b_B->size[0] * b_B->size[1];
      b_B->size[0] = 1;
      b_B->size[1] = B->size[0];
      emxEnsureCapacity_real_T(b_B, nx);
      for (nx = 0; nx < n; nx++) {
        b_B->data[nx] = B->data[nx];
      }

      nx = t->size[0] * t->size[1];
      t->size[0] = 1;
      t->size[1] = (b_B->size[1] + b_loop_ub) - i;
      emxEnsureCapacity_real_T(t, nx);
      loop_ub = b_B->size[1];
      for (nx = 0; nx < loop_ub; nx++) {
        t->data[nx] = b_B->data[nx];
      }

      loop_ub = b_loop_ub - i;
      for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
        t->data[b_loop_ub + b_B->size[1]] = t1->data[i + b_loop_ub];
      }
    }
  }

  emxFree_real_T(&g_B);
  emxFree_real_T(&f_B);
  emxFree_real_T(&e_B);
  emxFree_real_T(&d_B);
  emxFree_real_T(&B);
  emxFree_real_T(&VECTOR2);
  i = t2->size[0] * t2->size[1];
  t2->size[0] = 1;
  t2->size[1] = t->size[1];
  emxEnsureCapacity_real_T(t2, i);
  loop_ub = t->size[0] * t->size[1];
  for (i = 0; i < loop_ub; i++) {
    t2->data[i] = t->data[i] - t_e;
  }

  i = t1->size[0] * t1->size[1];
  t1->size[0] = 1;
  t1->size[1] = t2->size[1];
  emxEnsureCapacity_real_T(t1, i);
  nx = t2->size[1];
  for (n = 0; n < nx; n++) {
    d = t2->data[n];
    t1->data[n] = d * d;
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = 1;
  b_B->size[1] = t2->size[1];
  emxEnsureCapacity_real_T(b_B, i);
  nx = t2->size[1];
  for (n = 0; n < nx; n++) {
    d = t2->data[n];
    b_B->data[n] = d * d;
  }

  i = c_B->size[0] * c_B->size[1];
  c_B->size[0] = 1;
  c_B->size[1] = t2->size[1];
  emxEnsureCapacity_real_T(c_B, i);
  nx = t2->size[1];
  for (n = 0; n < nx; n++) {
    d = t2->data[n];
    c_B->data[n] = d * d;
  }

  loop_ub = VECTOR->size[1];
  nx = VECTOR->size[1];
  n = VECTOR->size[1];
  b_loop_ub = VECTOR->size[1];
  c_loop_ub = VECTOR->size[1];
  d_loop_ub = VECTOR->size[1];
  i = VECTOR1->size[0] * VECTOR1->size[1];
  VECTOR1->size[0] = 6;
  VECTOR1->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(VECTOR1, i);
  for (i = 0; i < loop_ub; i++) {
    VECTOR1->data[6 * i] = VECTOR->data[VECTOR->size[0] * i] + JJ_x * (t1->
      data[i] / 2.0);
  }

  emxFree_real_T(&t1);
  for (i = 0; i < nx; i++) {
    VECTOR1->data[6 * i + 1] = VECTOR->data[VECTOR->size[0] * i + 1] + JJ_y *
      (b_B->data[i] / 2.0);
  }

  emxFree_real_T(&b_B);
  for (i = 0; i < n; i++) {
    VECTOR1->data[6 * i + 2] = VECTOR->data[VECTOR->size[0] * i + 2] + JJ_z *
      (c_B->data[i] / 2.0);
  }

  emxFree_real_T(&c_B);
  for (i = 0; i < b_loop_ub; i++) {
    VECTOR1->data[6 * i + 3] = VECTOR->data[VECTOR->size[0] * i + 3] + JJ_x *
      t2->data[i];
  }

  for (i = 0; i < c_loop_ub; i++) {
    VECTOR1->data[6 * i + 4] = VECTOR->data[VECTOR->size[0] * i + 4] + JJ_y *
      t2->data[i];
  }

  for (i = 0; i < d_loop_ub; i++) {
    VECTOR1->data[6 * i + 5] = VECTOR->data[VECTOR->size[0] * i + 5] + JJ_z *
      t2->data[i];
  }

  emxFree_real_T(&t2);
  emxFree_real_T(&VECTOR);
  if (t->size[1] != 0) {
    n = t->size[1];
  } else if (VECTOR1->size[1] != 0) {
    n = VECTOR1->size[1];
  } else {
    n = 0;
  }

  empty_non_axis_sizes = (n == 0);
  if (empty_non_axis_sizes || (t->size[1] != 0)) {
    input_sizes_idx_0 = 1;
  } else {
    input_sizes_idx_0 = 0;
  }

  if (empty_non_axis_sizes || (VECTOR1->size[1] != 0)) {
    sizes_idx_0 = 6;
  } else {
    sizes_idx_0 = 0;
  }

  nx = input_sizes_idx_0;
  i = Optim->size[0] * Optim->size[1];
  Optim->size[0] = input_sizes_idx_0 + sizes_idx_0;
  Optim->size[1] = n;
  emxEnsureCapacity_real_T(Optim, i);
  for (i = 0; i < n; i++) {
    for (b_loop_ub = 0; b_loop_ub < nx; b_loop_ub++) {
      Optim->data[Optim->size[0] * i] = t->data[input_sizes_idx_0 * i];
    }
  }

  emxFree_real_T(&t);
  for (i = 0; i < n; i++) {
    loop_ub = sizes_idx_0;
    for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
      Optim->data[(b_loop_ub + input_sizes_idx_0) + Optim->size[0] * i] =
        VECTOR1->data[b_loop_ub + 6 * i];
    }
  }

  emxFree_real_T(&VECTOR1);
}

//
// File trailer for Optimization.cpp
//
// [EOF]
//
