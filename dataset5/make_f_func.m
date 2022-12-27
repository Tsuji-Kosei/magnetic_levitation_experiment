function f_y = make_f_func(l, r2)
    % r1 = sym('r1');
    function f = proto_f(y, r1)
        f = ((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l))) + y.*(asinh(r1./y)-asinh(r2./y))).^2;
    end
f_y = @proto_f;
end
