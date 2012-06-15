%Amplitudengang des Tiefpassfilters
   f=[10 100 800 900 1000 1100 1800 3000 7000 12000 15000 ];
   H=[2.1760 2.1760 2.1349 2.1349 2.1212 2.0802 1.7654 0.6295 0.0547 0.0547 0.0547 ]./11;
   Amp= 20*log(H);
   amp = Amp -max(Amp);
   semilogx(f,amp)
   grid on;
   
    figure(1); 
    clf();
    b = mkfilter(3100/(2*pi),2,'butterw');
    b = b^4;
    hold on
    semilogx(f,amp,'r');
    bode(b,{1*10^0,2*10^4});
    LEGEND('Aufgenommener Amplitudengang','Idealer Amplitudengang');
    grid on;
   
   %yp = polyfit(f,Amp,1);
   %figure(2)
   %semilogx(f,polyval(yp,f));
   
   %yp2 = spline(f,Amp);
   %figure(3)
   %semilogx(f,ppval(yp2,f));

