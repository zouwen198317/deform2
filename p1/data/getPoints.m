function getPoints( x, y, name )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

x = x(:);
y = y(:);

fid = fopen(name, 'w');
for i = 1 : size(x, 1);
    fprintf(fid,'v %f %f %f\n', x(i, 1), y(i, 1), 0);
end;

for i = 1 : size(x, 1);
    fprintf(fid,'vn %f %f %f\n', 0, 0, 1);
end;

fclose(fid);

end

