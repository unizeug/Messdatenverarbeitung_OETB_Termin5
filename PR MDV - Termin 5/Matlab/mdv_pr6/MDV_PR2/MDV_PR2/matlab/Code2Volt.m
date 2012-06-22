function [ voltage ] = Code2Volt (Code)
% funct i on [ voltage ] = Code2Volt (Code)
%
% filename : Bin2Volt .m
% author : Özgü Dogan, Timo Lausen, Boris Henckell
% organisation : TU Berlin %project :MDVPR
% date : 04.05.2012 %
% description : rechnet die vom ADU ausgegebenen Zahlencodes
% in Spannungen (Einheit : V) um
% input : Code : vom ADU ausgegebene Zahlencodes
% output : [ volatge ] : berechnete Spannungen [V]
Umax=7;
Umin=-7;
ADUbit=10;
Ulsb= (Umax-Umin)/(2^(ADUbit)-1);
Volt = zeros(1,length(Code));
for i = 1:length(Code)
    Volt(i) = Code(i)*Ulsb;
end
voltage = Volt;
return;
