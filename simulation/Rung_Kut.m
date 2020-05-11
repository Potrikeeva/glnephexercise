function [RU] = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t,VECTOR,delta_t)
    %% Метод Рунге-Кутты 4-го порядка
    for i = 1:length(t)-1
        K1 = f_x(VECTOR(:,i),J_2,A_e,GM);
        coor_2 = VECTOR(:,i) + delta_t.*K1./2;
        K2 = f_x(coor_2,J_2,A_e,GM);
        coor_3 = VECTOR(:,i) + delta_t.*K2./2;
        K3 = f_x(coor_3,J_2,A_e,GM);
        coor_4 = VECTOR(:,i) + delta_t.*K3;
        K4 = f_x(coor_4,J_2,A_e,GM);
        %clear coor_2 coor_3 coor_4
        VECTOR(:,i+1) = VECTOR(:,i) + (delta_t/6)*(K1 + 2*K2 + 2*K3 + K4);
    end
    [RU] = VECTOR;
end