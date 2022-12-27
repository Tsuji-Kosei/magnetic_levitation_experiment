function controller=controller()
    % x_1 is current x_2 is position x_3 is velocity
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
    mass=0.0044/grav;
    l=0.0277;
    r1=0.0217;
    r2=0.0492;
    C=4.7089*(5/0.95)^2;

    mag_y = C.*((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l)))+y.*(asinh(r1./y)-asinh(r2./y))).^2;
    ddyddt = (mass*grav-mag_y*I^2)/mass;
    % 電流電圧の関係
    R=31.68;
    L=3.165;
    dIdt_f=(-R*I)/L;
    dIdt_g = 1/L;

    %{
    磁気浮上系全体のシステム （U=V,X = [I,y,dydt],Y=I）;
        dXdt = sym_f+sym_g*U;
        Y = sym_h;
    %}
    X = sym('x',[3,1],'real');
    sym_f = [dIdt_f;dydt;ddyddt];
    sym_g = [dIdt_g;0;0];
    %状態変数をXに変換
    sym_f=subs(sym_f,[I,y,dydt],X.');
    sym_g=subs(sym_g,[I,y,dydt],X.');

    %出力を平衡点との誤差に変換
    y_equiv = sym('y_equiv','real')
    sym_h = [0,1,0]*X-y_equiv;

    %出力関数 h に対するシステムの相対次数(次差数)を確認
    Lgh = jacobian(sym_h,X)*sym_g;
    Lfh = jacobian(sym_h,X)*sym_f;
    LgLfh = jacobian(Lfh,X)*sym_g;
    LfLfh=jacobian(Lfh,X)*sym_f;
    LgLfLfh = jacobian(LfLfh,X)*sym_g;
    LfLfLfh = jacobian(LfLfh,X)*sym_f;
    %{
    LgLfLfhで初めてゼロになるのでシステムの時差数は3であり，システムの状態変数の次元と一致するため完全線形化が可能．
    このとき状態変数をZ = [h,Lfh,LfLfh].'と選べば，入力をU =
    -(LgLfLfh)^(-1)*(LfLfLfh)+(LgLfLfh)^(-1)*U_tilと取り直すことで元のシステムを
    以下の線形システムに書き換えることができる．
        dZdt = A*Z+B*U_til
        A = [0,1,0
            0,0,1
            0,0,0]
        B = [0
            0
            1];
    ここでU_tilを
        U_til = [-a0,-a1,-a2]*Z;
    と選べば，閉ループ系の係数行列は
        A_cl = [0,1,0
                0,0,1
                -a0,-a1,-a2];
    となり，その固有値は特性多項式
        s^3+a2*s^2+a1*s+a0=0
    の根と一致する．従って先に極を指定しておけば，入力のゲインを決めることができる．
    %}

    %線形化されたシステム dZdt=A_lin*Z+B_lin*U_til,Y_lin=C_lin*Z;
    A_lin = [0,1,0
        0,0,1
        0,0,0];
    B_lin = [0
        0
        1];
    C_lin = [1,0,0];
    %極の指定
    syms s
    %poly_den = (s+10)*(s+10)*(s+0.01);
    poly_den = (s+10)*(s+10)*(s+10);
    %ゲインの計算
    c = coeffs(poly_den);
    K_lin = -c(1:3)*1;

    %入力の計算
    Z_lin = [sym_h,Lfh,LfLfh].';
    U_til = K_lin*Z_lin;
    U = -(LgLfLfh)^(-1)*(LfLfLfh)+(LgLfLfh)^(-1)*U_til;
    
    %制御器(電圧)の関数の作成
    %f_U = matlabFunction(U,'Vars',X);
    %制御器(入力)
    %f_u = @(X) f_U(X)/6;
    u = U/5.5;
    f_u = matlabFunction(u, 'Vars',{X,y_equiv});
    controller=f_u;
end