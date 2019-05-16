function [abrak]=gyak9_f94_BUGE0Q()
	
	a=1; b=2; c=-2; d=-2; e=-3; f=1.5;
	x1=e:1:f;
	x2=e:0.001:f;
	
	p = [a b c d]
	o = roots(p);
	y1= polyval(p,x1);
	y2= polyval(p,x2);
	
	abrak(1) = figure;
	
	hold on;
	xlabel('x érték','FontSize', 14,...
 	'FontWeight', 'bold');
	ylabel('y értek', 'FontSize', 14,...
 	'FontWeight', 'bold');
	title('Polinom', 'FontSize', 14,...
 	'FontWeight', 'bold');
	plot(x1,y1,'r');
	plot(x2,y2,'b');
	plot(o,zeros(size(o)),'ko');
	plot([e,f],[0,0],'k--');
	legend('1-es lépésköz','0.001-es lépésköz','gyökök','location','southeast');
	hold off;

	print(abrak(1), '-depsc2', 'f011');
	print(abrak(1), '-dpng', 'f012');
	
	a=0; b=4*pi; c=1; d=0.05;
	x1 = a:c:b;
	x2 = a:d:b;
	
	s1 = sin(x1);
	s2 = sin(x2);
	
	abrak(2) = figure;
	subplot(1,2,1);
	xlabel('t','FontSize', 14,...
 	'FontWeight', 'bold');
	ylabel('fv értek', 'FontSize', 14,...
 	'FontWeight', 'bold');
	title('szinusz különböző felbontásokkal', 'FontSize', 14,...
 	'FontWeight', 'bold');
	hold on;
	plot(x1,s1,'b-o');
	plot(x2,s2,'r.-');
	legend('c felbontás','d felbontás');
	hold off;
	
	subplot(1,2,2);
	xlabel('t','FontSize', 14,...
 	'FontWeight', 'bold');
	ylabel('dy / dt', 'FontSize', 14,...
 	'FontWeight', 'bold');
	title('numerikus deriváltak', 'FontSize', 14,...
 	'FontWeight', 'bold');
	hold on;
	
	d1 = diff(s1) ./ diff(x1);
	d2 = diff(s2) ./ diff(x2);
	
	plot(x1(1:end-1),d1,'b-o');
	plot(x2(1:end-1),d2,'r.-');
	legend('c felbontás','d felbontás');
	hold off;

	print(abrak(2), '-depsc2', 'f021');
	print(abrak(2), '-dpng', 'f022');
	

	a=1.5; b=2; c=0.5; d=-2; e=3; t0=1.5;
	p = [a b c d];

	x = -e:0.001:e;
	y = polyval(p,x);
	
	y0 = polyval(p,t0)
	
	x_t = [t0-1e-9 t0+1e-9]; 
	y_t = polyval(p,x_t);
	
	d = diff(y_t) ./ diff(x_t);
	
	abrak(3) = figure;
	hold on;
	xlabel('x','FontSize', 14,...
 	'FontWeight', 'bold');
	ylabel('y', 'FontSize', 14,...
 	'FontWeight', 'bold');
	title('Érintő adott pontban', 'FontSize', 14,...
 	'FontWeight', 'bold');
	plot(x,y);
	plot(t0,y0,'ko');
	plot([t0-1 t0+1], [y0-d y0+d],'r');
	legend('fv. értékek','deriválási hely','érintő egyenes','location','northwest');
	hold off;

	print(abrak(3), '-depsc2', 'f031');
	print(abrak(3), '-dpng', 'f032');

	
	y = [100, 150]; t = [0, 20];
	mu = [200 300];

	F = @(t,y) [(1-y(2)/mu(2))*y(1); -(1-y(1)/mu(1))*y(2)] 
	
	[px,py] = ode45(F,t,y);
	abrak(4) = figure;
	subplot(2,1,1);
	xlabel('t','FontSize', 12,'FontWeight', 'bold');
	ylabel('egyedszám','FontSize', 12,'FontWeight', 'bold');
	title('Predator-Prey Modell', 'FontSize', 14,'FontWeight', 'bold');
	hold on;
	plot(px,py(:,1),'g','LineWidth',2);
	plot(px,py(:,2),'b','LineWidth',2);
	legend('zsákmány','ragadozó');
	hold off;
	subplot(2,1,2);
	xlabel('zsákmányok száma','FontSize', 12,'FontWeight', 'bold');
	ylabel('ragadozók száma','FontSize', 12,'FontWeight', 'bold');
	title('Fázisgörbe', 'FontSize', 14,'FontWeight', 'bold');
	hold on;
	plot(py(:,1),py(:,2),'b');
	hold off;

	print(abrak(4), '-depsc2', 'f041');
	print(abrak(4), '-dpng', 'f042');
	

	t= [0, 1.4]; y=[5, 7, 9];
	F = @(t,y) [1.2*y(1)+4.1*y(2)-1.7*y(3); -8*y(1)-1.4*y(2)+2.1*y(3); 2.1*y(1)-7.2*y(2)+1.3*y(3)]

	[px py] = ode45(F,t,y);
	
	felt = py(:,1) > py(:,2) & py(:,1) < py(:,3);
	my = py(felt,1);
	mx = px(felt);
	
	abrak(5) = figure;
	xlabel('idő','FontSize', 12,'FontWeight', 'bold');
	ylabel('koncentráció','FontSize', 12,'FontWeight', 'bold');
	hold on;
	plot(px,py(:,1),'b','LineWidth',2);
	plot(px,py(:,2),'k','LineWidth',2);
	plot(px,py(:,3),'r','LineWidth',2);
	legend('A','B','C','Location','southwest');
	plot(mx,my,'s g','MarkerFaceColor','g');
	hold off;


	print(abrak(5), '-depsc2', 'f051');
	print(abrak(5), '-dpng', 'f052');

end