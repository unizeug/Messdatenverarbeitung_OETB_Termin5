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

%%Impulsantwort bestimmen
y_k = DecimFilt(b_k, x_k, 1);

%% Fenster drüberlegen

N=length(y_k);

%erstellen eines Rechteckfensters
wn1 = ones(N,1);
%erstellen eines Hanningfensters
wn2 = hanning(N);
%erstellen eines Blackmanfensters
wn3 = blackman(N);

wn = wn1;

y_k = y_k.*wn';

%% Frequenzgang
y_k_ZP = zeros(2^20,1);
y_k_ZP(1:length(y_k)) = y_k;
y_k_DFT = FFTSHIFT(fft(y_k_ZP));

N2 = length(y_k_ZP);

%Amplitudengang
f_DFT = (-N2/2:N2/2-1)*Abtastrate/N2;
y_k_DFT_abs = 20*log10(abs(y_k_DFT)/sum(1));

%Phasengang
y_k_phase = unwrap(angle(y_k_DFT)/sum(1));

%% plotten

%Impulsantwort
figure(11); clc;clf;
hold on;
stem (x, y_k);
%plot(x,wn,'r');
hold off;
grid ();
 title('Zeitsignal');
 xlabel('t/s');
 ylabel('u/V');

%Frequenzgang
figure(12); clc;clf;
%Amplitudengang
subplot(2,1,1);
plot(f_DFT,y_k_DFT_abs);
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

% b_k_uebergeben = int16(y_k.*2^15);
% exportCoeff(b_k_uebergeben);
% figure(14)
% plot(b_k_uebergeben)

%% Amplitudengang 

% gemessener Digitalfilter
   f=[10 100 200 300 400 500 600 700 800 900 925 950 975 1000 1025 1050 1075 1100 1150 1200 1300 1500 1800 3000 4000 6000 8000 9000 10000 12000 13000 13200 13400 13500 13600 13700 13800 13900 14000 14500 15000 ];
   H=[2.9598 3.3562 3.3609 3.35 3.3728 3.3713 3.3658 3.3309 3.164 2.7584 2.616 2.4484 2.2862 2.0918 1.8942 1.6978 1.5 1.3015 0.9246 0.6184 0.1933 0.0275 0.0274 0.0274 0.0274 0.0274 0.0282 0.0275 0.0284 0.0286 0.0298 0.0294 0.0329 0.0698 0.3128 0.6959 1.4908 2.2196 2.9223 3.3589 3.3941 ]./length(f);
   Amp_digi= 20*log(H);
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