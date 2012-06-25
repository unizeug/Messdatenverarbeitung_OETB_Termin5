% Praxisaufgabe 6
clear;
%% laden der Daten
recht_3kHz = load('6_rechteck_3kHz_120');
recht_15kHz = load('6_rechteck_15kHz');
recht_15kHz_decim_3kHz = load('6_rechteck_15kHz_decim3kHz');

recht_3kHz = Code2Volt(recht_3kHz.a);
recht_15kHz = Code2Volt(recht_15kHz.rechteck_15kHz);
recht_15kHz_decim_3kHz = Code2Volt(recht_15kHz_decim_3kHz.rechteck_15kHz_decim3kHz);

wn1 = ones(1,length(recht_3kHz));
wn2 = ones(1,length(recht_15kHz));
fs = 15000;

%% erstellen des Spektrum und plotten
Spektrum(recht_3kHz, wn1, fs/5, 0,'b', 1);
Spektrum(recht_15kHz, wn2, fs, 0,'b', 2);
Spektrum(recht_15kHz_decim_3kHz, wn1, fs/5, 0,'b', 3);

figure(1);
SUPTITLE(['\bf Rechtecksignal mit 3kHz abgetastet', 10]);
figure(2);
SUPTITLE(['\bf Rechtecksignal mit 15kHz abgetastet', 10]);
figure(3);
SUPTITLE(['\bf Rechtecksignal digital gefiltert und dezimiert', 10]);