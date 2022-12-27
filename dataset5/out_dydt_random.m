function out = out_dydt_random(C,r1,r2,l,inp,xi0)
        parameters
        f = make_f(l,r1,r2);
        dydt = @(y,u,C)[y(2); g-C*f(y(1))*(y(3)^2)/m; -R*y(3)/L + u/L];

        Ans = zeros(length(inp),4);
        Ans(1,2:4)=xi0;
        dvdt = zeros(length(inp),1);
        didt = zeros(length(inp),1);
        invalid_flag = false;
        iter = 0;

    for i=2:length(inp)
        % if i==2
        %     k1 = dydt(Ans(i-1,2:4),inp(i-1),C,gamma)*dt;
        %     Ans(i,2:4) = Ans(i-1,2:4) + (k1)';
        % elseif i==3
        %     k1 = dydt(Ans(i-2,2:4),inp(i-2),C,gamma)*dt;
        %     k2 = dydt(Ans(i-1,2:4),inp(i-1),C,gamma)*dt;
        %     Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2)/3)';
        % else
        %     k1 = dydt(Ans(i-3,2:4),inp(i-3),C,gamma)*dt;
        %     k2 = dydt(Ans(i-2,2:4),inp(i-2),C,gamma)*dt;
        %     k3=k2;
        %     k4 = dydt(Ans(i-1,2:4),inp(i-1),C,gamma)*dt;
        %     Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2+2*k3+k4)/6)';
        % end   

        k1 = dydt(Ans(i-1,2:4),inp(i-1),C)*dt;
        k2 = dydt(Ans(i-1,2:4)+(k1/2)',inp(i-1),C)*dt;
        k3 = dydt(Ans(i-1,2:4)+(k2/2)',inp(i-1),C)*dt;
        k4 = dydt(Ans(i-1,2:4)+(k3)',inp(i-1),C)*dt;
        Ans(i,1) = Ans(i-1,1) + dt;
        Ans(i,2:4) = Ans(i-1,2:4) + ((k1+2*k2+2*k3+k4)/6)';

        % k1 = dydt(Ans(i-1,2:4),inp(i-1),C,gamma);
        % k2 = dydt(Ans(i-1,2:4)+(k1/2)'*dt,inp(i-1),C,gamma);
        % Ans(i,2:4) = Ans(i-1,2:4) + ((k1+k2)/2)'*dt;

%         if Ans(i,2)>=Ans(1,2)
%             if i>200
%                 invalid_flag = true;
%                 iter = i;
%                 break
%             end
%             Ans(i,2)=Ans(1,2);
%             Ans(i,3)=0;
%         elseif Ans(i,2)<=0
% %             if i>100
%             invalid_flag = true;
%             iter = i;
%             break
% %             end
% %             Ans(i,2)=0;
% %             Ans(i,3)=0;
%         end

    end
% 
%     for i=1:length(inp)
%         res_dydt = dydt(Ans(i,2:4),inp(i),C,gamma)*dt;
%         dvdt(i)= res_dydt(2);
%         didt(i)= res_dydt(3);
%     end

    % 計算したposを出す
%     fprintf("ringe done");
    % if ~invalid_flag
    %     disp("valid!!!")
    %     out = struct("pos",Ans(:,2),"vel",Ans(:,3),"cur",Ans(:,4));
    % else
    %     out = struct("pos",false,"iter",iter);
    % end
    out = struct("pos",Ans(:,2),"vel",Ans(:,3),"cur",Ans(:,4));
end