function [tablazat]=gyak9_f91_BUGE0Q()

t = 0:0.001:pi
for i=1:length(t)
	switch round(5*sin(3*exp(t(i))))
		case 1
			et{i, 1} = 'elégtelen'
		case 2
			et{i, 1} = 'elégséges'
		case 3
			et{i, 1} = 'közepes'
		case 4
			et{i, 1} = 'jó'
		case 5
			et{i, 1} = 'jeles'
		otherwise
			et{i, 1} = 'elégtelen'
	end
end
tablazat = table(t', 5*sin(3*exp(t')), et, 'VariableNames', {'ido', 'eredmeny', 'ertekeles'});

end