function [] = gyak01()

  %konstansok:
  B = 8/3
  R = 28
  O = 10
  
  %Egyenletrendszer
  %x=a(1)
  %y=a(2)
  %z=a(3)
  f = @(t,a) [...
    O*(a(2)-a(1));...
    a(1)*(R-a(3))-a(2);...
    a(1)*a(2)-B*a(3);...
    ];
    
  %kezdeti ertekek:
  ido = 0:0.05:25;
  kezdeti = [1 1 1];
  
  %megoldás
  [t y] = ode45(f,ido,kezdeti);
  
  %rajz
  abra = figure;
  subplot(2,2,1);
  hold on;
  plot(t,y(:,1),'r');
  plot(t,y(:,2),'g');
  plot(t,y(:,3),'b');
  hold off;
  subplot(2,2,2);
  plot3(y(:,1),y(:,2),y(:,3));
  
  [x y] = meshgrid(-5:0.5:5);
  z= sin(x).*cos(y) + x/10 - y/10;
  
  subplot(2,2,3);
  surfc(x,y,z);
  
  l = (0<z & z<1);
  n = (l==0); %negálás
  % 0 vektor + 0.5 ha l vagy z ha n 
  z = (z.*0+0.5*l+z.*n);
  
  subplot(2,2,4);
  meshc(x,y,z);
  
end