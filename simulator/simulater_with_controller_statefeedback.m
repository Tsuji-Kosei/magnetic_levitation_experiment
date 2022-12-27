% C,r1,r2,l : parameters
% pos_lim : limitation of position (floor pos)
% xi0 : initial statement
% r : reference position
parameters_identified
pos_lim = 0.05;
res = controller_state_feedback();
gain = res.gain;
V0 =res.V0;
I0 = res.I0;
r = zeros(10000,1);
Ans = zeros(length(r),5);
xi0 = [0,0.03,0];
x_ideal = [I0,0.03,0];
Ans(1,2:4)=xi0;
x=xi0;

for i=2:length(r)
    % get new input
%         u = controller(r(i));
% %         u = u*5.5;
    if i<1000
        x=x_ideal;
    end
    x = x-x_ideal;
    input = -gain*x'+V0;
    input=input/5.5;
    if input>10
        input=10;
    elseif input<-10
        input=-10;
    end
    input = input*5.5;
    Ans(i,5)=input;
    % update state
    x=x+x_ideal;
    x = out_dydt_with_statefeedback(input,x,pos_lim);
    Ans(i,1)=Ans(i-1)+dt;
    Ans(i,2:4)=x;
    % fprintf("%d\n",i);
end

simulater = struct("time", Ans(:,1),"cur",Ans(:,2),"pos",Ans(:,3),"vel",Ans(:,4),"inp",Ans(:,5));

figure(200)
plot(simulater.time,simulater.pos,'b-')
xlim([0,10])
title('position')
figure(201)
plot(simulater.time,simulater.vel,'b-')
xlim([0,10])
title('velocity')
figure(202)
plot(simulater.time,simulater.cur,'b-')
xlim([0,10])
title('current')
figure(203)
plot(simulater.time,simulater.inp,'b-')
xlim([0,10])
title('input')
drawnow