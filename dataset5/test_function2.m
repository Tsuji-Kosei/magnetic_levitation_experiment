function f_y = test_function2(a,b,c)
    e = sym('e');
    function f = bbb(d)
        f = a+b+c+d+e;
    end
f_y = @bbb;
end
