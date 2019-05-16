function abra=gyak4_f42_BUGE0Q(archivum)
load(archivum);

a1 = kep*A1;
a2 = kep*A2;
a3 = kep*A3;
a4 = kep*A4;

%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után

subplot(2,2,1);
hold on;
title('house*A1', 'FontSize', 14,'FontWeight', 'bold');
plot(a1(:,1),a1(:,2));
hold off;
%% X nyújt

subplot(2,2,2);
hold on;
title('house*A2', 'FontSize', 14,'FontWeight', 'bold');
plot(a2(:,1),a2(:,2));
hold off;
%% Y nyújt

subplot(2,2,3);
hold on;
title('house*A3', 'FontSize', 14,'FontWeight', 'bold');
plot(a3(:,1),a3(:,2));
hold off;
%% +90

subplot(2,2,4);
hold on;
title('house*A4', 'FontSize', 14,'FontWeight', 'bold');
plot(a4(:,1),a4(:,2));
hold off;
%% +180
end