function [x,y,z]=gyak4_f43_BUGE0Q(a,b,c,d,e,f,g)
matrix = [a b 0;c a b;0 b a];
vektor = [e;(f-d);(g+d)];
v2 = matrix\vektor;
x=v2(1);
y=v2(2);
z=v2(3);
end