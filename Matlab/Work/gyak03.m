function [] = gyak03()
  %konstansok
  U = 1;
  
  %difegy
  % x''-U(1-x^2)*x'+x
  %
  % x'=y
  % y'=U(1-x^2)*y-x
  
  % x=p(1)
  % y=p(2)
  
  f = @(t,p) [...
    p(2);...
    U*(1-p(1)^2)*p(2)-p(1);...
    ];
  
  %kezdeti,idő
  ido = [0 20];
  kezdeti = [0.1 0.1];
  
  %megoldás
  [t a] = ode45(f,ido,kezdeti);
  
  %rajz
  hold on;
  plot(a(:,1),a(:,2));
  
  %vektormező
  
  [u v] = meshgrid(-3:0.2:3);
  uu = v;
  vv = U*(1-u.^2).*v-u;
  quiver(u,v,uu,vv,'r');
  hold off;
  
  
end