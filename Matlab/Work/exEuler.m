function [t, y] = exEuler(F, tspan, y0, g)
t = linspace(tspan(1),tspan(2),g);
h = t(2)-t(1);
y = zeros(1,g);
y(1)= y0;
for i = 2:g;
  m = F(t(i),y(i-1));
  y(i)= y(i-1)+m*h;
end
end