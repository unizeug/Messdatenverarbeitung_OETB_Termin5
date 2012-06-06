%MDV Praktikum 04 FIR-Filter Vorbereitungsaufgaben

clear;

function [ y_k ] = FIRFilterung( b_k, x_k );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%filename:       FIRFilterung.m
%author:         Timo Lausen, Boris Henckell, Özgü Dogan
%organisation:   TU Berlin, Chair of Electronic Measurement 
%                and Diagnosting Technology
%project:        MDV PR SS12
%date:           06.06.2012
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%description:    Filterung mittels FIR
%input:          Filterkoeffizienten - b_k
%                Eingangsfolge - x_k    
%output:         Ausgangssignal gefiltert y_k
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

dummy = 0; %initialisiert Puffer
N = length(b_k); %bestimmt Filterordnung

%verlaengert das zu filternde Signal
x_k_neu = [zeros(1,length(b_k)),x_k,zeros(1,length(b_k))];
%initialisiert das Ausgangssignal
y_k = zeros(1,length(x_k));
%Initialisieren des Arbeitsvektors
y_k_neu = zeros(1,length(x_k));

%zaehlt durch die y-Indizes
for n=N:1:length(x_k)+N
    %zaehlt durch die Koefizienten-Indizes
    for k=0:1:N-1
        dummy=dummy+(b_k(k+1)*x_k_neu((n+1)-(k+1)));
    end
    %speichert Ergebnis ab
    y_k_neu(n+1)= dummy;
    %loescht Puffer fuer erneuten Durchlauf
    dummy = 0;
end
%kuerzt den Ergebnis-Vektor
for n=0:1:length(x_k)-1
    y_k(n+1) = y_k_neu(n+2+length(b_k));
end 

end

