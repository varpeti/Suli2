function abra=gyak5_f55_BUGE0Q(meresiPozicio,mertErtekek,a,b)

 p2 = polyfit(meresiPozicio, mertErtekek, 2);
 
 x2 = meresiPozicio;
 y2 = polyval(p2,x2);
 
 x3 = linspace(meresiPozicio(1),meresiPozicio(end),5);
 y3 = polyval(p2,x3);
 
 gyokok = roots(p2);
 gyy = zeros(size(gyokok));
 
 x5 = a:b:2*a;
 y5 = polyval(p2,x5);
 
 p6 = polyfit(meresiPozicio, mertErtekek, 6);
 
 x6 = meresiPozicio;
 y6 = polyval(p6,x6);
 
 x7 = x5;
 y7 = polyval(p6,x7);

abra = figure;

hold on;
xlabel('X érték','FontSize', 12,'FontWeight', 'bold');
ylabel('Y érték','FontSize', 12,'FontWeight', 'bold');
title('Polinom illesztés', 'FontSize', 14,'FontWeight', 'bold');
plot(meresiPozicio,mertErtekek,'k.');
plot(x2,y2,'r');
plot(x3,y3,'b--');
plot(gyokok,gyy,'x','MarkerSize',20,'MarkerEdgeColor','k');
plot(x5,y5,'g');
plot(x6,y6,'m:');
plot(x7,y7,'c--');
plot([meresiPozicio(1) a*2],[0 0],'k--');
legend('Zajos adatok','2. fokú illesztés','2. fokú illesztés kevés pontal','2. fokú gyökök','2. fokú predikció','6. fokú illesztés','6. fokú predikció','location','northwest');
hold off;
end