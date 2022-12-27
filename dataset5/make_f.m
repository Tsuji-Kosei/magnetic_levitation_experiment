function f_y = make_f(l, r1, r2)
    function f = proto_f(y)
        f = ((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l))) + y.*(asinh(r1./y)-asinh(r2./y))).^2;
%         if y>=0
%             if y<=0.05
%                 f=1;
%             else
%                 f = ((y+l).*(asinh(r2./(y+l))-asinh(r1./(y+l))) + y.*(asinh(r1./y)-asinh(r2./y))).^2;
%             end
%         else
%             f=1;
%         end
    end
f_y = @proto_f;
end
