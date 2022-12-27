clear
close all

loaddir = "C:\Users\tsuji\デスクトップ\dataset\";
list = dir(loaddir + "*.fig");
ver = "2";
index = ["position"+ver, "input"+ver, "current"+ver, "velocity"+ver];


data = struct();
num  = length(list);
for i = 1:num
    for  j = 1 : length(index)
        if strfind(list(i).name,index(j))
            filename = split(list(i).name, ver);
            fig = openfig(loaddir + list(i).name,'invisible');
            graph = fig.CurrentAxes.Children(1);
            data = setfield(data, filename{1}, [graph.XData',graph.YData']); 
        end
    end
    
%     filename = split(list(i).name,'.');
end

input    = data.input;
position = data.position;
current  = data.current;
velocity = data.velocity;

% データの前処理
% 制御をやめる時刻
time10 = find(position(:,1)==10,1);

% % position だけデータ数が少ないので他を間引く
% temp_inp = input(1:2:end,:);
% temp_cur = current(1:2:end,:);

pos = position(1:time10,:);
inp = input(1:time10,:);
cur = current(1:time10,:);
vel = velocity(1:time10,:);

inp(:,2) = inp(:,2)*5.5;
% nan除去
for i = 2:length(pos(:,2))
    if isnan(pos(i,2))
        pos(i,2) = pos(i-1,2);
    end
end
for i = 2:length(vel(:,2))
    if isnan(vel(i,2))
        vel(i,2) = vel(i-1,2);
    end
end
for i = 2:length(cur(:,2))
    if isnan(cur(i,2))
        cur(i,2) = cur(i-1,2);
    end
end

%　移動平均(5項)
% for i =3:length(pos(:,2))-2
%     pos(i,2)=(pos(i-2,2)+pos(i-1,2)+pos(i,2)+pos(i+1,2)+pos(i+2,2))/5;
% end


if prod(inp(:,1) == cur(:,1))==0 ||  prod(inp(:,1) == pos(:,1))==0
    disp('inp, pos, cur のサイズが違います')
end

% pos 描画
% figure
% plot(pos(:,1),pos(:,2))
% bestx=[];
% bestres = inf;


xi0 = [pos(1,2),0,cur(1,2)];
res_runge = out_dydt_func(inp(:,2),xi0);
syms C r1
i=1;
while true
    try
    
x0 = [20000*rand(1), 0.04*(rand(1))];

substitute = @(f) subs(f,C,x0(1),r1,x0(2));
err = sum((pos(:,2) - arrayfun(substitute, res_runge.pos)).^2);

options = optimset('Display','iter','MaxIter', 10000);
[x,fval] = fminsearch(err,x0,options);

% fprintf('C:%d, r1:%d, L:%d, R:%d\n',x0(1),x0(2),x0(3),x0(4));
% fprintf('C:%d, r1:%d\n',x0(1),x0(2));
% [x, resnorm] = lsqnonlin(err,x0,[0,0],[inf,0.05],optimoptions('lsqnonlin','Display','iter'));
%[x, resnorm] = lsqnonlin(err,x0,[],[],optimoptions('lsqnonlin','Display','iter'));
% oldoptions = optimoptions(@lsqcurvefit,'Algorithm','levenberg-marquardt',...
%     'MaxIterations',500,'MaxFunctionEvaluations',1500);
% options = optimoptions(oldoptions,'MaxIterations',10000,'MaxFunctionEvaluation',40000);
% 
% oldoptions = optimoptions(@lsqcurvefit,'Algorithm','levenberg-marquardt',...
%     'MaxIterations',500);
% options = optimoptions(oldoptions,'MaxIterations',100);
% x = lsqcurvefit(fun,x0,tdata,xdata,[],[],options)

%x = lsqnonlin(@(x) fun(x,tdata),x0)
%  [x, resnorm] = lsqcurvefit(fun,x0,t_real-t_real(1),con(:,1),[],[],optimoptions('lsqcurvefit','Display','none'));
%  [x, resnorm] = lsqcurvefit(fun,x0,tdata,xdata,lb, ub)
%  [x, resnorm] = lsqcurvefit(fun,x0,tdata,xdata,lb,ub,options)

if fval < bestres
    bestres = resnorm;
    bestx = x0;
    iter = i;
    fprintf('bestres = %d, bestx = %d, %d, iteration:%d\n', bestres, bestx,iter)
    figure(200)
    plot(pos(:,1),pos(:,2),'k-',pos(:,1),y_sim(bestx).pos,'b-')
    xlim([0,10])
    figure(201)
    plot(vel(:,1),vel(:,2),'k-',vel(:,1),y_sim(bestx).vel,'b-')
    xlim([0,10])
    figure(202)
    plot(cur(:,1),cur(:,2),'k-',cur(:,1),y_sim(bestx).cur,'b-')
    xlim([0,10])
    legend('Data','Fitted exponential')
    title('Data and Fitted Curve -x-')
    drawnow
end
    catch
    end
    
if i > 100
    break;
end

i=i+1;
end
fprintf('bestres = %d, bestx = %d, %d, iteration:%d\n', bestres, bestx,i);




