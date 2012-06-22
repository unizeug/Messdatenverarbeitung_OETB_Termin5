% Praxis 51
%% laden der Daten
daten = load('5_rechteck_110Hz');

datenu = Code2Volt(daten.rechteck_110Hz);



wn = ones(1,length(datenu));
fs = 15000;

%% erstellen des Spektrum und plotten
Spektrum(datenu, wn, fs, 0,'b', 1);


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

Spektrum(y_k_dezi, wn2, fs/5,0,'b',2);

%Spektrum(datenu, wn, fs, 0,'r', 3);
%Spektrum(y_k_dezi, wn, fs/5,0,'b',3);

%% filterung der Daten
Grenzfrequenz = 1000;
Abtastperiode = 1/fs;
Filterordnung = 85;
b_k = getFIRTiefpass( Grenzfrequenz, Abtastperiode, Filterordnung );
y_k_gefiltert_undezi = FIRFilterung( b_k, datenu );


y_k_gefiltert_dezi = zeros(1,floor(length(datenu)/5));

i=1;
n = 1;

while i <= length(datenu)
    y_k_gefiltert_dezi(n) = y_k_gefiltert_undezi(i);
    n= n+1;
    i = i + 5;
end

Spektrum(y_k_gefiltert_dezi, wn2, fs/5,0,'b',4);

%% Filtern und nachabtasten 

y_k_alleszusammen=DecimFilt(b_k, datenu, 5);

Spektrum(y_k_alleszusammen, wn2, fs/5,0,'b',5);
