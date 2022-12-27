function simulater = simulater_with_controller(C,r1,r2,l,pos_lim,xi0,r,controller)
    % C,r1,r2,l : parameters
    % pos_lim : limitation of position (floor pos)
    % xi0 : initial statement
    % r : reference position
    parameters_with_controller

    Ans = zeros(length(r),4);
    Ans(1,2:4)=xi0;
    x=xi0;

    for i=2:length(r)
        % get new input
%         u = controller(r(i));
% %         u = u*5.5;
        input = controller(x',r(i));
        if input>10
            input=10;
        elseif input<-10
            input=-10;
        end
        input = input*5.5;
        % update state
        x = out_dydt_with_controller(C,r1,r2,l,input,x,pos_lim);
        Ans(i,1)=Ans(i-1)+dt;
        Ans(i,2:4)=x;
        % fprintf("%d\n",i);
    end

    simulater = struct("cur",Ans(:,2),"pos",Ans(:,3),"vel",Ans(:,4));
end
