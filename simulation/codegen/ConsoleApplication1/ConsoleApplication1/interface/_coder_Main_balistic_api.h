/*
 * File: _coder_Main_balistic_api.h
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 11-May-2020 19:59:58
 */

#ifndef _CODER_MAIN_BALISTIC_API_H
#define _CODER_MAIN_BALISTIC_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Main_balistic(real_T x, real_T y, real_T z, real_T V_x, real_T V_y,
  real_T V_z, real_T a_x, real_T a_y, real_T a_z, real_T Year, real_T Month,
  real_T Day, real_T Hour, real_T Min, real_T Sec, real_T t_start, real_T t_end,
  real_T Day_start, emxArray_real_T *MAIN);
extern void Main_balistic_api(const mxArray * const prhs[18], int32_T nlhs,
  const mxArray *plhs[1]);
extern void Main_balistic_atexit(void);
extern void Main_balistic_initialize(void);
extern void Main_balistic_terminate(void);
extern void Main_balistic_xil_shutdown(void);
extern void Main_balistic_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Main_balistic_api.h
 *
 * [EOF]
 */
