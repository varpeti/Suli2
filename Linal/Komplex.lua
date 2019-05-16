[[Három féle alak]]
--Algebrai:
Za = a+b*i
--Geometriai:
Zg = r[cos(s)+i*sin(s)] -- 0<s<2pi
--Exponenciális
Ze = r*e^(i*s) -- 0<s<2pi

[[Átváltás]]
Za->Zg	Za->Ze		r = sqrt(a^2+b^2)	s = atg(b/a) {+pi} -- {}-csak akkor ha: a<0
Zg->Za	Ze->Za		a = r*cos(s)		b = r*sin(s)		

[[Összadás]]
Za		(a+b*i)+(c+d*i) = (a+c)+(b+d)*i

[[Kivonás]]
Za		(a+b*i)-(c+d*i) = (a-c)+(b-d)*i

[[Szorzás]]
--Def
Za		(a;b)*(c;d) = (ac-bd;bc+ad)
--Gyak
Za		(a+b*i)*(c+d*i) = ac+ad*i+bc*i-bd
Zg		r[cos(s)+i*sin(s)] * q[cos(t)+i*sin(t)] = r*q[cos(s+t)+i*sin(s+t)] -- 0<(s+t)<2pi
Ze		r*e^(i*s) * q*e^(i*t) = r*q*e^[i*(s+t)] -- 0<(s+t)<2pi

[[Osztás]]
--Gyak
Za		(a+b*i)/(c+d*i) = (a+b*i)/(c+d*i) * (c-d*i)/(c-d*i) = (e+f*i)/g = [(e/g)+(f/g)*i]
Zg		r[cos(s)+i*sin(s)] / q[cos(t)+i*sin(t)] = [r/q]*[cos(s-t)+i*sin(s-t)] -- 0<(s-t)<2pi
Ze		r*e^(i*s) / q*e^(i*t) = [r/q]*e^[i*(s-t)] -- 0<(s-t)<2pi

[[Komplementer]]
		_______
Za		(a+b*i) = (a-b*i)
		__________________
Zg		r[cos(s)+i*sin(s)] = r[cos(2pi-s)+i*sin(2pi-s)]
		_________
Ze		r*e^(i*s) = r*e^(i*[2pi-s])

[[i hatványai]]
i^1 = +i
i^2 = -1
i^3 = -i
i^4 = +1
i^5 = +i
		{	+1 	ha (n mod 4) = 0 -- 'mod' osztási maradék
i^n =	{	+i 	ha (n mod 4) = 1
 		{	-1 	ha (n mod 4) = 2
		{	-i 	ha (n mod 4) = 3

[[Hatványozás]]
Zg		{r[cos(s)+i*sin(s)]}^n = [r^n]*[cos(s*n)+i*sin(s*n)]
Ze		{r*e^(i*s)}^n = [r^n]*e^[i*(s*n)]

[[Gyökvonás]]
Zg		{r[cos(s)+i*sin(s)]}^(1/n) = [r^(1/n)]*[cos( s/n + k*[2pi/n] )+i*sin( s/n + k*[2pi/n] )] -- k € [0,..,n-1] természetes számoknak
Ze		{r*e^(i*s)}^(1/n) = [r^(1/n)]*e^[i*(s/n + k*[2pi/n])] -- k € [0,..,n-1] természetes számoknak
