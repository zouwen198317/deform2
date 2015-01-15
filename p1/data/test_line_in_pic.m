function [ re ] = test_line_in_pic( im, be, en )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

if be(1, 1) > en(1, 1);
    tmp =  be;
    be = en;
    en = tmp;
end;

ally = en(1, 2) - be(1, 2);
allx = en(1, 1) - be(1, 1);

for j = be(1, 1)+1:en(1, 1)-1;
    tmpx = j;
    tmpy = floor((j-be(1, 1))/allx*ally+be(1, 2));
    if im(tmpy, tmpx) == 0;
        re = 1;
        return;
    end;
end;

re = 0;
return;

end

