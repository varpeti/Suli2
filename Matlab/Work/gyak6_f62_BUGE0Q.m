function abra=gyak6_f62_(y,t)

F = @(t,y) [1.2*y(1)+4.1*y(2)-1.7*y(3); -8*y(1)-1.4*y(2)+2.1*y(3); 2.1*y(1)-7.2*y(2)+1.3*y(3)]

[px py] = ode45(F,t,y);

felt = py(:,1) > py(:,2) & py(:,1) < py(:,3);
my = py(felt,1);
mx = px(felt);

%% Ide ker�lj�n az �bra kirajzoltat�sa
abra = figure; % ez ut�n
xlabel('idő','FontSize', 12,'FontWeight', 'bold');
ylabel('koncentráció','FontSize', 12,'FontWeight', 'bold');
hold on;
plot(px,py(:,1),'b','LineWidth',2);
plot(px,py(:,2),'k','LineWidth',2);
plot(px,py(:,3),'r','LineWidth',2);
legend('A','B','C','Location','southwest');
plot(mx,my,'s g','MarkerFaceColor','g');
hold off;
end