#ifndef Optimization_H
#define Optimization_H

struct Place* Optim(struct Place* result, int length,
    double J_2, double JJ_x, double JJ_y, double JJ_z,
    double A_e, double GM, double delta_t, int t_start, int t_e, int t_end);
#endif
