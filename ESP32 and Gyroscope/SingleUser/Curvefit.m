%plot(gyrotime , gyrodata);
%hold on;
%plot(halleffecttime , halleffectdata);

%figure;
%plot(newtimes , newdata , newtimes , hallnew);
%title('Speed values of Gyroscope output vs HallEffect output');
%xlabel('Time (ms)');
%ylabel('Speed value (m/s)');
%legend({'Gyro','HallEffect'},'Location','southeast')

 p1 =    0.005429  ;
 p2 =    -0.08082  ;
 p3 =      0.3511  ;
 p4 =     -0.3186  ;
 p5 =       0.609  ;
 p6 =     0.06184  ;
 x1=newdata.*p5;
 x2=(newdata.^2).*p4;
 x3=(newdata.^3).*p3;
 x4= (newdata.^4).*p2;
 x5= (newdata.^5).*p1;
 y1= p6 + x1 + x2 + x3 +x4 + x5;
 
 figure;
 plot(newdata , y1);
 xlabel('Gyro data');
ylabel('Curve fit data');