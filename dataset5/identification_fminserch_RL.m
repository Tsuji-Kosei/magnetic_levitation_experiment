clear
close all

loaddir = "C:\Users\tsuji\デスクトップ\dataset4\";
list = dir(loaddir + "*.fig");
ver = "1";
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

% 　移動平均(n項)
% n=11; %odd
% for i = (n+1)/2:length(inp(:,2))-(n-1)/2
%     tmp_data=0;
%     for j =0:n-1
%         fprintf("%d,%d\n",i, j);
%         tmp_data= tmp_data+inp(i-5+j,2);
%     end
%     inp(i,2)=tmp_data/n;
% end

if prod(inp(:,1) == cur(:,1))==0 ||  prod(inp(:,1) == pos(:,1))==0
    disp('inp, pos, cur のサイズが違います')
end

xi0 = [pos(1,2),0,cur(1,2)];
y_sim = @(C) out_dydt_RL(C(1),C(2),inp(:,2),xi0);
% y_sim = Copy_of_out_dydt(inp(:,2),xi0);

figure
plot(pos(:,1),pos(:,2))
bestx=[];
bestres = inf;

iter=0;
% while true
try
iter=iter+1;
x0 = [30,2];

err = @(t) sum((cur(:,2) - y_sim(t).cur).^2);

options = optimset('Display','iter',"MaxIter",10000);
[x,fval] = fminsearch(err,x0,options);


if fval < bestres
    bestres = fval;
    bestx = x;
    fprintf('bestres = %d, R = %d, L = %d, iteration:%d\n', bestres, bestx, iter)
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
    
% if iter > 50000
%     break;
% end

% end
fprintf('bestres = %d, bestx = %d, %d, iteration:%d\n', bestres, bestx,i);




