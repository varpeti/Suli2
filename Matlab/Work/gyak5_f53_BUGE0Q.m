function abra=gyak5_f53_BUGE0Q(a,b,c,d,e,t0)

p = [a b c d];

x = -e:0.001:e;
y = polyval(p,x);

y0 = polyval(p,t0)

x_t = [t0-1e-9 t0+1e-9]; 
y_t = polyval(p,x_t);

d = diff(y_t) ./ diff(x_t);

abra = figure;
hold on;
xlabel('x','FontSize', 14,...
 'FontWeight', 'bold');
ylabel('y', 'FontSize', 14,...
 'FontWeight', 'bold');
title('Érintő adott pontban', 'FontSize', 14,...
 'FontWeight', 'bold');
plot(x,y);
plot(t0,y0,'ko');
plot([t0-1 t0+1], [y0-d y0+d],'r');
legend('fv. értékek','deriválási hely','érintő egyenes','location','northwest');
hold off;

end