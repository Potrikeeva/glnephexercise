/*
 * File: _coder_Main_balistic_api.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 11-May-2020 19:59:58
 */

/* Include Files */
#include "_coder_Main_balistic_api.h"
#include "_coder_Main_balistic_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131483U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "Main_balistic",                     /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(x), &thisId);
  emlrtDestroyArray(&x);
  return y;
}

/*
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 0, 0 };

  y = NULL;
  m = emlrtCreateNumericArray(2, iv, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 2);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : const mxArray * const prhs[18]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void Main_balistic_api(const mxArray * const prhs[18], int32_T nlhs, const
  mxArray *plhs[1])
{
  emxArray_real_T *MAIN;
  real_T x;
  real_T y;
  real_T z;
  real_T V_x;
  real_T V_y;
  real_T V_z;
  real_T a_x;
  real_T a_y;
  real_T a_z;
  real_T Year;
  real_T Month;
  real_T Day;
  real_T Hour;
  real_T Min;
  real_T Sec;
  real_T t_start;
  real_T t_end;
  real_T Day_start;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &MAIN, 2, true);

  /* Marshall function inputs */
  x = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "x");
  y = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "y");
  z = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "z");
  V_x = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "V_x");
  V_y = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "V_y");
  V_z = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "V_z");
  a_x = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "a_x");
  a_y = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "a_y");
  a_z = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "a_z");
  Year = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "Year");
  Month = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "Month");
  Day = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "Day");
  Hour = emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "Hour");
  Min = emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "Min");
  Sec = emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "Sec");
  t_start = emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "t_start");
  t_end = emlrt_marshallIn(&st, emlrtAliasP(prhs[16]), "t_end");
  Day_start = emlrt_marshallIn(&st, emlrtAliasP(prhs[17]), "Day_start");

  /* Invoke the target function */
  Main_balistic(x, y, z, V_x, V_y, V_z, a_x, a_y, a_z, Year, Month, Day, Hour,
                Min, Sec, t_start, t_end, Day_start, MAIN);

  /* Marshall function outputs */
  MAIN->canFreeData = false;
  plhs[0] = emlrt_marshallOut(MAIN);
  emxFree_real_T(&MAIN);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Main_balistic_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Main_balistic_xil_terminate();
  Main_balistic_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Main_balistic_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Main_balistic_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_Main_balistic_api.c
 *
 * [EOF]
 */
