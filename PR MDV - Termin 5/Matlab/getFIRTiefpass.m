function [ Filterkoeffizienten ] = getFIRTiefpass( Grenzfrequenz, Abtastperiode, Filterordnung )

tau = ((Filterordnung-1)/2)*(Abtastperiode);
k = 0:1:(Filterordnung-1);
%Impulsantwort_k = (sin(2*pi*Grenzfrequenz*(k.*(Abtastperiode)-tau)))./(pi*(k.*(Abtastperiode)-tau));
Impulsantwort_k = 2*Grenzfrequenz*sinc(2*Grenzfrequenz*(k.*(Abtastperiode)-tau));
Filterkoeffizienten = Impulsantwort_k/(sum(Impulsantwort_k));

end