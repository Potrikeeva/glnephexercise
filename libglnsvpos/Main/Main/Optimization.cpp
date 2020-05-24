#include <math.h>
#include <iostream>
#include <stdlib.h>
#include"Optimization.h"
#include"f_x.h"
#include"RungKut.h"

/*
Данная функция оптимизирует вычисление положения КА ГЛОНАСС 
в зависимости от взаимного отношения времен t_start, t_end и t_e.

Входные данные:
struct Place* result - динамический массив структур в первом элементе которого
находится структура положение КА на момент времени t_e,
int length - длинна массива структур struct Place* result,
double J_2 - зональный гармонический коэф.второй степени,
double JJ_x - Лунно-Слонечные ускорения по Оx,
double JJ_y - Лунно-Слонечные ускорения по Оy,
double JJ_z - Лунно-Слонечные ускорения по Оz,
double A_e - большая полуось общеземного эллипсоида[м],
double GM - геоцентр.конст.грав.поля Земли с учетом атмосф.[м ^ 3 / c ^ 2],
double delta_t - шаг расчета положения КА,
int t_start - момент времени с которого стоит расчитать положение КА,
int t_end -момент времени до которого стоит расчитать положение КА.

Выходные данные:
struct Place* result - заполненный динамический массив структур в элементах которого
находятся структуры с положением КА на моменты времени от t_start до t_end с шагом delta_t.

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

struct Place* Optim(struct Place *result, int length,
    double J_2, double JJ_x, double JJ_y, double JJ_z,
    double A_e, double GM, double delta_t, int t_start, int t_e, int t_end)
{
    if ((t_e == t_start && t_end > t_e) || (t_e < t_start && t_end > t_e)) {
        result = RungKut(result, length, J_2, A_e, GM, delta_t);
    }
        else if (t_e > t_start && t_end > t_e){

        int length_t1 = ((double)t_end - (double)t_e) / delta_t;
        Place* result_1 = new Place[length_t1];     
        result_1[0] = { result[0].x, result[0].y, result[0].z,
                        result[0].V_x, result[0].V_y, result[0].V_z };
        result_1 = RungKut(result_1, length_t1, J_2, A_e, GM, delta_t);

        int length_t2 = (((double)t_e - (double)t_start) / delta_t) + 1;
        Place* result_2 = new Place[length_t2];
        result_2[0] = { result[0].x, result[0].y, result[0].z,
                        result[0].V_x, result[0].V_y, result[0].V_z };
        result_2 = RungKut(result_2, length_t2, J_2, A_e, GM, -delta_t);

        for (int i = 0; i < length; i++) {
            if (i < (length_t2-1)) {

                result[i] = { result_2[length_t2 - i - 1].x, result_2[length_t2 - i - 1].y,
                             result_2[length_t2 - i - 1].z, result_2[length_t2 - i - 1].V_x,
                             result_2[length_t2 - i - 1].V_y, result_2[length_t2 - i - 1].V_z };

            }
            else {

                result[i] = { result_1[i - length_t2 + 1].x, result_1[i - length_t2 + 1].y,
                             result_1[i - length_t2 + 1].z, result_1[i - length_t2 + 1].V_x,
                             result_1[i - length_t2 + 1].V_y, result_1[i - length_t2 + 1].V_z };
            }

        }
        delete[] result_2;
        result_2 = nullptr;
        delete[] result_1;
        result_1 = nullptr;
    }
    else if((t_e > t_start && t_end < t_e) || (t_e == t_start && t_end < t_e)) {
        Place* result_2 = new Place[length];
        result_2[0] = { result[0].x, result[0].y, result[0].z,
                        result[0].V_x, result[0].V_y, result[0].V_z };
        result_2 = RungKut(result_2, length, J_2, A_e, GM, -delta_t);
        for (int i = 0; i < length; i++) {
                result[i] = { result_2[length - i].x, result_2[length - i].y,
                             result_2[length - i - 1].z, result_2[length - i].V_x,
                             result_2[length - i - 1].V_y, result_2[length - i].V_z };

            }
        delete[] result_2;
        result_2 = nullptr;
    }
    else if (t_e < t_start && t_end < t_e) {

        int length_t1 = ((double)t_start - (double)t_e) / delta_t;
        Place* result_1 = new Place[length_t1];
        result_1[0] = { result[0].x, result[0].y, result[0].z,
                        result[0].V_x, result[0].V_y, result[0].V_z };
        result_1 = RungKut(result_1, length_t1, J_2, A_e, GM, delta_t);

        int length_t2 = (((double)t_e - (double)t_end) / delta_t) + 1;
        Place* result_2 = new Place[length_t2];
        result_2[0] = { result[0].x, result[0].y, result[0].z,
                        result[0].V_x, result[0].V_y, result[0].V_z };
        result_2 = RungKut(result_2, length_t2, J_2, A_e, GM, -delta_t);

        for (int i = 0; i < length; i++) {
            if (i < (length_t1)) {

                result[i] = { result_2[length_t1 - i].x, result_2[length_t1 - i].y,
                             result_2[length_t1 - i].z, result_2[length_t1 - i].V_x,
                             result_2[length_t1 - i].V_y, result_2[length_t1 - i].V_z };

            }
            else {

                result[i] = { result_1[i - length_t1 + 2].x, result_1[i - length_t1 + 2].y,
                             result_1[i - length_t1 + 2].z, result_1[i - length_t1 + 2].V_x,
                             result_1[i - length_t1 + 2].V_y, result_1[i - length_t1 + 2].V_z };
            }

        }
        delete[] result_2;
        result_2 = nullptr;
        delete[] result_1;
        result_1 = nullptr;
    }
    else {
        std::cout << "ERROR! t_start - t_e - t_end\n\n";
        exit(0);
    }
        
    // Поправки на солнечно-лунные ускорения
    for (int i = 0; i < length; i++) {
        double tau = (t_start + i * delta_t) - t_e;
        result[i] = { JJ_x * ((tau * tau) / 2.0) + result[i].x,
                      JJ_y * ((tau * tau) / 2.0) + result[i].y,
                      JJ_z * ((tau * tau) / 2.0) + result[i].z,
                      JJ_x * tau + result[i].V_x,
                      JJ_y * tau + result[i].V_y,
                      JJ_z * tau + result[i].V_z };
    }
    return result;
}