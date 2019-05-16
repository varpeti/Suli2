function [cellaTomb, abra]=gyak8_f81_BUGE0Q(db)
t = linspace(0, (2*pi), db);
cellaTomb = {t,{'Sin(3t)','Cos(5t)','Sin(3t)*Cos(5t)'},{sin(3*t),cos(5*t),sin(3*t).*cos(5*t)}};

abra = figure;
for i=1:3
  subplot(3,1,i);
  plot(cellaTomb{1,1},cellaTomb{1,3}{1,i},'k');
  title(cellaTomb{1,2}{1,i});
  xlabel('t');
  xlim([t(1) t(end)]);
end
end