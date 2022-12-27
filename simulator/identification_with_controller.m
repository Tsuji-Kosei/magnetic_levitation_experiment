clear
close all

loaddir = "C:\Users\tsuji\デスクトップ\新入生課題\dataset5\";
list = dir(loaddir + "*.fig");
ver = "8";
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
% 制御を始める時刻（球が浮く時刻）
% time05 = find(position(:,1)==0.5,1);
% 制御をやめる時刻
time15 = find(position(:,1)==15,1);

% % position だけデータ数が少ないので他を間引く
% temp_inp = input(1:2:end,:);
% temp_cur = current(1:2:end,:);

pos = position(1:time15,:);
inp = input(1:time15,:);
cur = current(1:time15,:);
vel = velocity(1:time15,:);

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
n=5; %odd
for i = (n+1)/2:length(inp(:,2))-(n-1)/2
    tmp_data=0;
    for j =0:n-1
        % fprintf("%d,%d\n",i, j);
        tmp_data= tmp_data+inp(i-(n-1)/2+j,2);
    end
    inp(i,2)=tmp_data/n;
end

if prod(inp(:,1) == cur(:,1))==0 ||  prod(inp(:,1) == pos(:,1))==0
    disp('inp, pos, cur のサイズが違います')
end


% figure
% plot(pos(:,1),pos(:,2))

% x_1 is current x_2 is position x_3 is velocity
controller = controller();
xi0 = [cur(1,2),pos(1,2),0];
pos_lim = pos(1,2);
r = make_r(pos(:,1));
y_sim = @(param) simulater_with_controller(param(1),param(2),param(3),param(4),pos_lim,xi0,r(:,2),controller);
err = @(param) sum((pos(:,2) - y_sim(param).pos).^2)*1000;

param0 = [4000,0.03,0.04,0.055];

A=[0,1,-1,0];
b=-0.01;
Aeq=[];
beq = [];
lb=[0,0.03,0.03,0.05];
ub = [1000000,0.054,0.054,0.07];
options = optimset('Display','iter',"MaxIter", 10000);
[x,fval] = fmincon(err,param0,A,b,Aeq,beq,lb,ub);

fprintf('fval = %d, C = %d, r1 = %d, r2 = %d, l = %d\n', fval, x)
figure(200)
plot(pos(:,1),pos(:,2),'k-',pos(:,1),y_sim(x).pos,'b-', pos(:,1),r(:,2),'r-')
xlim([0,15])
title('position')
figure(201)
plot(vel(:,1),vel(:,2),'k-',vel(:,1),y_sim(x).vel,'b-')
xlim([0,15])
title('velocity')
figure(202)
plot(cur(:,1),cur(:,2),'k-',cur(:,1),y_sim(x).cur,'b-')
xlim([0,15])
title('current')
drawnow




