function make_r = make_r(time)
    time5 = find(time==5,1);
    time10 = find(time==10,1);

    r = zeros(length(time),2);
    r(:,1)=time;
    r(1:time5,2)=0.04;
    r(time5:time10,2)=0.03;
    r(time10:end,2)=0.02;

    make_r = r;
end