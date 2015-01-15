
clc;
clear;

% contour = rgb2gray(imread('contour.png'));
% field = rgb2gray(imread('field.png'));

% picture
contour = imread('contour.png');
field = imread('field.png');

% edge points
fid = fopen('cont.txt', 'r');
[f, count]=fscanf(fid,'%d, %d\n', [2, 1500]);
fclose(fid);
 count = count/2;
 xpoints = f(1, 1:count);
 ypoints = f(2, 1:count);

 % size
[m, n]=  size(contour);

% boundary points
figure;
 plot(xpoints, m-ypoints, '.',....
     'MarkerSize', 3);
 hold on;
 axis equal;
axis([0 n 0 m]);
hold off;

% random point
randsize =  3000;
randpic = zeros(m, n);
for i = 1:randsize;
    y = unidrnd(m);
    x = unidrnd(n);
    randpic(y, x) = 255;
end;

% substract back & contour points
inner = field- contour;
for i = 1:m;
    for j = 1:n;
        if (randpic(i, j) == 255....
                && inner(i, j) ~= 255)
            randpic(i, j) = 0;
        end;
    end;
end;

% inner points
count2 = count;
for i = 1:m;
    for j = 1:n;
        if (randpic(i, j) == 255)
                y = i;
                x = j;
                count2 = count2+1;
                xpoints(1, count2) = x;
                ypoints(1, count2) = y;
        end;
    end;
end;

% show inner points
figure;
 plot(xpoints(1, count+1:count2), m-ypoints(1, count+1:count2),....
'.',....     
'MarkerSize', 10);
 hold on;
 axis equal;
axis([0 n 0 m]);
hold off;


% % constrains
% C = [];
% for i = 1:count-1;
%     C(i, 1:2) = [i, i+1];
% end;
% C(count, 1:2) = [count, 1];
% 
% % delauny
% xp2(1:count2, 1) = xpoints(1, 1:count2);
% yp2(1:count2, 1) = ypoints(1, 1:count2);
% DT = DelaunayTri(xp2, yp2, C);
% figure;
% triplot(DT,xp2,yp2);

% use another delaunay
% don't know why

% delauny
xp2(1:count2-count, 1) = xpoints(1, count+1:count2);
yp2(1:count2-count, 1) = ypoints(1, count+1:count2);
DT = delaunay(xp2, yp2);
figure;
triplot(DT,xp2,m-yp2);
hold on;
 axis equal;
axis([0 n 0 m]);
hold off;

% delete edge
tri = DT+count;
x = xpoints(:);
y = ypoints(:);
a = field;
tri2 = [];
count = 1;
for i= 1: size(tri, 1);
    
    i1 = tri(i, 1);
    i2 = tri(i, 2);
    i3 = tri(i, 3);
    
    p1 = [x(i1, 1), y(i1, 1)];
    p2 = [x(i2, 1), y(i2, 1)];
    p3 = [x(i3, 1), y(i3, 1)];
    
     % p1 p2
    [ re ] = test_line_in_pic( a, p1, p2 );    
    [ re2 ] = test_line_in_pic( a, p1, p3 );  
    [ re3 ] = test_line_in_pic( a, p2, p3 );
    
    if (re == 0....
            &&re2 == 0.....
            &&re3 == 0);
                  tri2(count, 1:3) = tri(i, :);
          count = count+1;
    end;
end;

triplot(tri2,x,m-y),
hold on;
 axis equal;
axis([0 n 0 m]);
hold off;
