#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include"efem_calc.h"
#include"Optimization.h"


/*
Данная функция сначала обрабатывает данные эфемерид и вычисляет положение КА
в инерциальной геоцентрической СК, направляет их для вычисления положения КА ГЛОНАСС по методу Рунге-Кутты
на заданный отрезок времени и обрабатывает вычисления положения КА ГЛОНАСС
по сравнению с вычислениями произведенными в MatLab

Входные данные:
double x = 10584969.2383; // координата Х в системе ПЗ_90[m]
double y = 2721713.86719; // координата Y в системе ПЗ_90[m]
double z = 23027096.6797; // координата Z в системе ПЗ_90[m]
double V_x = -788.876533508; // скорость по Х в системе ПЗ_90[m / s]
double V_y = 3058.68911743; // скорость по Y в системе ПЗ_90[m / s]
double V_z = 1.50871276855; // скорость по Z в системе ПЗ_90[m / s]
double a_x = 0; // ускорение по Х в системе ПЗ_90[m / s ^ 2]
double a_y = 0; // ускорение по Y в системе ПЗ_90[m / s ^ 2]
double a_z = -372.529029846e-9; // ускорение по Z в системе ПЗ_90[m / s ^ 2]
int Year = 2020; // год по UTC
int Month = 2; // месяц по UTC
int Day = 10; // день по UTC
int Hour = 13; // час по UTC
int Min = 45; // минута по UTC
int Sec = 0; // секунда по UTC
double t_start = 12; // время начала прогноза указывать в МДВ
double t_end = 24; // время окончания прогноза указывать в МДВ
int Day_start = 10; // день начала прогноза(должен совпадать с днем прихода эфемерид) указывать в МДВ
double delta_t = 0.1; // шаг расчета

Выходные данные:
нет, но выводит рассогласование вычислений положения КА на заданный 
момент времени в инерциальной СК в MatLab и в С++ и время выполнения программы

*/

using namespace std;


typedef struct Place
{
    double x;
    double y;
    double z;
    double V_x;
    double V_y;
    double V_z;

}Place;


void efem_calc(double x, double y, double z, double V_x, double V_y, double V_z,
    double a_x, double a_y, double a_z, int Year, int Month,
    int Day, int Hour, int Min, int Sec,
    int t_start, int t_end, double delta_t, int Day_start)

