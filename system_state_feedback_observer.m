clear

%{
磁気浮上系の球の高さについてのEOM
    m*ddyddt=m*g-f_mag(y)*I^2,
    f_mag(y)= C.*((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l)))+y.*(asinh(r1./y)-asinh(r2./y))).^2;
システム同定の結果
    [l,r1,r2,C]=[0.0277    0.0217    0.0492    4.7089*(5/0.95)^2];
重さ mg=0.004, m=0.004/9.80;

電流、電圧の関係
    dIdt=(V-R*I)/L;
システム同定の結果
    R=31.68;
    L=3.165;
%}

syms V I u y dydt

% 磁気浮上系の球の高さについてのEOM
grav=9.80;
mass=0.0044;
l=0.0277;
r1=0.0217;
r2=0.0492;
C=4.7089*(5/0.95)^2*grav;

mag_y = ((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l)))+y.*(asinh(r1./y)-asinh(r2./y))).^2;
diff_mag_y = diff(mag_y,y);

f_mag_y = matlabFunction(mag_y, 'Vars',{y});
f_diff_mag_y = matlabFunction(diff_mag_y, 'Vars',{y});


ddyddt = (mass*grav-mag_y*I^2)/mass;
% 電流電圧の関係
R=31.68;
L=3.165;
dIdt_f=(-R*I)/L;
dIdt_g = 1/L;

% 平衡点(y0)近傍における電流値(I0)、電圧値(V0)
y0 = 0.020;
I0 = sqrt((mass*grav)/(C*f_mag_y(y0)));
V0 = R*I0;

% 磁気浮上系システムのモデルの伝達関数（入力: V->y）
s = tf('s');
Np = -2*C*f_mag_y(y0)*I0;
Dp = (s^2+(C*f_diff_mag_y(y0)*I0)/mass)*(s+R/L)*mass*L;
model_tf = Np/Dp;

% num_d = tfdata(Dp);
% 
% [A, B, C, D] = tf2ss(Np, num_d{1});

f0 = f_mag_y(y0);
df0 = f_diff_mag_y(y0);

Ap = [0, 1, 0; -C*df0*I0^2/mass, 0, -2*C*f0*I0/mass; 0, 0, -R/L];
Bp = [0; 0; 1/L];
Cp = [1, 0, 0; 0, 0, 1];
Dp = 0;

lambda = 200;
alpha = -C*df0*I0^2/mass;
D = [-C*df0*I0^2/mass-lambda^2, -2*C*f0*I0/mass];
W = [0;1;0];
V = [1,0;lambda,0;0,1];

Ob=obsv(Ap,Cp);
unob = length(Ap)-rank(Ob);
Co=ctrb(Ap,Bp);
unct = length(Ap)-rank(Co);

p = [-2, -2.5, -2.3];
K = place(Ap,Bp,p);
q = [-10,-11,-12];
Apt = transpose(Ap);
Cpt = transpose(Cp);
L = place(Apt,Cpt,q);

