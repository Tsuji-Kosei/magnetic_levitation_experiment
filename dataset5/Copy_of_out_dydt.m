function out = Copy_of_out_dydt(inp,xi0)
        Ans = zeros(length(inp),4);
        Ans(1,2:4)=xi0;
%         dvdt = zeros(length(inp),1);
%         didt = zeros(length(inp),1);
       
    function sol = proto_RK(C,r1,r2,l)
            % true parameters 
            g = 9.80;    % [m/s^2]
            % L = 3.165;   % [H]
            % R = 31.68;   % [ohm]
            L = 2.109;   % [H]
            R = 28.205;   % [ohm]
            
            % measured parameters
            m = 4.4e-3;  % [kg]
%             l = 70.0e-3; % [m]
%             r2= 98.0e-3 / 2; % [m]
            
            % unknown parameters
            % r1= 21.7e-3; % [m]
            % mu0 = 4*pi*10e7;
            % mu0 mur n S --> C
            
            % sample time
            dt = 0.0010; % [s]
            
            f = make_f(l,r1,r2);
            dydt = @(y,u,C)[-y(2); g-C*f(y(1))*(y(3)^2)/m; -R*y(3)/L + u/L];
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
    
            k1 = dydt(Ans(i-1,2:4),inp(i-1),C)*dt;
            k2 = dydt(Ans(i-1,2:4)+(k1/2)',inp(i-1),C)*dt;
            k3 = dydt(Ans(i-1,2:4)+(k2/2)',inp(i-1),C)*dt;
            k4 = dydt(Ans(i-1,2:4)+(k3)',inp(i-1),C)*dt;
            Ans(i,1) = Ans(i-1,1) + dt;
            Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2+2*k3+k4)/6)';
        end
        sol = Ans(:,2);
    end

%     for i=1:length(inp)
%         res_dydt = dydt(Ans(i,2:4),inp(i),C)*dt;
%         dvdt(i)= res_dydt(2);
%         didt(i)= res_dydt(3);
%     end
% 
%     % 計算したposを出す
%     fprintf("ringe done");
%     out = struct("pos",Ans(:,2),"vel",Ans(:,3),"cur",Ans(:,4));
    out = @proto_RK;
end