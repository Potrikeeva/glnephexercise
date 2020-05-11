function [Optim] = Optimization(x,y,z,V_x,V_y,V_z,J_2,JJ_x,JJ_y,JJ_z,A_e,GM,delta_t,t_start,t_e,t_end)
    t = 0;
    VECTOR = 0;
    if (t_e == t_start && t_end > t_e) || (t_e < t_start && t_end > t_e)
            t = t_start : delta_t : (t_end - delta_t); % временной ветор прогноза
            VECTOR = zeros(6,length(t));
            VECTOR(:,1) = [x; y; z; V_x; V_y; V_z]; 
            VECTOR = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t,VECTOR,delta_t);
     elseif t_e > t_start && t_end > t_e 
            t1 = t_e : delta_t : (t_end - delta_t);
            VECTOR1 = zeros(6,length(t1));
            VECTOR1(:,1) = [x; y; z; V_x; V_y; V_z]; 
            VECTOR1 = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t1,VECTOR1,delta_t);
            t2 = t_e : -delta_t : t_start;
            VECTOR2 = zeros(6,length(t2));
            VECTOR2(:,1) = [x; y; z; V_x; V_y; V_z]; 
            VECTOR2 = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t2,VECTOR2,-delta_t);
            VECTOR2 = [rot90(rot90(VECTOR2(1,:))); ...
                       rot90(rot90(VECTOR2(2,:))); ...
                       rot90(rot90(VECTOR2(3,:))); ...
                       rot90(rot90(VECTOR2(4,:))); ...
                       rot90(rot90(VECTOR2(5,:))); ...
                       rot90(rot90(VECTOR2(6,:)))];

            VECTOR = [VECTOR2 VECTOR1(:,2:end)];
            t = [rot90(rot90(t2)) t1(1,2:end)];
     elseif  (t_e > t_start && t_end < t_e) || (t_e == t_start && t_end < t_e)
            t = t_start : -delta_t : (t_end - delta_t); % временной ветор прогноза
            VECTOR = zeros(6,length(t));
            VECTOR(:,1) = [x; y; z; V_x; V_y; V_z]; 
            VECTOR = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t,VECTOR,-delta_t);
            VECTOR = [rot90(rot90(VECTOR(1,:))); ...
                      rot90(rot90(VECTOR(2,:))); ...
                      rot90(rot90(VECTOR(3,:))); ...
                      rot90(rot90(VECTOR(4,:))); ...
                      rot90(rot90(VECTOR(5,:))); ...
                      rot90(rot90(VECTOR(6,:)))];
            t = rot90(rot90(t));
     elseif t_e < t_start && t_end < t_e
            t1 = t_start : delta_t : (t_e - delta_t);
            VECTOR1 = zeros(6,length(t1));
            VECTOR1(:,1) = [x; y; z; V_x; V_y; V_z]; 
            VECTOR1 = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t1,VECTOR1,delta_t);
            t2 = t_e : -delta_t : t_end;
            VECTOR2 = zeros(6,length(t2));
            VECTOR2(:,1) = [x; y; z; V_x; V_y; V_z]; 
            VECTOR2 = Rung_Kut(J_2,JJ_x,JJ_y,JJ_z,A_e,GM,t2,VECTOR2,-delta_t);
            VECTOR2 = [rot90(rot90(VECTOR2(1,:))); ...
                       rot90(rot90(VECTOR2(2,:))); ...
                       rot90(rot90(VECTOR2(3,:))); ...
                       rot90(rot90(VECTOR2(4,:))); ...
                       rot90(rot90(VECTOR2(5,:))); ...
                       rot90(rot90(VECTOR2(6,:)))];

            VECTOR = [VECTOR2 VECTOR1(:,2:end)];
            t = [rot90(rot90(t2)) t1(1,2:end)];
    end   
    tau = t - t_e;
    delta_x = JJ_x.*((tau.^2)/2);
    delta_y = JJ_y.*((tau.^2)/2);
    delta_z = JJ_z.*((tau.^2)/2);
    delta_Vx =  JJ_x.*tau;
    delta_Vy = JJ_y.*tau;
    delta_Vz = JJ_z.*tau;
    DELTA = [delta_x; delta_y; delta_z; delta_Vx; delta_Vy; delta_Vz];
    VECTOR = VECTOR + DELTA;
    [Optim] = [t;VECTOR];
end