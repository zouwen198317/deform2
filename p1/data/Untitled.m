
for i = 1 : count-1;
    
    i1 = i;
    i2 = i+1;
    
    
    
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
    