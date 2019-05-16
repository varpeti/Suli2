function [struktura, abra]=gyak8_f82_BUGE0Q(db)

t = linspace(0, (2*pi), db);
struktura.y = t;
struktura.nev = {'Sin(3t)','Cos(5t)','Sin(3t)*Cos(5t)'};
struktura.x = {sin(3*t),cos(5*t),sin(3*t).*cos(5*t)};

abra = figure;
for i=1:3
  subplot(3,1,i);
  plot(struktura.y,struktura.x{1,i},'k');
  title(struktura.nev{1,i});
  xlabel('t');
  xlim([t(1) t(end)]);
end
end