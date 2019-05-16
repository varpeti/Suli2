function [c,d,e,f,g,h,k,i,m,n,o,p,q,r,s]=gyak2_BUGE0Q(a,b,x)
  c = a<x & x<b;
  d = x(c);
  e = find(a<x & x<b);
  f = mean(x);
  g = f<=x & x<a;
  h = x(g);
  k = a<x & x<b;
  i = x(k);
  [m n] = max(i);
  o = length(i);
  t = linspace(eps,pi,100);
  fv = sin(t)./(4.7*t+3)+0.1*cos(t.^2);
  [q id] = max(fv);
  p = t(id);
  
  r = figure;
  t = 5:1:10;
  plot(t,t./sin(t),'o-- r');
  hold on;
  xlabel('t','FontSize', 14,...
 'FontWeight', 'bold');
  ylabel('y ertek', 'FontSize', 14,...
 'FontWeight', 'bold');
  title('abracim', 'FontSize', 14,...
 'FontWeight', 'bold');
 hold off;
  
  
  s = figure;
  t = 2:1:14;
  subplot(2,2,1);
  hold on;
  xlabel('t','FontSize', 14,...
 'FontWeight', 'bold');
  ylabel('y ertek', 'FontSize', 14,...
 'FontWeight', 'bold');
  title('balfelso', 'FontSize', 14,...
 'FontWeight', 'bold');
  plot(t,0.5-0.2*exp(1).^(log(t).*cos(t)),'s--');
  hold off;
  subplot(2,2,3);
  hold on;
  xlabel('t','FontSize', 14,...
 'FontWeight', 'bold');
  ylabel('y ertek','FontSize', 14,...
 'FontWeight', 'bold');
  title('balalso','FontSize', 14,...
 'FontWeight', 'bold');
  plot(t,pi.^(0.1*t-3).*sin(t),'^k-');
  hold off;
  subplot(2,2,[2, 4]);
  hold on;
  xlabel('t','FontSize', 14,...
 'FontWeight', 'bold');
  ylabel('y ertek','FontSize', 14,...
 'FontWeight', 'bold');
  title('jobboldal','FontSize', 14,...
 'FontWeight', 'bold');
  plot(t,cos(t)./(exp(1).^sin(t)),'*-r');
  grid on;
  plot(t,0.*t,'k--');
  hold off
end