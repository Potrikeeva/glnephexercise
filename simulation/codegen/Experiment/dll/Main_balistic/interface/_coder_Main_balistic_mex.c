/*
 * File: _coder_Main_balistic_mex.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 11-May-2020 21:18:08
 */

/* Include Files */
#include "_coder_Main_balistic_mex.h"
#include "_coder_Main_balistic_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void Main_balistic_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[18]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[18]
 * Return Type  : void
 */
void Main_balistic_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[18])
{
  const mxArray *outputs[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 18) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 18, 4,
                        13, "Main_balistic");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "Main_balistic");
  }

  /* Call the function. */
  Main_balistic_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(Main_balistic_atexit);

  /* Module initialization. */
  Main_balistic_initialize();

  /* Dispatch the entry-point. */
  Main_balistic_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  Main_balistic_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_Main_balistic_mex.c
 *
 * [EOF]
 */
