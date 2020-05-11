function [EC2EN] = ec2en(Xr,Yr,Zr,Xp,Yp,Zp)
    a = 6378137; % экваториальный радиус в WGS 84
    b = 6356752.3141; % пол€рный радиус в WGS 84
    e2 = ((a^2)-(b^2))/(a^2);
    e_2 = ((a^2)-(b^2))/(b^2);
    e4 = ((a^4)-(b^4))/(a^4);
    r = sqrt((Xr.^2) + (Yr.^2));
    G = (r.^2) + (1-e2).*(Zr^2) - e2*((a^2) - (b^2));
    F = 54*(b^2).*(Zr.^2);
    c = (e4.*F.*(r.^2))./(G.^3);
    s = (1 + c + sqrt((c.^2) + 2.*c)).^(1/3);
    P = F./(3*((s+(1/s)+1)^2)*(G^2));
    Q = sqrt(1 + 2.*e4.*P);
    r0 = -(P.*e2.*r)./(1+Q) + sqrt((1/2)*(a^2).*(1+(1./Q)) - (P.*(1-e2)*(Zr.^2))./(Q.*(1+Q)) - (1/2).*P.*(r.^2));
    V = sqrt(((r - e2.*r0).^2) + ((1 - e2).*Zr.^2));
    z0 = ((b^2).*Zr)./(a.*V);
    Br = atan((Zr + e_2.*z0)./r);
    Lr = atan2(Yr,Xr);
    cor = [-sin(Lr) cos(Lr) 0;...
           -sin(Br).*cos(Lr) -sin(Br).*sin(Lr) cos(Br);...
            cos(Br).*cos(Lr) cos(Br).*sin(Lr) sin(Br)]...
                 *[(Xp - Xr); (Yp - Yr); (Zp - Zr)];
    [EC2EN] = cor';
end

