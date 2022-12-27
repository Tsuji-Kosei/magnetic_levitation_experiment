function out = out_dydt_func(inp,xi0)

    parameters

%     sym x [1 3];
%     sym u;
%     sym C r1;
    x = sym('x',[3,1],'real');
    u = sym('u','real');
    C = sym('C','real');
    r1 = sym('r1','real');
    
    f = make_f_func(l,r2);
    dxdt = [-x(2); g-C*f(x(1), r1)*x(3)^2/m; -R*x(3)/L + u/L];

    F = matlabFunction(dxdt,'Vars',{x,u,C,r1});
    k_1 = @(x,u,C,r1) F(x,u,C,r1);
    k_2 = @(x,u,C,r1) F(x + dt*k_1(x,u,C,r1)/2, u,C,r1);
    k_3 = @(x,u,C,r1) F(x + dt*k_2(x,u,C,r1)/2, u,C,r1);
    k_4 = @(x,u,C,r1) F(x + dt*k_3(x,u,C,r1), u,C,r1);
    f_xnext =@(x,u,C,r1) x + dt*(k_1(x,u,C,r1) + 2*k_2(x,u,C,r1)+ 2*k_3(x,u,C,r1) + k_4(x,u,C,r1))/6;

    dvdt = zeros(length(inp),1);
    didt = zeros(length(inp),1);

    Ans = zeros(length(inp),4);
    Ans = num2cell(Ans);
    x_now = xi0;
    Ans(1,2:4)={x_now};
    
    for i=1:length(inp)
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
        % k1 = dydt(Ans(i-1,2:4),inp(i-1))*dt;
        % k2 = dydt(Ans(i-1,2:4)+(k1/2)',inp(i-1))*dt;
        % k3 = dydt(Ans(i-1,2:4)+(k2/2)',inp(i-1))*dt;
        % k4 = dydt(Ans(i-1,2:4)+(k3)',inp(i-1))*dt;
        % Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2+2*k3+k4)/6)';
        x_next = @(C,r1)f_xnext(x_now, inp(i),C,r1);
        % Ans(i+1,1) = Ans(i,1) + dt;
        Ans(i+1,2:4) = {x_next};
        x_now = x_next;
        fprintf("iter_num: %d\n", i)
    end

    % for i=1:length(inp)
    %     res_dydt = dydt(Ans(i,2:4),inp(i))*dt;
    %     dvdt(i)= res_dydt(2);
    %     didt(i)= res_dydt(3);
    % end

    % 計算したposを出す
    out = struct("pos",Ans(:,2),"vel",Ans(:,3),"cur",Ans(:,4));
end