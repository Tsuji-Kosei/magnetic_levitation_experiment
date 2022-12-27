function [f_sum_error] = make_sum_error(f_F_sysid)
[u,y,mg] = f_data_list();
    function val = proto_make_sum_error(p)
        I = ones(size(y));
        val = norm(mg-f_F_sysid(u,y,p(1)*I,p(2)*I,p(3)*I,p(4)*I))^2*30;
        %val = (mg-f_F_sysid(u,y,p(1)*I,p(2)*I,p(3)*I,p(4)*I))*100;
    end
f_sum_error = @proto_make_sum_error;
end