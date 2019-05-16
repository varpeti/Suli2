function [struktura, abra, A, B]=gyak8_f84_BUGE0Q(bemenetiFajl)
	f = fopen(bemenetiFajl);
		A = fscanf(f,'%f',6);
		B = fscanf(f,'%f',[21 inf]);
	fclose(f);

	[x, y] = meshgrid(A(1):A(2):A(3), A(4):A(5):A(6));

	struktura = struct('x',x,'y',y, 'z',B);

	abra = figure;
	hold on;
	plot3(struktura.x, struktura.y, struktura.z,'g.');
	view(-41, 28);
	contour3(struktura.x, struktura.y, struktura.z);
	clabel(contour3(struktura.x,struktura.y, struktura.z));
	xlabel('x');
	ylabel('y');
	zlabel('z');
	title('a betoltott adapont-felho');
	colorbar;
	hold off;

	save('gyak8_f84_kimenet.mat', 'struktura');
end