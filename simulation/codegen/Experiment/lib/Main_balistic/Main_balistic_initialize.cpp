//
// File: Main_balistic_initialize.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 19:59:58
//

// Include Files
#include "Main_balistic_initialize.h"
#include "Main_balistic.h"
#include "Main_balistic_data.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void Main_balistic_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_Main_balistic = true;
}

//
// File trailer for Main_balistic_initialize.cpp
//
// [EOF]
//
