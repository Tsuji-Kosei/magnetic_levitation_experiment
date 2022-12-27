function out = out_dydt_RL(R,L,inp,xi0)
        parameters_RL
        f = make_f(l,r1,r2);
        dydt = @(y,u,C,d)[y(2); g-C*f(y(1))*(y(3)^2)/m-d*y(2); -R*y(3)/L + u/L];

        Ans = zeros(length(inp),4);
        Ans(1,2:4)=xi0;
        dvdt = zeros(length(inp),1);
        didt = zeros(length(inp),1);

    for i=2:length(inp)
        % if i==2
        %     k1 = dydt(Ans(i-1,2:4),inp(i-1),C)*dt;
        %     Ans(i,2:4) = Ans(i-1,2:4) + (k1)';
        % elseif i==3
        %     k1 = dydt(Ans(i-2,2:4),inp(i-2),C)*dt;
        %     k2 = dydt(Ans(i-1,2:4),inp(i-1),C)*dt;
        %     Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2)/3)';
        % else
        %     k1 = dydt(Ans(i-3,2:4),inp(i-3),C)*dt;
        %     k2 = dydt(Ans(i-2,2:4),inp(i-2),C)*dt;
        %     k3=k2;
        %     k4 = dydt(Ans(i-1,2:4),inp(i-1),C)*dt;
        %     Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2+2*k3+k4)/6)';
        % end

        k1 = dydt(Ans(i-1,2:4),inp(i-1),C,d)*dt;
        k2 = dydt(Ans(i-1,2:4)+(k1/2)',inp(i-1),C,d)*dt;
        k3 = dydt(Ans(i-1,2:4)+(k2/2)',inp(i-1),C,d)*dt;
        k4 = dydt(Ans(i-1,2:4)+(k3)',inp(i-1),C,d)*dt;
        Ans(i,1) = Ans(i-1,1) + dt;
        Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2+2*k3+k4)/6)';
    end

    for i=1:length(inp)
        res_dydt = dydt(Ans(i,2:4),inp(i),C,d)*dt;
        dvdt(i)= res_dydt(2);
        didt(i)= res_dydt(3);
    end

    % 計算したposを出す
%     fprintf("ringe done");
    out = struct("pos",Ans(:,2),"vel",Ans(:,3),"cur",Ans(:,4));
end