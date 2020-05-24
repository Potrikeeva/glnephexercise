
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include"f_x.h"

/*
Данная функция позводяет вычислить коэф. К 
для реализации метода Рунге-Кутты

Входные данные:
double A_e - большая полуось общеземного эллипсоида[м],
double GM - геоцентр.конст.грав.поля Земли с учетом атмосф.[м ^ 3 / c ^ 2]б
struct Place cor - структура PLace с поправками от коэф. K,
double J_2 - зональный гармонический коэф.второй степени.

Выходные данные:
struct Place К - структура коэф K.

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


typedef struct Cor
{
    double x;
    double y;
    double z;
} Cor;


struct Place f_x(double A_e, double GM,
         struct Place cor, double J_2)
{
        Cor cor_p;
        Place K;
        double r = sqrt(cor.x * cor.x + cor.y * cor.y + cor.z * cor.z);
        cor_p.x = cor.x / r;
        cor_p.y = cor.y / r;
        cor_p.z = cor.z / r;
        double GM_P = GM / (r * r);
        double ro = A_e / r;

        K.x = cor.V_x;
        K.y = cor.V_y;
        K.z = cor.V_z;
        K.V_x = - GM_P * cor_p.x - (3 / 2.0) * J_2 * GM_P * cor_p.x * (ro * ro) * (1 - 5 * (cor_p.z * cor_p.z));
        K.V_y = - GM_P * cor_p.y - (3 / 2.0) * J_2 * GM_P * cor_p.y * (ro * ro) * (1 - 5 * (cor_p.z * cor_p.z));
        K.V_z = - GM_P * cor_p.z - (3 / 2.0) * J_2 * GM_P * cor_p.z * (ro * ro) * (3 - 5 * (cor_p.z * cor_p.z));

        return K;
}