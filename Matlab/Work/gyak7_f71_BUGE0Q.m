function abra=gyak7_f71(x_min,x_max,y_min,y_max)

[x,y] = meshgrid(x_min:0.25:x_max, y_min:0.25:y_max);
z = sin(x).*exp(-sin(x)-y.^2);

%% Ábrázolás

abra = figure;
surf(x,y,z);
xlim([x_min x_max]);
ylim([y_min y_max]);
title('Felület');
xlabel('X értékek');
ylabel('Y értékek');
zlabel('Z értékek');
colorbar;
end