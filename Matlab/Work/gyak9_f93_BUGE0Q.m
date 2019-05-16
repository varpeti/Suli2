function gyak9_f93()

	T = readtable('geodata.csv');
	X = reshape(T.X,[33, 45]);
	Y = reshape(T.Y,[33, 45]);
	Z = reshape(T.Z,[33, 45]);

	abra = figure;
	surf(X, Y, Z);
	hold on;
	[U, V, W]= surfnorm(Z);
	quiver3(X, Y, Z, U, V, W, 'm');
	load cmp;
	colormap(cmp);
	view(-15, 60);
	hold off;

	print(abra,'-dpng','surf2')


end