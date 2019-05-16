function kimenetiSzoveg=gyak5_f54_BUGE0Q(a,b)
x = 0:b:a;
y = sin(x);

e1 = sum(y) * (x(2)-x(1));

e2 = trapz(x,y);

fv = @(t) sin(t);
e3 = quad(fv,x(1),x(end));

kimenetiSzoveg = sprintf('Integrálási eredmények:\n\tÖsszeadással: %1.3f\n\tTrapézszabállyal: %1.3f\n\tFüggvénnyel: %1.3f',e1,e2,e3);
end