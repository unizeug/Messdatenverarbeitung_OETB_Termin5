%MDV Praktikum 5&6, Spektrum bilden:

function [BetragXf, PhaseXf] = Spektrum(xt, wn, fs, LogFlag,farbe,xmin,xmax,ymin,ymax, fig)

% function [BetragXf, PhaseXf] = Spektrum(xt, wn, fs, LogFlag);
% ??????????????????????????????????????????????????????
% filename:           Spektrum.m
% author:             Özgü Dogan, Timo Lausen, Boris Henckell
% organisation:       TU Berlin 
% project:            MDVPR
% date:               21.05.2012
% 
% ??????????????????????????????????????????????????????
% description:        Bestimmt und plottet das Betrags- und Phasenspektrum 
%                     eines Signals xt
% input:              xt : Signal im Zeitbereich
% output:             BetragXf = Betragsspektrum des Signals xt
%                     PhaseXf = Phasenspektrum des Signals xt

% xt = Signal im Zeitbereich
% wn = Fensterfolge
% fs = Abtastfrequenz
% LogFlag = für Flag=1 ist y-Achse log. in dB dargestellt, sonst 0

%Multiplikation des Zeitsignals und des Fensters
ergebnis1 = xt.*wn;             

%erstellen der DFT des Ergebnisses
ergebnis2 = fft(ergebnis1);     
ergebnis2 = fftshift(ergebnis2);
N = length(xt);
N2=sum(wn);

%Betragsspektrum
BetragXf = abs(ergebnis2)/N2;
%Phasenspektrum
PhaseXf = unwrap(angle(ergebnis2)/N2);

%Zeitachse
t = 0 :1/fs : (N-1)/fs;
length(t);

%Frequenzachse
%f_DFT = fs*2*(0:(N-1))/(N-1);
f_DFT = (-N/2:N/2-1)*fs/N;
%ceil bzw floor als Lösung
%neues Fenster zur Darstellung
figure(fig);
%Darstellung des Zeitsignals
subplot(3,1,1);
hold on
plot(t,ergebnis1,farbe);
%plot(t,wn,'r');
hold off
%stem(t,xt);
%AXIS([0 0.025 -3 3]) % Vorbereintungsaufgabe 4.3
 title('Zeitsignal');
 xlabel('t/s');
 ylabel('u/V');
%Darstellung des Amplitudenspektrums
subplot(3,1,2);
if LogFlag == 1
    BetragXflog = 20*log10(BetragXf);
    plot(f_DFT, BetragXflog,farbe);
else
    %plot(f_DFT, BetragXf,'-');
    stem(f_DFT,BetragXf,farbe);
end;
AXIS([ xmin xmax ymin ymax]); % allgemeiner aufruf
%AXIS([-1000 1000 -70 10])%für die Praxisaufgabe  5.x
%AXIS([-1000 1000 0 1.5])%für die Praxisaufgabe  6.x
%AXIS([-1000 1000 0 1.5])%für die Vorbereitungsaufgabe 2
%Axis([-0.5 0.5 10^(-15) 10^(-5)])%für die Vorbereitungsaufgabe 3
%ylim ([-30 5])
 title('Amplitudenspektrum');
 xlabel('f/Hz');
 ylabel('A(f)[dB]');    
%Darstellung des Phasenspektrums
subplot(3,1,3);
plot(f_DFT, PhaseXf,farbe);
%AXIS([ xmin xmax min(PhaseXf)*1.2 max(PhaseXf)*1.2]); % allgemeiner aufruf
%AXIS([-1000 1000 min(PhaseXf)*1.2 max(PhaseXf)*1.2])%Für die Praxisaufgabe 5.x
%AXIS([-1000 1000 -0.015 0.015])%Für die Vorbereitungsaufgabe 2
%Axis([-0.5 0.5 -4*10^(-6) 4*10^(-6)])%für die Vorbereitungsaufgabe 3
title('Phasenspektrum');
 xlabel('f/Hz');
 ylabel('phi(f)');


