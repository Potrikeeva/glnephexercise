function [F_X] = f_x(coor,J_2,A_e,GM)
    r = sqrt(coor(1,1)^2 + coor(2,1)^2 + coor(3,1)^2);
    coor_p = [coor(1,1)/r; coor(2,1)/r; coor(3,1)/r];
    GM_P = GM/(r^2);
    ro = A_e/r;
    F_x = [coor(4,1); coor(5,1); coor(6,1); ...
            -GM_P*coor_p(1,1) - (3/2)*J_2*GM_P*coor_p(1,1)*(ro^2)*(1-5*(coor_p(3,1)^2));...
            -GM_P*coor_p(2,1) - (3/2)*J_2*GM_P*coor_p(2,1)*(ro^2)*(1-5*(coor_p(3,1)^2));...
            -GM_P*coor_p(3,1) - (3/2)*J_2*GM_P*coor_p(3,1)*(ro^2)*(3-5*(coor_p(3,1)^2))];
        [F_X] = F_x;
end