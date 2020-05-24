#include <iostream>
#include <xlocale>
#ifndef lib_efem_calc_H
#define lib_efem_calc_H

void efem_calc(double x, double y, double z, double V_x, double V_y, double V_z,
    double a_x, double a_y, double a_z, int Year, int Month,
    int Day, int Hour, int Min, int Sec,
    int t_start, int t_end,  double delta_t, int Day_start);

#endif
