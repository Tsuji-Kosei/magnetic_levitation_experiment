clear
close all

syms y l r1 r2 C u

F_sysid = C.*((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l)))+y.*(asinh(r1./y)-asinh(r2./y))).^2.*u.^2;

f_F_sysid = matlabFunction(F_sysid,'Vars',{u,y,l,r1,r2,C});
[f_sum_error] = make_sum_error(f_F_sysid);

%initial estimate
[u_data,y_data,mg] = f_data_list();
l0 = 0.07;
r10 = 0.03;
r20 = 0.054;
u0 = u_data(6);
y0 = y_data(6);
mg = mg;

C0 = mg/(f_F_sysid(u0,y0,l0,r10,r20,1));
p0 = [l0,r10,r20,C0];
[p_ans,val_res] = fminsearch(@(p) f_sum_error(p),p0)

% check result
F_u = sqrt(mg./(C.*((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l)))+y.*(asinh(r1./y)-asinh(r2./y))).^2));
f_F_u = matlabFunction(F_u,'Vars',{y,l,r1,r2,C});
I = ones(size(y_data));
u_predict = f_F_u(y_data,p_ans(1)*I,p_ans(2)*I,p_ans(3)*I,p_ans(4)*I);
%u_predict = f_F_u(y_data,l0*I*50,r10*I*5,r20*I,C0*I*0.0015);
figure(1)
plot(y_data,u_data,'*-b',y_data,u_predict,'*-r','Linewidth',2)
xlabel('y','Interpreter','Latex')
ylabel('u','Interpreter','Latex')

%magnetic force simulation
u_specify = 4.3;
f_B = @(y) f_F_sysid(u_specify,y,p_ans(1),p_ans(2),p_ans(3),p_ans(4));
y_check = linspace(0.1,6,100)*1e-2;
figure(2)
plot(y_check*1e2,f_B(y_check),'g',y_check*1e2,mg*ones(size(y_check)),'--k')
xlabel('y')
ylabel('magnetic force')
legend('magnetic force','gravity')





