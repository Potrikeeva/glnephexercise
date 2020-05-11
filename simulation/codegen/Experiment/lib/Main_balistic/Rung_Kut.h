//
// File: Rung_Kut.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 19:59:58
//
#ifndef RUNG_KUT_H
#define RUNG_KUT_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "Main_balistic_types.h"

// Function Declarations
extern void Rung_Kut(const emxArray_real_T *t, emxArray_real_T *VECTOR);
extern void b_Rung_Kut(const emxArray_real_T *t, emxArray_real_T *VECTOR, double
  delta_t);
extern void c_Rung_Kut(const emxArray_real_T *t, emxArray_real_T *VECTOR);

#endif

//
// File trailer for Rung_Kut.h
//
// [EOF]
//
