function [] = gyak02()
  %konstansok
  U = 1;
  
  %Egyenletrendszer
  %x'=y
  %y'=U(1-x^2)*y-x
  
  %x=a(1)
  %y=a(2)
  
  f = @(t,a) [...
    a(2);...
    U*(1-a(1)^2)*a(2)-a(1);...
  ];
  
  %kezdeti értékek
  ido = 0:0.01:20;
  kezdeti = [0.1 0.1]
  
  %megoldás
  [t, a] = ode45(f,ido,kezdeti);
  
  abra = figure;
  hold on;
  plot(a(:,1),a(:,2));
  [x y] = meshgrid(-3:0.3:3);
  quiver(x,y,y,U*(1-x.^2).*y-x);
  hold off;
  
end