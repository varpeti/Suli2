function abra=gyak7_f72(x_min,x_max,y_min,y_max,Az,El)

[x, y] = meshgrid(x_min:0.02:x_max, y_min:0.02:y_max);
r = sqrt(x.^2+y.^2);
z = 0.5*sin(r).*cos(r);

%% Ábrázolás
abra = figure;
surf(x,y,z);
view(Az,El);
xlim([x_min x_max]);
ylim([y_min y_max]);
title('0.5sin(r)cos(r)');
xlabel('x értékek');
ylabel('y értékek');
zlabel('z értékek');
hold on;
clabel(contour(x,y,z));
colorbar;

end