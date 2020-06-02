#include <math.h>
#include <iostream>
#include <stdlib.h>
#include"RungKut.h"
#include"f_x.h"

/*
Данная функция позводяет вычислить положение КА ГЛОНАСС 
на назначенный момент времени методом Рунге-Кутты.

Входные данные:
struct Place* result - динамический массив структур в первом элементе которого 
находится структура положение КА на момент времени t_e,
int length - длинна массива структур struct Place* result,
double J_2 - зональный гармонический коэф.второй степени,
double A_e - большая полуось общеземного эллипсоида[м],
double GM - геоцентр.конст.грав.поля Земли с учетом атмосф.[м ^ 3 / c ^ 2],
double delta_t - шаг расчета положения КА.

Выходные данные:
struct Place* result - заполненный динамический массив структур в элементах которого
находятся структуры с положением КА на моменты времени от t_start до t_end с шагом delta_t
без поправок на солн-лунные ускорения!.

*/


typedef struct Place
{
    double x;
    double y;
    double z;
    double V_x;
    double V_y;
    double V_z;

} Place;

struct Place* RungKut(struct Place* result, int length,
    double J_2, double A_e, double GM, double delta_t)
{
    for (int i = 0; i < (length-1); i++) {
        Place K1;
        Place K2;
        Place K3;
        Place K4;
        Place cor;
        cor = { result[i].x, result[i].y, result[i].z, result[i].V_x, result[i].V_y, result[i].V_z };

        K1 = f_x(A_e, GM, cor, J_2);
        cor = { result[i].x + delta_t * K1.x / 2,
                result[i].y + delta_t * K1.y / 2,
                result[i].z + delta_t * K1.z / 2,
                result[i].V_x + delta_t * K1.V_x / 2,
                result[i].V_y + delta_t * K1.V_y / 2,
                result[i].V_z + delta_t * K1.V_z / 2 };

        K2 = f_x(A_e, GM, cor, J_2);
        cor = { result[i].x + delta_t * K2.x / 2,
                result[i].y + delta_t * K2.y / 2,
                result[i].z + delta_t * K2.z / 2,
                result[i].V_x + delta_t * K2.V_x / 2,
                result[i].V_y + delta_t * K2.V_y / 2,
                result[i].V_z + delta_t * K2.V_z / 2 };

        K3 = f_x(A_e, GM, cor, J_2);
        cor = { result[i].x + delta_t * K3.x,
                result[i].y + delta_t * K3.y,
                result[i].z + delta_t * K3.z,
                result[i].V_x + delta_t * K3.V_x,
                result[i].V_y + delta_t * K3.V_y,
                result[i].V_z + delta_t * K3.V_z};

        K4 = f_x(A_e, GM, cor, J_2);

        result[i+1] = { result[i].x + (delta_t/6.0) * (K1.x + 2 * K2.x + 2 * K3.x + K4.x),
                result[i].y + (delta_t/6.0) * (K1.y + 2 * K2.y + 2 * K3.y + K4.y),
                result[i].z + (delta_t / 6.0) * (K1.z + 2 * K2.z + 2 * K3.z + K4.z),
                result[i].V_x + (delta_t / 6.0) * (K1.V_x + 2 * K2.V_x + 2 * K3.V_x + K4.V_x),
                result[i].V_y + (delta_t / 6.0) * (K1.V_y + 2 * K2.V_y + 2 * K3.V_y + K4.V_y),
                result[i].V_z + (delta_t / 6.0) * (K1.V_z + 2 * K2.V_z + 2 * K3.V_z + K4.V_z) };
    }
    return result;
}