{
    if (Day_start != Day) {
        cout << "ERROR! The forecast day does not coincide with the day of arrival of the ephemeris\n\n";
        exit(0);
    }
    double omega_z = 7.2921151467e-5; // средняя угловая скорость вращения Земли относительно т.ВР[рад / с]
    double A_e = 6378136; // большая полуось общеземного эллипсоида[м]
    double GM = 398600441.8e6; // геоцентр.конст.грав.поля Земли с учетом атмосф.[м ^ 3 / c ^ 2]
    double J_2 = 1082625.75e-9; // зональный гармонический коэф.второй степени
    double pi = 3.141592653589793;
    // Перевод в МДВ времен прогноза
    t_start = (t_start + 3) * 60 * 60;// время начала прогноза указывать в МДВ
    t_end = (t_end + 3) * 60 * 60; // время окончания прогноза указывать в МДВ
    // Пересчет в МДВ времени эфемеридных данных
    if (Hour + 3 < 24) { // учет перехода на МДВ
        Hour = Hour + 3;
    }
    else {
        Hour = (Hour + 3) - 24;
        Day = Day + 1;
    }
    int  DEL = Year - 1995;
    int N_ch = ceil((DEL) / 4.0); // номер четырехлетия по эфем.
    int N_t = 0;
    if (DEL % 4 == 1) {
        int vis[13] = { 31, 31 + 29, 31 + 29 + 31, 31 + 29 + 31, 31 + 29 + 31 + 30, 31 + 29 + 31 + 30 + 31,
            31 + 29 + 31 + 30 + 31 + 30, 31 + 29 + 31 + 30 + 31 + 30 + 31, 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31,
            31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30, 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
            31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30, 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 };
        N_t = N_t + vis[Month - 2] + Day; // номер суток от начала четырехлетия по эфем.
    }
    else {
        N_t = N_t + 365 * ((DEL % 4) - 1) + 1;
        int n_vis[13] = { 31, 31 + 29, 31 + 28 + 31, 31 + 29 + 31, 31 + 29 + 31 + 30, 31 + 29 + 31 + 30 + 31,
            31 + 29 + 31 + 30 + 31 + 30, 31 + 29 + 31 + 30 + 31 + 30 + 31, 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31,
            31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30, 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
            31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30, 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 };
        N_t = N_t + n_vis[Month - 2] + Day; // номер суток от начала четырехлетия по эфем.
    }
    int t_e = Hour * 60 * 60 + Min * 60 + Sec; // номер секунды от начала суток по эфем.
    // Трансформация координат, скоростей и ускорений из ПЗ - 90 в инерц.геоцентричекую СК
    // Вычислим среднее звездное время по Гринвичу
    double JD0 = 1461 * ((double)N_ch - 1) + (double)N_t + 2450082.5; // текущая Юлианская дата на 0 часов шкалы МДВ
    double ERA = 2 * pi * (0.7790572732640 + 1.00273781191135448 * (JD0 - 2451545)); //  угол поворота Земли[рад]
    double delta_T = (JD0 - 2451545) / 36525; // время от эпохи 2000 г 1 января 12 ч(UTC(SU))
    // до текущей эпохи в Юлианских столетиях по 36525 эфемеридных суток
    double GMST = ERA + 0.0000000703270726 + 0.0223603658710194 * delta_T \
        + 0.0000067465784654 * pow(delta_T, 2) - 0.0000000000021332 * pow(delta_T, 3) \
        - 0.0000000001452308 * pow(delta_T, 4) - 0.000000000001784 * pow(delta_T, 5); //  среднее зв - е время по Гринвичу[рад]
    double S = GMST + omega_z * ((double)t_e - 10800);
    x = x * cos(S) - y * sin(S);
    y = x * sin(S) + y * cos(S);
    V_x = V_x * cos(S) - V_y * sin(S) - omega_z * y;
    V_y = V_x * sin(S) + V_y * cos(S) + omega_z * x;
    double JJ_x = a_x * cos(S) - a_y * sin(S);
    double JJ_y = a_x * sin(S) + a_y * cos(S);
    double JJ_z = a_z;



    int length = ((double)t_end - (double)t_start) / delta_t;
    Place* result = new Place[length];

    result[0].x = x;
    result[0].y = y;
    result[0].z = z;
    result[0].V_x = V_x;
    result[0].V_y = V_y;
    result[0].V_z = V_z;

    result = Optim(result, length, J_2,
        JJ_x, JJ_y, JJ_z,
        A_e, GM, delta_t, t_start, t_e, t_end); // положение КА ГЛОНАСС на заданный 
    //отрезок времени в инерциальной геоцентрической СК

    // Чтение данный из .txt в котором записаны данный положения КА на 
    //заданный отрезок времени в инерциальной геоцентрической СК вычисленные в MatLab
    // и сравнение с вычислениями в С++
    ifstream File;
    File.open("XYZ.txt");
    if (!File.is_open()) {
        cout << "Error opening file\n\n";
        exit(0);
    }
    else {
        cout << "File is opening\n\n";
    }

    double delta_X0, delta_Y0, delta_Z0, delta_X, delta_Y, delta_Z;
    double X_file, Y_file, Z_file;
    delta_X = 0;
    delta_Y = 0;
    delta_Z = 0;

    for (int i = 0; i < length; i++) {
        File >> X_file;
        delta_X0 = abs(X_file - result[i].x);
        File >> Y_file;
        delta_Y0 = abs(Y_file - result[i].y);
        File >> Z_file;
        delta_Z0 = abs(Z_file - result[i].z);
        if (delta_X0 > delta_X) {
            delta_X = delta_X0;
        }
        if (delta_Y0 > delta_Y) {
            delta_Y = delta_Y0;
        }
        if (delta_Z0 > delta_Z) {
            delta_Z = delta_Z0;
        }
    }
    std::cout.setf(std::ios::fixed);
    std::cout.precision(14); //14 - число символов после точки
    std::cout << "Maximum calculation error in C++ compared to MatLab:\n\n";
    std::cout << "delta_X, m = " << delta_X << "\n\n";
    std::cout << "delta_Y, m = " << delta_Y << "\n\n";
    std::cout << "delta_Z, m = " << delta_Z << "\n\n";
    float end_time = clock() / 1000.0;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(3); //3 - число символов после точки
    std::cout << "Time of the programm:\n\n";
    std::cout << "Time, s = " << end_time << "\n\n";
}

