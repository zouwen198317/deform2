a = rgb2gray(imread('1.png'));

x = [];
y = [];
count = 1;
add_pixels = 50;

[m, n] = size(a);

for i = 1 :add_pixels: m;
    for j = 1:add_pixels:n;
        if (a(i, j) ~= 0);
            x(count, 1) = j;
            y(count, 1) = m-i;
            count = count+1;
        end;
    end;
end;

tri = delaunay(x,y);

tri2 = [];
count = 1;
for i= 1: size(tri, 1);
    
    i1 = tri(i, 1);
    i2 = tri(i, 2);
    i3 = tri(i, 3);
    
    p1 = [x(i1, 1), y(i1, 1)];
    p2 = [x(i2, 1), y(i2, 1)];
    p3 = [x(i3, 1), y(i3, 1)];
    
    m1 = (p1+p2)/2;
    m2 = (p2+p3)/2;
    m3 = (p1+p3)/2;
    
    m1 = floor(m1);
     m2 = floor(m2);
      m3 = floor(m3);
      
      if (a(m-m1(1, 2), m1(1, 1)) ~= 0....
          &&a(m-m2(1, 2), m2(1, 1)) ~= 0....
          &&a(m-m3(1, 2), m3(1, 1)) ~= 0);
          tri2(count, 1:3) = tri(i, :);
          count = count+1;
      end;
    
end;

plot(x,y,'.','markersize',12)
xlabel('Longitude'), ylabel('Latitude')
grid on

hold on, triplot(tri2,x,y), hold off

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