function y_k = DecimFilt(b_k, x_k, fr)
% function yk=DecimFilt(bk, xk, fr)
% ?????????????????????????????????????
% filename: DecimFilt.m
% author: �zg� Dogan, Timo Lausen, Boris Henckell
% organisation : TU Berlin ,
%
% project:  MDF PR
% date:     2012.06.14
% ?????????????????????????????????????
% description : Filterung mittels FIR Veranstaltung PR MDV SS12
%
% input :   Filterkoeffizienten ? bk 
%           Eingangsfolge ? xk 
%           Nachabtastfaktor ? fr
%           fr = f_alt/f_neu (ganzzahlig)
%
% output : Ausgangssignal ? yk gefiltert und dezimiert
%
% ?????????????????????????????????????


%y_k_undezi  = FIRFilterung( b_k, x_k); 

 
 %y_k_dezi = zeros(1,floor(length(y_k_undezi)/fr));
 
 %i=1;
 %n = 1;
 
 %while i <= length(y_k_undezi)
  %   y_k_dezi(n) = y_k_undezi(i);
   %  n= n+1;
    % i = i + fr;
% end
 
 %yk = y_k_dezi;
 
dummy = 0; %initialisiert Puffer
N = length(b_k); %bestimmt Filterordnung

%verlaengert das zu filternde Signal
x_k_neu = [zeros(1,length(b_k)),x_k,zeros(1,length(b_k))];
%initialisiert das Ausgangssignal
y_k = zeros(1,length(x_k));
%Initialisieren des Arbeitsvektors
y_k_neu = zeros(1,length(x_k));

%zaehlt durch die y-Indizes
for n=N:fr:length(x_k)+N
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

