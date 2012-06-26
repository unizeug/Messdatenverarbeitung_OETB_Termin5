% Praxis 51
%% laden der Daten
close all;
clc;

daten = load('5_rechteck_110Hz');

datenu = Code2Volt(daten.rechteck_110Hz);



wn = ones(1,length(datenu));
fs = 15000;

%% erstellen des Spektrum und plotten
Spektrum(datenu, wn, fs, 1,'b',-1000,1000,-70,10, 1);


%% dezimierung der Messwerte
y_k_dezi = zeros(1,floor(length(datenu)/5));
wn2 = ones(1,length(y_k_dezi));
i=1;
n = 1;

while i <= length(datenu)
    y_k_dezi(n) = datenu(i);
    n= n+1;
    i = i + 5;
end

Spektrum(y_k_dezi, wn2, fs/5,1,'b',-1000,1000,-70,10,2);

%Spektrum(datenu, wn, fs, 0,'r',-1000,1000,-70,10, 3);
%Spektrum(y_k_dezi, wn, fs/5,0,'b',-1000,1000,-70,10,3);

%% filterung der Daten
Grenzfrequenz = 1000;
Abtastperiode = 1/fs;
Filterordnung = 85;
b_k = getFIRTiefpass( Grenzfrequenz, Abtastperiode, Filterordnung );
wn = hanning(length(b_k));
b_k = b_k.*wn';

y_k_gefiltert_undezi = FIRFilterung( b_k, datenu );

y_k_gefiltert_dezi = zeros(1,floor(length(y_k_gefiltert_undezi)/5));

i=1;
n = 1;

while i <= length(y_k_gefiltert_undezi)
    y_k_gefiltert_dezi(n) = y_k_gefiltert_undezi(i);
    n= n+1;
    i = i + 5;
end
y_k_gefiltert_dezi_gefenstert = y_k_gefiltert_dezi(14:68);
% figure(88);
% plot(y_k_gefiltert_dezi_gefenstert);

wn3 = ones(1,length(y_k_gefiltert_dezi_gefenstert));

Spektrum(y_k_gefiltert_dezi_gefenstert, wn3, fs/5,1,'b',-1000,1000,-70,10,4);

%% Filtern und nachabtasten 

y_k_alleszusammen=DecimFilt(b_k, datenu, 5);

wn3 = ones(1,length(y_k_alleszusammen));

Spektrum(y_k_alleszusammen, wn3, fs/5,1,'b',-1000,1000,-70,10,5);

%% testbereich
% testvektor = zeros(length(datenu),1);
% 
% i=1;
% n = 1;
% 
% while i <= length(datenu)
%     testvektor(i) = 2;
%     n= n+1;
%     i = i + 5;
% end
% 
% figure(22);
% hold on
% plot(datenu,'c');
% plot(y_k_gefiltert_undezi);
% stem(testvektor,'r');
% hold off
% legend('datenu','y k gefiltert undezi','Abtaststellen');
% 
% figure(23);
% hold on
% plot(y_k_gefiltert_dezi);
% plot(y_k_alleszusammen,'r');
% hold off


%% Bilder abspeichern
%   % mit Axis aufgenommen
%        figure(1);
%        print -painters -dpdf -r600 ../Bilder/rechteck_100Hz_15kHz_frequenzbegrenzung.pdf
%        figure(2);
%        print -painters -dpdf -r600 ../Bilder/rechteck_100Hz_15kHz_3kHz_nachabgetastet_frequenzbegrenzung.pdf
    % ohne Axis aufgenommen
%        figure(1);
%        print -painters -dpdf -r600 ../Bilder/rechteck_100Hz_15kHz_keine_frequenzbegrenzung.pdf
%        figure(2);
%        print -painters -dpdf -r600
%        ../Bilder/rechteck_100Hz_15kHz_3kHz_nachabgetastet_keine_frequenzbegrenzung.pdf

%         figure(4);
%         print -painters -dpdf -r600 ../Bilder/rechteck_100Hz_gefiltert_15kHz_3kHz_nachabgetastet.pdf
%         figure(5);
%         print -painters -dpdf -r600 ../Bilder/rechteck_100Hz_decimFilt_15kHz_3kHz_nachabgetastet.pdf

