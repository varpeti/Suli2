function [B,C,d,e,f]=gyak3_f31_BUGE0Q(A)
% A bemenetünk egy véletlenszerű értékeket tartalmazó 5x2x3-as mátrix.
B = squeeze(A(:,1,:));
C = squeeze(A(:,2,:));

d = sum(max(B,[],2));
e = mean(min(C));

f = sprintf('B-ben a sorok maximumának összege: %3.2f, míg C-ben az oszlopok minimumának átlaga: %3.2f',d,e);
end