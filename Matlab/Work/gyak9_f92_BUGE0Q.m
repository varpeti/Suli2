function gyak9_f92_BUGE0Q()

	T= sortrows(readtable('country_data.xls'),-7);

	writetable(T,'country_data_reordered.csv');

	summary(T(height(T)-10:height(T), 4));
	summary(T(height(T)-10:height(T), 5));
	summary(T(height(T)-10:height(T), 6));
	summary(T(height(T)-10:height(T), 7));

end