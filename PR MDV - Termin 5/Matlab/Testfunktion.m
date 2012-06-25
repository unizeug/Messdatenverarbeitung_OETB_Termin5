%testfunktion
clear;clc;

%%Variablen
Grenzfrequenz=1000;
Abtastrate = 15000;
Abtastperiode = 1/Abtastrate;
Filterordnung = 85;
x_k = zeros(Filterordnung,1);
x_k(1) = 1;
x_k = x_k';
x = 1:length(x_k);


%%Filtercoeffizenten berechen
b_k = getFIRTiefpass( Grenzfrequenz, Abtastperiode, Filterordnung );

%% Fenster drüberlegen

N=length(b_k);

%erstellen eines Rechteckfensters
wn1 = ones(N,1);
%erstellen eines Hanningfensters
wn2 = hanning(N);
%erstellen eines Blackmanfensters
wn3 = blackman(N);
%erstellen eines Hammingfensters
wn4 = hamming(N);


wn = wn2;

b_k = b_k.*wn';

%%Impulsantwort bestimmen
y_k = DecimFilt(b_k, x_k, 1);

%% Frequenzgang
y_k_ZP = zeros(2^20,1);
y_k_ZP(1:length(y_k)) = y_k;
y_k_DFT = FFTSHIFT(fft(y_k_ZP));
%y_k_DFT = FFTSHIFT(fft(y_k));

N2 = length(y_k_DFT);

%Amplitudengang
f_DFT = (-N2/2:N2/2-1)*Abtastrate/N2;
y_k_DFT_abs = 20*log10(abs(y_k_DFT)/sum(1));

%Phasengang
y_k_phase = unwrap(angle(y_k_DFT)/sum(1));

%% plotten

%Impulsantwort
% figure(11); clc;clf;
% hold on;
% stem (x, y_k);
% %plot(x,wn,'r');
% hold off;
% grid ();
%  title('Impulsantwort');
%  xlabel('t/s');
%  ylabel('u/V');

Grenze1=ones(length(f_DFT),1)*-3;
Grenze2=Grenze1*20;
Grenze31=1000;
Grenze32=linspace(-150,0);
Grenze41=1500;
Grenze42=Grenze32;

%Frequenzgang
figure(12); clc;clf;
%Amplitudengang
subplot(2,1,1);
hold on
    plot(f_DFT,y_k_DFT_abs);
    plot(f_DFT,Grenze1,'r');
    plot(f_DFT,Grenze2,'r');
    plot(Grenze31,Grenze32,'r');
    plot(Grenze41,Grenze42,'r');
hold off
 title('Amplitudenspektrum');
 xlabel('f/Hz');
 ylabel('A(f)[dB]');  
%phasengang
subplot(2,1,2);
plot(f_DFT,y_k_phase);
 title('Phasenspektrum');
 xlabel('f/Hz');
 ylabel('phi(f)');  
grid();





%% Filtercoeffizenten exportieren

  b_k_uebergeben = int16(y_k.*2^15);
  exportCoeff(b_k_uebergeben);
%  figure(14)
%  plot(b_k_uebergeben)

%% Amplitudengang 

% gemessener Digitalfilter
   % Coeffizenten mit Rechteckfenster
   %f=[10 100 200 300 400 500 600 700 800 900 925 950 975 1000 1025 1050 1075 1100 1150 1200 1300 1500 1800 3000 4000 6000 8000 9000 10000 12000 13000 13200 13400 13500 13600 13700 13800 13900 14000 14500 15000 ];
   %H=[2.9598 3.3562 3.3609 3.35 3.3728 3.3713 3.3658 3.3309 3.164 2.7584 2.616 2.4484 2.2862 2.0918 1.8942 1.6978 1.5 1.3015 0.9246 0.6184 0.1933 0.0275 0.0274 0.0274 0.0274 0.0274 0.0282 0.0275 0.0284 0.0286 0.0298 0.0294 0.0329 0.0698 0.3128 0.6959 1.4908 2.2196 2.9223 3.3589 3.3941 ]./length(f);
   
   % Coeffizenten mit Hanningfenster
%    f=[10     100    200    300    400    500    600    700    800    900    925    950   975    1000   1025   1050   1075   1100   1125   1150   1200   1300  1400  1500   1800   3000   4000   6000   8000   9000   10000  12000  13000  13200  13400  13500  13600  13700  13800  13900  14000  14500  15000 ];
%    H=[2.3467 2.3089 2.2528 2.1915 2.1362 2.1251 2.1187 2.0603 1.8812 1.5130 1.3936 1.286 1.1651 1.0354 0.9105 0.7928 0.6746 0.5948 0.4941 0.4108 0.2944 0.237 0.235 0.1949 0.1677 0.2322 0.2529 0.2529 0.2385 0.1993 0.2193 0.2201 0.2364 0.1928 0.2506 0.2248 0.1968 0.2786 0.6993 1.2324 1.6451 2.1264 2.2813]./length(f);
%    
   f=[10  100 200  300  400  500  600   700   800  900   925   950   975   1000  1025  1050 1075  1100  1125  1150  1200  1300  1400  1500  1800  3000  4000   6000 8000  9000 10000 12000  13000  13200  13400  13500  13600  13700  13800  13900  14000  14500  15000 ];
   H=[2.4 2.3 2.24 2.19 2.12 2.12 2.137 2.123 1.98 1.598 1.469 1.326 1.175 1.029 0.875 0.73 0.597 0.506 0.391 0.313 0.233 0.232 0.236 0.104 0.148 0.297 0.2526 0.45 0.195 0.43 0.738 0.4315 0.0713 0.248  0.254  0.204  0.1536 0.242  0.564  1.187  1.63   2.12   2.2834]./length(f);
   
   Amp_digi= 20*log10(H);
   amp_digi = Amp_digi -max(Amp_digi);
   
y_k_DFT_2 = fft(y_k_ZP);
%Amplitudengang
f_DFT = (0:N2-1)*Abtastrate/N2;
y_k_DFT_abs_2 = 20*log10(abs(y_k_DFT_2)/sum(1));
   
     figure(15); 
     clf();
     hold on
     semilogx(f,amp_digi,'r');
     plot(f_DFT,y_k_DFT_abs_2);
     LEGEND('Aufgenommener Amplitudengang','Idealer Amplitudengang',3);
     grid on;
      title('Amplitudenspektrum');
     xlabel('f/Hz');
     ylabel('A(f)[dB]');

%% bilder abspeichern
     
%        figure(15);
%        print -painters -dpdf -r600 ../Bilder/gemessener_FIR_Filter.pdf

    