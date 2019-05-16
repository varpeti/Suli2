%%BUGE0Q
function [] = zh2_feladat2_varpe8()
x = linspace(-5,5,100);
y = linspace(-5,5,100);
z = sin(x) + cos(y); 

abra = figure;
surf(x,y,z);

end