
load data

figure;
 plot(xp2, yp2,....
'.',....     
'MarkerSize', 10);

DT = DelaunayTri(xp2, yp2);
figure;
triplot(DT,xp2,yp2);

DT2 = delaunay(xp2, yp2);
figure;
triplot(DT2,xp2,yp2);