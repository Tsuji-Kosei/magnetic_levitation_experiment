clear;
a =0;
b=1;
c=2;
syms e
f = test_function2(a,b,c);
f2 = f(2);
t = subs(f2,e,3);
