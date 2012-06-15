function exportCoeff(coeff)
% function exportCoeff(coeff)
% ---------------------------------------------------
% filename: exportCoeff
% author: Jürgen Funck
% organisation: TU Berlin
% project: MDV PR
% date: 2010-05-25
% ---------------------------------------------------
% description: export Filter coefficients to a c-header file 
%      named 'filter_coeff.h'
% input: 
%   coeff:   filter coefficients
% ---------------------------------------------------
    % string constants
    preface = '#define FILTER_COEFF';

    % open file
    fid = fopen('filter_coeff.h','w');
    
    % write coefficients to file
    fprintf(fid,'%s %i',preface,coeff(1));
    fprintf(fid,',%i',coeff(2:end));
    
    % close file
    fclose(fid);
end