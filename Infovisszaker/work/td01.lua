local TxD = {	
	{0,1,0,1,1,0,1},
	{0,1,1,0,0,0,0},
	{0,0,0,0,0,1,1},
	{0,0,0,1,0,0,0},
	{0,1,1,0,0,0,0},
	{1,0,0,1,0,0,0},
	{0,0,0,0,1,1,0},
	{0,0,1,1,0,0,0},
	{1,0,0,1,0,0,0},
}

local Q = {0,1/math.sqrt(5),0,0,1/math.sqrt(5),1/math.sqrt(5),1/math.sqrt(5),1/math.sqrt(5),0}


function TFN(TxD) -- TFN normált
	local n,m = #TxD,#TxD[1]
	for j=1,m do --D
		local o = 0
		for i=1,n do --T
			o = o + TxD[i][j]^2
		end
		for i=1,n do
			TxD[i][j]=TxD[i][j]/math.sqrt(o)
		end
	end
end

function Cosin(TxD,Q)
	local R = {}
	local n,m = #TxD,#TxD[1]
	for j=1,m do
		local o = 0
		for i=1,n do
			o = o + TxD[i][j]*Q[i] --Skalár szorzás
		end
		R[j]=o
	end
	return R
end

function Dice(TxD,Q)
	local R = {}
	local n,m = #TxD,#TxD[1]
	for j=1,m do
		local o, oo = 0,0
		for i=1,n do --Szumma
			o 	= o  + TxD[i][j]*Q[i] --Skaláris szorzás
			oo 	= oo + TxD[i][j]+Q[i]
		end
		R[j] = 2*o / oo
	end
	return R
end

function Jaccard(TxD,Q)
	local R = {}
	local n,m = #TxD,#TxD[1]
	for j=1,m do
		local o,oo = 0,0
		for i=1,n do --Szumma
			o 	= o  + TxD[i][j] * Q[i]
			oo 	= oo + (TxD[i][j]+Q[i])/( 2^(TxD[i][j] * Q[i]) )
		end
		R[j]=o/oo
	end
	return R
end

TFN(TxD)
R = {}
R.cos = Cosin(TxD,Q)
R.dice = Dice(TxD,Q)
R.jaccard = Jaccard(TxD,Q)



function deep_pretty_print(data,szint)
	szint = szint or 0
	local r = ""
	if type(data)=="table" then
		for n,v in pairs(data) do
			local t = ""
			for i=1,szint do t=t.."\t" end
			r = r..t..tostring(n)..":\n"..t..deep_pretty_print(v,szint+1)
		end
	else
		r = "\t"..tostring(data).."\n"
	end
	return r
end

print(deep_pretty_print(R))





