clear
set(0,'DefaultTextInterpreter','latex');
set(0,'DefaultLegendInterpreter','latex');
set(0,'DefaultAxesFontSize',12);
set(0,'DefaultLineLineWidth',0.5);
set(0,'DefaultAxesLineWidth',0.5);

l= 0.054713702626590;
r1 = 0.026251827551707;
r2 = 0.043780353749413;
f = make_f(l,r1,r2);

figure(1)
fplot(@(y) f(y),[-0.05 0.05],'b')
xlabel('$y$')
ylabel('$\mathrm{f}_{\mathrm{mag}}(y)$')