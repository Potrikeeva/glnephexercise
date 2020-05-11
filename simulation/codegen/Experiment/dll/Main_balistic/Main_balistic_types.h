//
// File: Main_balistic_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 21:18:08
//
#ifndef MAIN_BALISTIC_TYPES_H
#define MAIN_BALISTIC_TYPES_H

// Include Files
#include "rtwtypes.h"
#ifdef MAIN_BALISTIC_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define MAIN_BALISTIC_DLL_EXPORT       __declspec(dllimport)
#else
#define MAIN_BALISTIC_DLL_EXPORT
#endif

#elif defined(BUILDING_MAIN_BALISTIC)
#if defined(_MSC_VER) || defined(__LCC__)
#define MAIN_BALISTIC_DLL_EXPORT       __declspec(dllexport)
#else
#define MAIN_BALISTIC_DLL_EXPORT       __attribute__ ((visibility("default")))
#endif

#else
#define MAIN_BALISTIC_DLL_EXPORT
#endif

// Type Definitions
struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for Main_balistic_types.h
//
// [EOF]
//
