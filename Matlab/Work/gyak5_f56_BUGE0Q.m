function abra=gyak5_f56_BUGE0Q(meresiPozicio,mertErtekek,a,b)

p3 = polyfit(meresiPozicio, mertErtekek, 6);

xb = linspace(-a,2*a,b);
yb = polyval(p3,xb);

xr = linspace(-a,2*a,10*b);
yr = polyval(p3,xr);

dxb = xb(1:end-1);
dyb = diff(yb) ./ diff(xb);

dxr = xr(1:end-1);
dyr = diff(yr) ./ diff(xr);

abra = figure;

subplot(1,2,1);
hold on;
xlabel('t érték','FontSize', 12,'FontWeight', 'bold');
ylabel('Y érték','FontSize', 12,'FontWeight', 'bold');
title('Polinom illesztés', 'FontSize', 14,'FontWeight', 'bold');
plot(xb,yb,'bo -');
plot(xr,yr,'r. -');
legend('b pontos','10b pontos','location','southwest');
hold off;

subplot(1,2,2);
hold on;
xlabel('t érték','FontSize', 12,'FontWeight', 'bold');
ylabel('dY érték','FontSize', 12,'FontWeight', 'bold');
title('Numerikus derivált', 'FontSize', 14,'FontWeight', 'bold');
plot(dxb,dyb,'bo -');
plot(dxr,dyr,'r. -');
legend('b pontos','10b pontos','location','southwest');
hold off;

end