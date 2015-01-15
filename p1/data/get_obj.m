
function get_obj(x, y, name);

fid = fopen('a.obj', 'w');
for i = 1 : size(x, 1);
    fprintf(fid,'v %f %f %f\n', x(i, 1), y(i, 1), 0);
end;
for i = 1 : size(x, 1);
    % fprintf(fid,'vn %f %f %f\n', 0, 0, 1);
end;
for i = 1 : size(tri2, 1);
    % fprintf(fid,'f %f//%f %f//%f %f//%f\n', tri2(i, 1), tri2(i, 1), tri2(i, 2), tri2(i, 2), tri2(i, 3), tri2(i, 3));
    fprintf(fid,'f %f %f %f\n', tri2(i, 1), tri2(i, 2), tri2(i, 3));
end;

fclose(fid);

triplot(tri2,x,y);

end;