function abra=gyak5_f52_BUGE0Q(a,b,c,d)

x1 = a:c:b;
x2 = a:d:b;

s1 = sin(x1);
s2 = sin(x2);

abra = figure;
subplot(1,2,1);
xlabel('t','FontSize', 14,...
 'FontWeight', 'bold');
ylabel('fv értek', 'FontSize', 14,...
 'FontWeight', 'bold');
title('szinusz különböző felbontásokkal', 'FontSize', 14,...
 'FontWeight', 'bold');
hold on;
plot(x1,s1,'b-o');
plot(x2,s2,'r.-');
legend('c felbontás','d felbontás');
hold off;

subplot(1,2,2);
xlabel('t','FontSize', 14,...
 'FontWeight', 'bold');
ylabel('dy / dt', 'FontSize', 14,...
 'FontWeight', 'bold');
title('numerikus deriváltak', 'FontSize', 14,...
 'FontWeight', 'bold');
hold on;

d1 = diff(s1) ./ diff(x1);
d2 = diff(s2) ./ diff(x2);

plot(x1(1:end-1),d1,'b-o');
plot(x2(1:end-1),d2,'r.-');
legend('c felbontás','d felbontás');
hold off;

end