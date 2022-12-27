function out = out_dydt_with_controller(C,r1,r2,l,u,x,pos_lim)
    % x_1 is current x_2 is position x_3 is velocity
    parameters_with_controller
    f = make_f(l,r1,r2);
    % dydt = @(y,u,C,gamma)[y(2); g-C*f(y(1))*(y(3)^2)/m-gamma*y(2); -R*y(3)/L + u/L];
    dydt = @(y,u,C)[-R*y(1)/L + u/L; y(3); g-C*f(y(2))*(y(1)^2)/m];  

    % Runge-Kutta method
    % k1 = dydt(x,u,C)*dt;
    % k2 = dydt(x+(k1/2)',u,C)*dt;
    % k3 = dydt(x+(k2/2)',u,C)*dt;
    % k4 = dydt(x+(k3)',u,C)*dt;
    % next_x = x+((k1+2*k2+2*k3+k4)/6)';
    
    % Heun method
    k1 = dydt(x,u,C);
    k2 = dydt(x+(k1/2)'*dt,u,C);
    next_x = x+((k1+k2)/2)'*dt;
    % Ans(i,2:4) = Ans(i-1,2:4) + ((k1+k2)/2)'*dt;
    
    if next_x(2)>=pos_lim
        next_x(2) = pos_lim;
        next_x(3)=0;
    elseif next_x(2)<=0
        next_x(2)=0;
        next_x(3)=0;
    end

    out = next_x;
end