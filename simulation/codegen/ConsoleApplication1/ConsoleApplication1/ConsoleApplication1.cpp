// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <math.h>
#include "tmwtypes.h"
#include "Main_balistic.h"
#include "Main_balistic_emxAPI.h"
#include "Main_balistic_terminate.h"
#include "ConsoleApplication1.h"
//#include "rt_nonfinite.h"

int main()
{


    double x = 10584969.2383; // координата Х в системе ПЗ_90[m]
    double y = 2721713.86719; // координата Y в системе ПЗ_90[m]
    double z = 23027096.6797; // координата Z в системе ПЗ_90[m]
    double V_x = -788.876533508; // скорость по Х в системе ПЗ_90[m / s]
    double V_y = 3058.68911743; // скорость по Y в системе ПЗ_90[m / s]
    double V_z = 1.50871276855; // скорость по Z в системе ПЗ_90[m / s]
    double a_x = 0; // ускорение по Х в системе ПЗ_90[m / s ^ 2]
    double a_y = 0; // ускорение по Y в системе ПЗ_90[m / s ^ 2]
    double a_z = -372.529029846e-9; // ускорение по Z в системе ПЗ_90[m / s ^ 2]
    double Year = 2020; // год по UTC
    double Month = 2; // месяц по UTC
    double Day = 10; // день по UTC
    double Hour = 13; // час по UTC
    double Min = 45; // минута по UTC
    double Sec = 0; // секунда по UTC
    double t_start = 12; // время начала прогноза указывать в МДВ
    double t_end = 24; // время окончания прогноза указывать в МДВ
    double Day_start = 10; // день начала прогноза(должен совпадать с днем прихода эфемерид) указывать в МДВ
    emxArray_real_T* MAIN;

    Main_balistic(x, y, z, V_x, V_y,
                   V_z, a_x, a_y, a_z, Year, 
                   Month, Day, Hour, Min, Sec,
                   t_start, t_end, Day_start, MAIN);
    //emxDestroyArray_real_T(MAIN);
    return 0;
}
