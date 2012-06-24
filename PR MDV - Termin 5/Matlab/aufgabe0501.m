%MDV Pr05 Praktischer Teil
%Aufgabe 1

rechteck_110Hz = load('x');
u = Code2Volt(rechteck_110Hz.x);
N = length(u);

y_DFT = abs(fftshift(fft(u)));

%Betragsspektrum
ampl_rechteck = 20*LOG10(abs(y_DFT)/N);
% ampl_rechteck = y_DFT/N;

%Abtastfrequenz
f_T = 15000;

figure(1)
%Frequenzachse
f_DFT = f_T/(N-1)*((-N/2+0.5):(N/2-0.5));
%%f_DFT = f_DFT(178:1:233);
plot(f_DFT, ampl_rechteck)
% AXIS(-1000 1000 -1 2);
%------------------------------Aufgabe2------------------------------------

u_kurz = zeros(1,(length(u)/5));
for k = 1:1:length(u_kurz)
    u_kurz(k) = u(k*5);
end

N = length(u_kurz);

y_DFT = abs(fftshift(fft(u_kurz)));

%Betragsspektrum
%ampl_rechteck = 20*LOG10(abs(y_DFT)/N);
ampl_rechteck = 20*LOG10(y_DFT/N);

%Abtastfrequenz nur noch ein fünftel
f_T = 15000/5;

figure(2)
%Frequenzachse
f_DFT = f_T/(N-1)*((-N/2+0.5):(N/2-0.5));
%%f_DFT = f_DFT(178:1:233);
% plot(f_DFT(178:1:233), ampl_rechteck(178:1:233))
plot(f_DFT,ampl_rechteck)

