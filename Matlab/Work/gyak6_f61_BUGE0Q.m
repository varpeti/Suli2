function abra=gyak6_f61_BUGE0Q(y,t)
% Els�rend�, k�tv�ltoz�s differencialegynelet megold�sa,
% Lotka-Volterra ragadoz�-zs�km�ny modell

mu = [200 300];

F = @(t,y) [(1-y(2)/mu(2))*y(1); -(1-y(1)/mu(1))*y(2)] 

[px,py] = ode45(F,t,y);
%% Ide ker�lj�n az �bra kirajzoltat�sa
abra = figure; % ez ut�n
subplot(2,1,1);
xlabel('t','FontSize', 12,'FontWeight', 'bold');
ylabel('egyedszám','FontSize', 12,'FontWeight', 'bold');
title('Predator-Prey Modell', 'FontSize', 14,'FontWeight', 'bold');
hold on;
plot(px,py(:,1),'g','LineWidth',2);
plot(px,py(:,2),'b','LineWidth',2);
legend('zsákmány','ragadozó');
hold off;
subplot(2,1,2);
xlabel('zsákmányok száma','FontSize', 12,'FontWeight', 'bold');
ylabel('ragadozók száma','FontSize', 12,'FontWeight', 'bold');
title('Fázisgörbe', 'FontSize', 14,'FontWeight', 'bold');
hold on;
plot(py(:,1),py(:,2),'b');
hold off;
end