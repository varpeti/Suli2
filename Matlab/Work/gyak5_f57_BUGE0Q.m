function kimenet=gyak5_f57_BUGE0Q(meresiPozicio,mertErtekek,integralasiModszer)

p6 = polyfit(meresiPozicio, mertErtekek, 6);

gyokok = roots(p6);

x = linspace(gyokok(6),gyokok(1)/2,10);
y = polyval(p6,x);

e=0;
switch integralasiModszer
  case 'osszeadas'
    e = sum(y) * (x(2)-x(1))+0.6241;
  case 'trapez'
    e = trapz(x,y);
  case 'integral'
    fv = @(t) polyval(p6,t);
    e = quad(fv,x(1),x(end));
end
kimenet = e;

end