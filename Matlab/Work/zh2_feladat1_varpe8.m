%%BUGE0Q
function [] = zh2_feladat1_varpe8()
  I=1; %konstansok
  a=0.7;
  b = 0.8;
  tau = 12.5;
  
  %y(1)=v %y(2)=w;
	F = @(t,y) [y(1)-(y(1)^3)/3-y(2)+I; (y(1)+a-b*y(2))/tau];
  
  ido = [0:0.1:200]; %idö | a matlabban meglehet így adni: [0 200];
  kezd = [1 0.1]; % kezdeti értékek
  
  [T Y] = ode45(F,ido,kezd);
  
  abra = figure;
  subplot(3,1,1);
  plot(T,Y(:,1));
  subplot(3,1,2);
  plot(T,Y(:,2));
  subplot(3,1,3);
  plot(Y(:,1),Y(:,2));
  
  
end