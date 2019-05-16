function abra=gyak5_f51_BUGE0Q(a,b,c,d,e,f)

x1=e:1:f;
x2=e:0.001:f;

p = [a b c d]
o = roots(p);
y1= polyval(p,x1);
y2= polyval(p,x2);

%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után

hold on;
xlabel('x érték','FontSize', 14,...
 'FontWeight', 'bold');
ylabel('y értek', 'FontSize', 14,...
 'FontWeight', 'bold');
title('Polinom', 'FontSize', 14,...
 'FontWeight', 'bold');
plot(x1,y1,'r');
plot(x2,y2,'b');
plot(o,zeros(size(o)),'ko');
plot([e,f],[0,0],'k--');
legend('1-es lépésköz','0.001-es lépésköz','gyökök','location','southeast');
hold off;

end