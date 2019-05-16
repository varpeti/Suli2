function [tVektor, yMatrix, abra, A]=gyak8_f83_BUGE0Q(bemenetiFajl)
	f = fopen(bemenetiFajl);
	  A = fscanf(f, '%f', 4);
  fclose(f);
  
	F = @(t,y) [5*log(y(2))*y(1); (1-1.2*y(1))*y(2)];
	[tVektor,yMatrix] = ode45(F,[A(1) A(2)],[A(3),A(4)]);
  
	f = fopen('gyak8_f83_kimenet.bin','w');
	  fwrite(f, [tVektor' yMatrix(:,1)' yMatrix(:,2)'],'double');
	fclose(f);
  
	abra = figure;
	subplot(2,1,1);
	  plot(tVektor,yMatrix(:,1), '-.m',tVektor, yMatrix(:,2),':g');
    legend('y1','y2');
    xlabel('ido');
	  ylabel('ertek');
	  title('Idobeli lefutasok');
	subplot(2,1,2);
	  plot(yMatrix(:,1),yMatrix(:,2),'r');
    xlabel('y1');
	  ylabel('y2');
	  title('Fazisportre - allapotter');
end