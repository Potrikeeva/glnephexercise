//
// File: Main_balistic.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 11-May-2020 21:18:08
//

// Include Files
#include "Main_balistic.h"
#include "Main_balistic_data.h"
#include "Main_balistic_emxutil.h"
#include "Main_balistic_initialize.h"
#include "Optimization.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);
static double rt_powd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// format long
// Arguments    : double x
//                double y
//                double z
//                double V_x
//                double V_y
//                double V_z
//                double a_x
//                double a_y
//                double a_z
//                double Year
//                double Month
//                double Day
//                double Hour
//                double Min
//                double Sec
//                double t_start
//                double t_end
//                double Day_start
//                emxArray_real_T *MAIN
// Return Type  : void
//
void Main_balistic(double x, double y, double z, double V_x, double V_y, double
                   V_z, double a_x, double a_y, double a_z, double Year, double
                   Month, double Day, double Hour, double Min, double Sec,
                   double t_start, double t_end, double, emxArray_real_T *MAIN)
{
  double N_t;
  static const short n_vis[13] = { 31, 60, 90, 91, 121, 152, 182, 213, 244, 274,
    305, 335, 366 };

  static const short vis[13] = { 31, 60, 91, 91, 121, 152, 182, 213, 244, 274,
    305, 335, 366 };

  emxArray_real_T *VECTOR;
  emxArray_real_T *t;
  double t_e;
  double delta_T;
  double x_tmp;
  int nx;
  int i;
  int i1;
  emxArray_real_T *b_VECTOR;
  int loop_ub;
  int i2;
  emxArray_real_T *b_x;
  emxArray_real_T *b_z;
  emxArray_real_T *r;
  emxArray_real_T *c_VECTOR;
  emxArray_real_T *d_VECTOR;
  emxArray_real_T *e_VECTOR;
  double f_VECTOR[3];
  static const double dv[3] = { 0.07, -0.0, -0.77 };

  static const double a[9] = { -3.0E-9, 1.7113923461492218E-6,
    1.9392547831719228E-8, -1.7113923461492218E-6, -3.0E-9,
    -9.2114602200666327E-8, -1.9392547831719228E-8, 9.2114602200666327E-8,
    -3.0E-9 };

  emxArray_real_T *teta;
  emxArray_real_T *phi;
  double cor[3];
  static const double b_a[9] = { -0.61157116287167612, -0.654040076655535,
    0.44521038944773922, 0.79118942911529455, -0.50555787972568789,
    0.34413735267111173, 0.0, 0.56271023482400673, 0.82665421527039418 };

  if (isInitialized_Main_balistic == false) {
    Main_balistic_initialize();
  }

  //  средняя угловая скорость вращения Земли относительно т. ВР [рад/с]
  //  большая полуось общеземного эллипсоида [м]
  //  геоцентр. конст. грав. поля Земли с учетом атмосф. [м^3/c^2]
  //  зональный гармонический коэф. второй степени
  //  Перевод в МДВ времен прогноза
  t_start = (t_start + 3.0) * 60.0 * 60.0;

  //  время начала прогноза указывать в МДВ
  t_end = (t_end + 3.0) * 60.0 * 60.0;

  //  время окончания прогноза указывать в МДВ
  //  Пересчет в МДВ времени эфемеридных данных
  if (Hour + 3.0 < 24.0) {
    //  учет перехода на МДВ
    Hour += 3.0;
  } else {
    Hour = (Hour + 3.0) - 24.0;
    Day++;
  }

  //  номер четырехлетия по эфем.
  if (rtIsNaN(Year - 1995.0) || rtIsInf(Year - 1995.0)) {
    N_t = rtNaN;
  } else if (Year - 1995.0 == 0.0) {
    N_t = 0.0;
  } else {
    N_t = std::fmod(Year - 1995.0, 4.0);
    if (N_t == 0.0) {
      N_t = 0.0;
    } else {
      if (Year - 1995.0 < 0.0) {
        N_t += 4.0;
      }
    }
  }

  if (N_t == 1.0) {
    N_t = static_cast<double>(vis[static_cast<int>((Month - 1.0)) - 1]) + Day;

    //  номер суток от начала четырехлетия по эфем.
  } else {
    N_t = ((365.0 * (N_t - 1.0) + 1.0) + static_cast<double>(n_vis[static_cast<
            int>((Month - 1.0)) - 1])) + Day;

    //  номер суток от начала четырехлетия по эфем.
  }

  emxInit_real_T(&VECTOR, 2);
  emxInit_real_T(&t, 2);
  t_e = (Hour * 60.0 * 60.0 + Min * 60.0) + Sec;

  //  номер секунды от начала суток по эфем.
  //  Трансформация координат, скоростей и ускорений из ПЗ-90 в инерц. геоцентричекую СК 
  //  Вычислим среднее звездное время по Гринвичу
  N_t = (1461.0 * (std::ceil((Year - 1995.0) / 4.0) - 1.0) + N_t) + 2.4500825E+6;

  //  текущая Юлианская дата на 0 часов шкалы МДВ
  //  угол поворота Земли [рад]
  delta_T = (N_t - 2.451545E+6) / 36525.0;

  //  время от эпохи 2000 г 1 января 12 ч (UTC(SU))
  //  до текущей эпохи в Юлианских столетиях по 36525 эфемеридных суток
  delta_T = (((((6.2831853071795862 * (1.0027378119113546 * (N_t - 2.451545E+6)
    + 0.779057273264) + 7.03270726E-8) + 0.0223603658710194 * delta_T)
               + 6.7465784654E-6 * (delta_T * delta_T)) - 2.1332E-12 *
              rt_powd_snf(delta_T, 3.0)) - 1.452308E-10 * rt_powd_snf(delta_T,
              4.0)) - 1.784E-12 * rt_powd_snf(delta_T, 5.0);

  //  среднее зв-е время по Гринвичу [рад]
  N_t = delta_T + 7.2921151467E-5 * (t_e - 10800.0);
  x_tmp = std::sin(N_t);
  N_t = std::cos(N_t);
  x = x * N_t - y * x_tmp;
  y = x * x_tmp + y * N_t;
  V_x = (V_x * N_t - V_y * x_tmp) - 7.2921151467E-5 * y;
  V_y = (V_x * x_tmp + V_y * N_t) + 7.2921151467E-5 * x;

  //  В нашем случае необходимо дать прогноз на момент ранее данных эфемерид.
  //  функция Optimization подстраивает параметры относительно времени прогноза
  //  и времени эфемеридных данных и сразу вычисляет методом Рунге-Кутты
  //  положение КА
  Optimization(x, y, z, V_x, V_y, V_z, a_x * N_t - a_y * x_tmp, a_x * x_tmp +
               a_y * N_t, a_z, t_start, t_e, t_end, VECTOR);
  nx = VECTOR->size[1];
  i = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(t, i);
  for (i = 0; i < nx; i++) {
    t->data[i] = VECTOR->data[VECTOR->size[0] * i];
  }

  if (2 > VECTOR->size[0]) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = VECTOR->size[0];
  }

  emxInit_real_T(&b_VECTOR, 2);
  nx = VECTOR->size[1] - 1;
  loop_ub = i1 - i;
  i1 = b_VECTOR->size[0] * b_VECTOR->size[1];
  b_VECTOR->size[0] = loop_ub;
  b_VECTOR->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(b_VECTOR, i1);
  for (i1 = 0; i1 <= nx; i1++) {
    for (i2 = 0; i2 < loop_ub; i2++) {
      b_VECTOR->data[i2 + b_VECTOR->size[0] * i1] = VECTOR->data[(i + i2) +
        VECTOR->size[0] * i1];
    }
  }

  i = VECTOR->size[0] * VECTOR->size[1];
  VECTOR->size[0] = b_VECTOR->size[0];
  VECTOR->size[1] = b_VECTOR->size[1];
  emxEnsureCapacity_real_T(VECTOR, i);
  nx = b_VECTOR->size[0] * b_VECTOR->size[1];
  for (i = 0; i < nx; i++) {
    VECTOR->data[i] = b_VECTOR->data[i];
  }

  emxFree_real_T(&b_VECTOR);

  // clear x y z V_x V_y V_z JJ_x JJ_y JJ_z t1 t2 VECTOR1 VECTOR2
  //  [X_erth,Y_erth,Z_erth] = sphere(40); % сфера обозначающая Землю
  //  X_erth =  (A_e/1e3).*X_erth;
  //  Y_erth =  (A_e/1e3).*Y_erth;
  //  Z_erth =  (A_e/1e3).*Z_erth;
  nx = VECTOR->size[0] * VECTOR->size[1];
  for (i = 0; i < nx; i++) {
    VECTOR->data[i] /= 1000.0;
  }

  //  переход к километрам
  //  surf(X_erth,Y_erth,Z_erth)
  i = t->size[0] * t->size[1];
  i1 = t->size[0] * t->size[1];
  t->size[0] = 1;
  emxEnsureCapacity_real_T(t, i1);
  nx = i - 1;
  for (i = 0; i <= nx; i++) {
    t->data[i] = delta_T + 7.2921151467E-5 * (t->data[i] - 10800.0);
  }

  emxInit_real_T(&b_x, 2);
  i = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  b_x->size[1] = t->size[1];
  emxEnsureCapacity_real_T(b_x, i);
  nx = t->size[0] * t->size[1];
  for (i = 0; i < nx; i++) {
    b_x->data[i] = t->data[i];
  }

  nx = t->size[1];
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    b_x->data[loop_ub] = std::cos(b_x->data[loop_ub]);
  }

  nx = t->size[1];
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    t->data[loop_ub] = std::sin(t->data[loop_ub]);
  }

  emxInit_real_T(&b_z, 2);
  nx = VECTOR->size[1];
  i = b_z->size[0] * b_z->size[1];
  b_z->size[0] = 1;
  b_z->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(b_z, i);
  for (i = 0; i < nx; i++) {
    b_z->data[i] = -VECTOR->data[VECTOR->size[0] * i] * t->data[i];
  }

  emxInit_real_T(&r, 2);
  nx = VECTOR->size[1];
  i = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(r, i);
  for (i = 0; i < nx; i++) {
    r->data[i] = VECTOR->data[VECTOR->size[0] * i + 1] * b_x->data[i];
  }

  emxInit_real_T(&c_VECTOR, 2);
  nx = VECTOR->size[1] - 1;
  i = c_VECTOR->size[0] * c_VECTOR->size[1];
  c_VECTOR->size[0] = 1;
  c_VECTOR->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(c_VECTOR, i);
  for (i = 0; i <= nx; i++) {
    c_VECTOR->data[i] = VECTOR->data[VECTOR->size[0] * i] * b_x->data[i] +
      VECTOR->data[VECTOR->size[0] * i + 1] * t->data[i];
  }

  emxFree_real_T(&b_x);
  emxFree_real_T(&t);
  nx = c_VECTOR->size[1];
  for (i = 0; i < nx; i++) {
    VECTOR->data[VECTOR->size[0] * i] = c_VECTOR->data[i];
  }

  emxFree_real_T(&c_VECTOR);
  nx = b_z->size[1];
  for (i = 0; i < nx; i++) {
    VECTOR->data[VECTOR->size[0] * i + 1] = b_z->data[i] + r->data[i];
  }

  emxFree_real_T(&b_z);
  emxInit_real_T(&d_VECTOR, 2);

  // clear X_PZ90 Y_PZ90
  //  surf(X_erth,Y_erth,Z_erth)
  //  Переведем полученные для спутника координаты в систему WGS-84
  nx = VECTOR->size[1];
  i = d_VECTOR->size[0] * d_VECTOR->size[1];
  d_VECTOR->size[0] = 3;
  d_VECTOR->size[1] = VECTOR->size[1];
  emxEnsureCapacity_real_T(d_VECTOR, i);
  for (i = 0; i < nx; i++) {
    d_VECTOR->data[3 * i] = VECTOR->data[VECTOR->size[0] * i] * 1000.0;
    d_VECTOR->data[3 * i + 1] = VECTOR->data[VECTOR->size[0] * i + 1] * 1000.0;
    d_VECTOR->data[3 * i + 2] = VECTOR->data[VECTOR->size[0] * i + 2] * 1000.0;
  }

  emxFree_real_T(&VECTOR);

  //  переход к метрам
  //  [mas] это миллисекунда в угловых единицах измерения
  //  [см]
  //  [ppd] или одна миллиардная часть величины
  //  [рад]
  //  [м]
  i = d_VECTOR->size[1] - 1;
  for (nx = 0; nx <= i; nx++) {
    for (i1 = 0; i1 < 3; i1++) {
      f_VECTOR[i1] = (d_VECTOR->data[i1 + 3 * nx] + dv[i1]) + ((a[i1] *
        d_VECTOR->data[3 * nx] + a[i1 + 3] * d_VECTOR->data[3 * nx + 1]) + a[i1
        + 6] * d_VECTOR->data[3 * nx + 2]);
    }

    d_VECTOR->data[3 * nx] = f_VECTOR[0];
    d_VECTOR->data[3 * nx + 1] = f_VECTOR[1];
    d_VECTOR->data[3 * nx + 2] = f_VECTOR[2];
  }

  emxInit_real_T(&e_VECTOR, 2);
  nx = d_VECTOR->size[1] - 1;
  i = e_VECTOR->size[0] * e_VECTOR->size[1];
  e_VECTOR->size[0] = 3;
  e_VECTOR->size[1] = d_VECTOR->size[1];
  emxEnsureCapacity_real_T(e_VECTOR, i);
  for (i = 0; i <= nx; i++) {
    e_VECTOR->data[3 * i] = d_VECTOR->data[3 * i] / 1000.0;
    i1 = 3 * i + 1;
    e_VECTOR->data[i1] = d_VECTOR->data[i1] / 1000.0;
    i1 = 3 * i + 2;
    e_VECTOR->data[i1] = d_VECTOR->data[i1] / 1000.0;
  }

  i = d_VECTOR->size[0] * d_VECTOR->size[1];
  d_VECTOR->size[0] = 3;
  d_VECTOR->size[1] = e_VECTOR->size[1];
  emxEnsureCapacity_real_T(d_VECTOR, i);
  nx = e_VECTOR->size[0] * e_VECTOR->size[1];
  for (i = 0; i < nx; i++) {
    d_VECTOR->data[i] = e_VECTOR->data[i];
  }

  //  переход к км
  // surf(X_erth,Y_erth,Z_erth)
  //  Географические координаты корпуса Е и их перевод в систему WGS-84
  //  высота в метрах
  //  широта в радионах
  //  долгота в радионах
  nx = d_VECTOR->size[1] - 1;
  i = e_VECTOR->size[0] * e_VECTOR->size[1];
  e_VECTOR->size[0] = 3;
  e_VECTOR->size[1] = d_VECTOR->size[1];
  emxEnsureCapacity_real_T(e_VECTOR, i);
  for (i = 0; i <= nx; i++) {
    e_VECTOR->data[3 * i] = d_VECTOR->data[3 * i] * 1000.0;
    i1 = 3 * i + 1;
    e_VECTOR->data[i1] = d_VECTOR->data[i1] * 1000.0;
    i1 = 3 * i + 2;
    e_VECTOR->data[i1] = d_VECTOR->data[i1] * 1000.0;
  }

  i = d_VECTOR->size[0] * d_VECTOR->size[1];
  d_VECTOR->size[0] = 3;
  d_VECTOR->size[1] = e_VECTOR->size[1];
  emxEnsureCapacity_real_T(d_VECTOR, i);
  nx = e_VECTOR->size[0] * e_VECTOR->size[1];
  for (i = 0; i < nx; i++) {
    d_VECTOR->data[i] = e_VECTOR->data[i];
  }

  emxFree_real_T(&e_VECTOR);

  //  переход к метрам
  //  %% Постороение SkyPlot
  nx = d_VECTOR->size[1];
  i = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = d_VECTOR->size[1];
  emxEnsureCapacity_real_T(r, i);
  for (i = 0; i < nx; i++) {
    r->data[i] = 0.0;
  }

  emxInit_real_T(&teta, 2);
  nx = d_VECTOR->size[1];
  i = teta->size[0] * teta->size[1];
  teta->size[0] = 1;
  teta->size[1] = d_VECTOR->size[1];
  emxEnsureCapacity_real_T(teta, i);
  for (i = 0; i < nx; i++) {
    teta->data[i] = 0.0;
  }

  emxInit_real_T(&phi, 2);
  nx = d_VECTOR->size[1];
  i = phi->size[0] * phi->size[1];
  phi->size[0] = 1;
  phi->size[1] = d_VECTOR->size[1];
  emxEnsureCapacity_real_T(phi, i);
  for (i = 0; i < nx; i++) {
    phi->data[i] = 0.0;
  }

  i = d_VECTOR->size[1] - 1;
  for (nx = 0; nx <= i; nx++) {
    //  экваториальный радиус в WGS 84
    //  полярный радиус в WGS 84
    f_VECTOR[0] = d_VECTOR->data[3 * nx] - 2.8463537440309208E+6;
    f_VECTOR[1] = d_VECTOR->data[3 * nx + 1] - 2.2001657316473983E+6;
    f_VECTOR[2] = d_VECTOR->data[3 * nx + 2] - 5.2496507568679815E+6;
    for (i1 = 0; i1 < 3; i1++) {
      cor[i1] = (b_a[i1] * f_VECTOR[0] + b_a[i1 + 3] * f_VECTOR[1]) + b_a[i1 + 6]
        * f_VECTOR[2];
    }

    // [x(i) y(i) z(i)] = ecef2enu(VECTOR(1,i),VECTOR(2,i),VECTOR(3,i),N,E,H,wgs84Ellipsoid,'radians'); 
    if (cor[2] > 0.0) {
      N_t = cor[0] * cor[0] + cor[1] * cor[1];
      teta->data[nx] = rt_atan2d_snf(std::sqrt(N_t), cor[2]);
      r->data[nx] = std::sqrt(N_t + cor[2] * cor[2]);
      phi->data[nx] = rt_atan2d_snf(cor[1], cor[0]);
    } else {
      r->data[nx] = rtNaN;
      phi->data[nx] = rtNaN;
    }
  }

  emxFree_real_T(&d_VECTOR);
  i = MAIN->size[0] * MAIN->size[1];
  MAIN->size[0] = 3;
  MAIN->size[1] = teta->size[1];
  emxEnsureCapacity_real_T(MAIN, i);
  nx = teta->size[1];
  for (i = 0; i < nx; i++) {
    MAIN->data[3 * i] = teta->data[i];
  }

  emxFree_real_T(&teta);
  nx = r->size[1];
  for (i = 0; i < nx; i++) {
    MAIN->data[3 * i + 1] = r->data[i];
  }

  emxFree_real_T(&r);
  nx = phi->size[1];
  for (i = 0; i < nx; i++) {
    MAIN->data[3 * i + 2] = phi->data[i];
  }

  emxFree_real_T(&phi);
}

//
// File trailer for Main_balistic.cpp
//
// [EOF]
//
