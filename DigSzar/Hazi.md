# Házi feladat Digitális Rendszerek és Számítógép Architektúrák c. tárgyhoz, 2019
Tervezzen  meg  egy  olyan  logikai  kapcsolást,  amely  minimális  számú logikai kapuból és bemenetből áll és az alábbi függvényt valósítja meg: F = ∑(3, 12, 13, 14, 15, 20, 21, 22, 23, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 38, 39, 44, 45, 46, 47, 48, 50, 52, 54, 56, 57, 58, 59, 60, 61, 62, 63)

## 1. Határozza   meg   a   bemenetek   és   a   kimenetek   számát!   Ennek megfelelően alkossa meg az igazságtáblázatukat!

A megadott függvény megvalósításához legalább 5 bemenetre van szükség, mivel 64 = 2^6 

Lua kód:
```lua
local m = {3, 12, 13, 14, 15, 20, 21, 22, 23, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 38, 39, 44, 45, 46, 47, 48, 50, 52, 54, 56, 57, 58, 59, 60, 61, 62, 63}
local a = {32,16,8,4,2,1}
local b = { 1, 1,1,1,1,1}
for i=0,63 do
    for j,v in ipairs(a) do
        if i%v==0 then
            if b[j]==0 then b[j]=1 else b[j]=0 end
        end
    end
    local e = 0
    for j,v in ipairs(m) do
        if v==i then 
            e=1
            break
        end
    end
    print(i,"|",b[1],b[2],b[3],b[4],b[5],b[6],"|",e)
end
```
Kimenet:
```
#   |   A   B   C   D   E   F       M
----+---------------------------+-------
0   |   0   0   0   0   0   0   |   0
1   |   0   0   0   0   0   1   |   0
2   |   0   0   0   0   1   0   |   0
3   |   0   0   0   0   1   1   |   1
4   |   0   0   0   1   0   0   |   0
5   |   0   0   0   1   0   1   |   0
6   |   0   0   0   1   1   0   |   0
7   |   0   0   0   1   1   1   |   0
8   |   0   0   1   0   0   0   |   0
9   |   0   0   1   0   0   1   |   0
10  |   0   0   1   0   1   0   |   0
11  |   0   0   1   0   1   1   |   0
12  |   0   0   1   1   0   0   |   1
13  |   0   0   1   1   0   1   |   1
14  |   0   0   1   1   1   0   |   1
15  |   0   0   1   1   1   1   |   1
16  |   0   1   0   0   0   0   |   0
17  |   0   1   0   0   0   1   |   0
18  |   0   1   0   0   1   0   |   0
19  |   0   1   0   0   1   1   |   0
20  |   0   1   0   1   0   0   |   1
21  |   0   1   0   1   0   1   |   1
22  |   0   1   0   1   1   0   |   1
23  |   0   1   0   1   1   1   |   1
24  |   0   1   1   0   0   0   |   1
25  |   0   1   1   0   0   1   |   0
26  |   0   1   1   0   1   0   |   1
27  |   0   1   1   0   1   1   |   0
28  |   0   1   1   1   0   0   |   1
29  |   0   1   1   1   0   1   |   1
30  |   0   1   1   1   1   0   |   1
31  |   0   1   1   1   1   1   |   1
32  |   1   0   0   0   0   0   |   1
33  |   1   0   0   0   0   1   |   1
34  |   1   0   0   0   1   0   |   1
35  |   1   0   0   0   1   1   |   1
36  |   1   0   0   1   0   0   |   0
37  |   1   0   0   1   0   1   |   0
38  |   1   0   0   1   1   0   |   1
39  |   1   0   0   1   1   1   |   1
40  |   1   0   1   0   0   0   |   0
41  |   1   0   1   0   0   1   |   0
42  |   1   0   1   0   1   0   |   0
43  |   1   0   1   0   1   1   |   0
44  |   1   0   1   1   0   0   |   1
45  |   1   0   1   1   0   1   |   1
46  |   1   0   1   1   1   0   |   1
47  |   1   0   1   1   1   1   |   1
48  |   1   1   0   0   0   0   |   1
49  |   1   1   0   0   0   1   |   0
50  |   1   1   0   0   1   0   |   1
51  |   1   1   0   0   1   1   |   0
52  |   1   1   0   1   0   0   |   1
53  |   1   1   0   1   0   1   |   0
54  |   1   1   0   1   1   0   |   1
55  |   1   1   0   1   1   1   |   0
56  |   1   1   1   0   0   0   |   1
57  |   1   1   1   0   0   1   |   1
58  |   1   1   1   0   1   0   |   1
59  |   1   1   1   0   1   1   |   1
60  |   1   1   1   1   0   0   |   1
61  |   1   1   1   1   0   1   |   1
62  |   1   1   1   1   1   0   |   1
63  |   1   1   1   1   1   1   |   1
----+---------------------------+-------
```

# 2.   Quine-McCluskey függvényminimalizálási eljárás segítségével határozza meg a kimenetet. 

Lua kód:
```lua
local m = {3, 12, 13, 14, 15, 20, 21, 22, 23, 24, 26, 28, 29, 30, 31, 32, 33, 34, 35, 38, 39, 44, 45, 46, 47, 48, 50, 52, 54, 56, 57, 58, 59, 60, 61, 62, 63}
local a = {32,16,8,4,2,1}
local b = { 1, 1,1,1,1,1}


function generate()
    local minterms = {}
    for i=0,63 do
        for j,v in ipairs(a) do
            if i%v==0 then
                if b[j]==0 then b[j]=1 else b[j]=0 end
            end
        end
        for j,v in ipairs(m) do
            if v==i then 
                --print(i,"|",b[1],b[2],b[3],b[4],b[5],b[6])
                local minterm = {i,b[1],b[2],b[3],b[4],b[5],b[6]}
                table.insert(minterms,minterm)
            end
        end
    end
    return minterms
end

--If two variables differ in exactly one variable, the two minterms will combine together.
function fgroup(minterms)
    local groups = {}
    for i=0,6 do
        groups[i]={}
    end

    for i,minterm in ipairs(minterms) do
        local count = 0
        for j=2,7 do
            if minterm[j]==1 then count=count+1 end
        end
        table.insert(groups[count],minterm)
    end
    return groups
end

local minterms = generate()
local groups = fgroup(minterms)

for i,group in pairs(groups) do
    print(i..":")
    for j,minterm in ipairs(group) do
        print(minterm[1],"|",minterm[2],minterm[3],minterm[4],minterm[5],minterm[6],minterm[7])
    end
    print()
end
```
Kimenet:
```
0:

1:
32  |   1   0   0   0   0   0

2:
3   |   0   0   0   0   1   1
12  |   0   0   1   1   0   0
20  |   0   1   0   1   0   0
24  |   0   1   1   0   0   0
33  |   1   0   0   0   0   1
34  |   1   0   0   0   1   0
48  |   1   1   0   0   0   0

3:
13  |   0   0   1   1   0   1
14  |   0   0   1   1   1   0
21  |   0   1   0   1   0   1
22  |   0   1   0   1   1   0
26  |   0   1   1   0   1   0
28  |   0   1   1   1   0   0
35  |   1   0   0   0   1   1
38  |   1   0   0   1   1   0
44  |   1   0   1   1   0   0
50  |   1   1   0   0   1   0
52  |   1   1   0   1   0   0
56  |   1   1   1   0   0   0

4:
15  |   0   0   1   1   1   1
23  |   0   1   0   1   1   1
29  |   0   1   1   1   0   1
30  |   0   1   1   1   1   0
39  |   1   0   0   1   1   1
45  |   1   0   1   1   0   1
46  |   1   0   1   1   1   0
54  |   1   1   0   1   1   0
57  |   1   1   1   0   0   1
58  |   1   1   1   0   1   0
60  |   1   1   1   1   0   0

5:
31  |   0   1   1   1   1   1
47  |   1   0   1   1   1   1
59  |   1   1   1   0   1   1
61  |   1   1   1   1   0   1
62  |   1   1   1   1   1   0

6:
63  |   1   1   1   1   1   1
```

Lua kód:
```lua
function algo(minterms)
    local ret = {}
    for i,m1 in ipairs(minterms) do
        for j,m2 in ipairs(minterms) do
            for sintaxcsemege4continue=1,1 do

            -- Decimális index külömbsége négyzetszám
            local dn = false
            for k,x in ipairs(a) do
                if math.abs(m1[1]-m2[1])==x then dn=true break end
            end

            if not dn then break end

            -- Bináris súlyuk különbsége 1
            local c1,c2 = 0,0
            for k=2,7 do
                if m1[k]=="1" then c1=c1+1 end
                if m2[k]=="1" then c2=c2+1 end
            end
            if math.abs(c1-c2)~=1 then break end

            -- A nagyobb decimális indexhűhöz nagyobb bináris súly tartozik
            -- És mivel kereszt szorzat itt felezzük le
            if not (m1[1]>m2[1] and c1>c2) then break end
            
            --print(m1[1],m2[1])
            local r = {}
            r[1] = m1[1].." "..m2[1]
            for k=2,7 do
                r[k]=m1[k]
                if m1[k]~=m2[k] then r[k]="-" end
            end
            table.insert(ret,r)

            end --sintaxcsemege4continue
        end
    end 
    return ret
end

local implicants = algo(minterms)

for i,v in ipairs(implicants) do
    print(v[1],"|",v[2],v[3],v[4],v[5],v[6],v[7])
end
```
Kimenet:
```
13 12   |   0   0   1   1   0   -
14 12   |   0   0   1   1   -   0
15 13   |   0   0   1   1   -   1
15 14   |   0   0   1   1   1   -
21 20   |   0   1   0   1   0   -
22 20   |   0   1   0   1   -   0
23 21   |   0   1   0   1   -   1
23 22   |   0   1   0   1   1   -
26 24   |   0   1   1   0   -   0
28 12   |   0   -   1   1   0   0
28 20   |   0   1   -   1   0   0
28 24   |   0   1   1   -   0   0
29 13   |   0   -   1   1   0   1
29 21   |   0   1   -   1   0   1
29 28   |   0   1   1   1   0   -
30 14   |   0   -   1   1   1   0
30 22   |   0   1   -   1   1   0
30 26   |   0   1   1   -   1   0
30 28   |   0   1   1   1   -   0
31 15   |   0   -   1   1   1   1
31 23   |   0   1   -   1   1   1
31 29   |   0   1   1   1   -   1
31 30   |   0   1   1   1   1   -
33 32   |   1   0   0   0   0   -
34 32   |   1   0   0   0   -   0
35 3    |   -   0   0   0   1   1
35 33   |   1   0   0   0   -   1
35 34   |   1   0   0   0   1   -
38 34   |   1   0   0   -   1   0
39 35   |   1   0   0   -   1   1
39 38   |   1   0   0   1   1   -
44 12   |   -   0   1   1   0   0
45 13   |   -   0   1   1   0   1
45 44   |   1   0   1   1   0   -
46 14   |   -   0   1   1   1   0
46 38   |   1   0   -   1   1   0
46 44   |   1   0   1   1   -   0
47 15   |   -   0   1   1   1   1
47 39   |   1   0   -   1   1   1
47 45   |   1   0   1   1   -   1
47 46   |   1   0   1   1   1   -
48 32   |   1   -   0   0   0   0
50 34   |   1   -   0   0   1   0
50 48   |   1   1   0   0   -   0
52 20   |   -   1   0   1   0   0
52 48   |   1   1   0   -   0   0
54 22   |   -   1   0   1   1   0
54 38   |   1   -   0   1   1   0
54 50   |   1   1   0   -   1   0
54 52   |   1   1   0   1   -   0
56 24   |   -   1   1   0   0   0
56 48   |   1   1   -   0   0   0
57 56   |   1   1   1   0   0   -
58 26   |   -   1   1   0   1   0
58 50   |   1   1   -   0   1   0
58 56   |   1   1   1   0   -   0
59 57   |   1   1   1   0   -   1
59 58   |   1   1   1   0   1   -
60 28   |   -   1   1   1   0   0
60 44   |   1   -   1   1   0   0
60 52   |   1   1   -   1   0   0
60 56   |   1   1   1   -   0   0
61 29   |   -   1   1   1   0   1
61 45   |   1   -   1   1   0   1
61 57   |   1   1   1   -   0   1
61 60   |   1   1   1   1   0   -
62 30   |   -   1   1   1   1   0
62 46   |   1   -   1   1   1   0
62 54   |   1   1   -   1   1   0
62 58   |   1   1   1   -   1   0
62 60   |   1   1   1   1   -   0
63 31   |   -   1   1   1   1   1
63 47   |   1   -   1   1   1   1
63 59   |   1   1   1   -   1   1
63 61   |   1   1   1   1   -   1
63 62   |   1   1   1   1   1   -
```
Tovább:
(awk magic-el kiszedve és kézzel beírva a kimaradt rész)
```
12 13 14 15 |  0   0   1   1   -   -
12 13 28 29 |  0   -   1   1   0   -
12 13 44 45 |  -   0   1   1   0   -
12 14 28 30 |  0   -   1   1   -   0
12 14 44 46 |  -   0   1   1   -   0
12 28 44 60 |  -   -   1   1   0   0
13 15 29 31 |  0   -   1   1   -   1
13 15 45 47 |  -   0   1   1   -   1
13 29 45 61 |  -   -   1   1   0   1
14 15 30 31 |  0   -   1   1   1   -
14 15 46 47 |  -   0   1   1   1   -
14 30 46 62 |  -   -   1   1   1   0
15 31 47 63 |  -   -   1   1   1   1
20 21 22 23 |  0   1   0   1   -   -
20 21 28 29 |  0   1   -   1   0   -
20 22 28 30 |  0   1   -   1   -   0
20 22 52 54 |  -   1   0   1   -   0
20 28 52 60 |  -   1   -   1   0   0
21 23 29 31 |  0   1   -   1   -   1
22 23 30 31 |  0   1   -   1   1   -
22 30 54 62 |  -   1   -   1   1   0
24 26 28 30 |  0   1   1   -   -   0
24 26 56 58 |  -   1   1   0   -   0
24 28 56 60 |  -   1   1   -   0   0
26 30 58 62 |  -   1   1   -   1   0
28 29 30 31 |  0   1   1   1   -   -
28 29 60 61 |  -   1   1   1   0   -
28 30 60 62 |  -   1   1   1   -   0
29 31 61 63 |  -   1   1   1   -   1
30 31 62 63 |  -   1   1   1   1   -
32 33 34 35 |  1   0   0   0   -   -
32 34 48 50 |  1   -   0   0   -   0
34 35 38 39 |  1   0   0   -   1   -
34 38 50 54 |  1   -   0   -   1   0
38 39 46 47 |  1   0   -   1   1   -
38 46 54 62 |  1   -   -   1   1   0
44 45 46 47 |  1   0   1   1   -   -
44 45 60 61 |  1   -   1   1   0   -
44 46 60 62 |  1   -   1   1   -   0
45 47 61 63 |  1   -   1   1   -   1
46 47 62 63 |  1   -   1   1   1   -
48 50 52 54 |  1   1   0   -   -   0
48 50 56 58 |  1   1   -   0   -   0
48 52 56 60 |  1   1   -   -   0   0
50 54 58 62 |  1   1   -   -   1   0
52 54 60 62 |  1   1   -   1   -   0
56 57 58 59 |  1   1   1   0   -   -
56 57 60 61 |  1   1   1   -   0   -
56 58 60 62 |  1   1   1   -   -   0
57 59 61 63 |  1   1   1   -   -   1
58 59 62 63 |  1   1   1   -   1   -
60 61 62 63 |  1   1   1   1   -   -

Kimaradt:
3 35    |   -   0   0   0   1   1
```
Tovább:
```
12 13 14 15 28 29 30 31 |   0   -   1   1   -   -
12 13 14 15 44 45 46 47 |   -   0   1   1   -   -
12 13 28 29 44 45 60 61 |   -   -   1   1   0   -
12 14 28 30 44 46 60 62 |   -   -   1   1   -   0
13 15 29 31 45 47 61 63 |   -   -   1   1   -   1
14 15 30 31 46 47 62 63 |   -   -   1   1   1   -
20 21 22 23 28 29 30 31 |   0   1   -   1   -   -
20 22 28 30 52 54 60 62 |   -   1   -   1   -   0
24 26 28 30 56 58 60 62 |   -   1   1   -   -   0
28 29 30 31 60 61 62 63 |   -   1   1   1   -   -
44 45 46 47 60 61 62 63 |   1   -   1   1   -   -
48 50 52 54 56 58 60 62 |   1   1   -   -   -   0
56 57 58 59 60 61 62 63 |   1   1   1   -   -   -

Kimaradt:
32 33 34 35 |   1   0   0   0   -   -
32 34 48 50 |   1   -   0   0   -   0
34 35 38 39 |   1   0   0   -   1   -
34 38 50 54 |   1   -   0   -   1   0
38 39 46 47 |   1   0   -   1   1   -
38 46 54 62 |   1   -   -   1   1   0
```
Tovább:
```
12 13 14 15 28 29 30 31 44 45 46 47 60 61 62 63 |   -   -   1   1   -   -

Kimaradt:
20 21 22 23 28 29 30 31 |   0   1   -   1   -   -
20 22 28 30 52 54 60 62 |   -   1   -   1   -   0
24 26 28 30 56 58 60 62 |   -   1   1   -   -   0
48 50 52 54 56 58 60 62 |   1   1   -   -   -   0
56 57 58 59 60 61 62 63 |   1   1   1   -   -   -
```

Táblázat:
(Kézzel kitöltve)
```
                                                |   A   B   C   D   E   F   |   3   12  13  14  15  20  21  22  23  24  26  28  29  30  31  32  33  34  35  38  39  44  45  46  47  48  50  52  54  56  57  58  59  60  61  62  63
3 35                                            |   -   0   0   0   1   1   |   1                                                                       0                                                                           
32 33 34 35                                     |   1   0   0   0   -   -   |                                                               0   1   0   0                                                                           
32 34 48 50                                     |   1   -   0   0   -   0   |                                                               0       0                               0   0                                           
34 35 38 39                                     |   1   0   0   -   1   -   |                                                                       0   0   0   0                                                                   
34 38 50 54                                     |   1   -   0   -   1   0   |                                                                       0       0                           0       0                                   
38 39 46 47                                     |   1   0   -   1   1   -   |                                                                               0   0           0   0                                                   
38 46 54 62                                     |   1   -   -   1   1   0   |                                                                               0               0                   0                           0       
20 21 22 23 28 29 30 31                         |   0   1   -   1   -   -   |                       0   1   0   1           0   0   0   0                                                                                           
20 22 28 30 52 54 60 62                         |   -   1   -   1   -   0   |                       0       0               0       0                                                       0   0                   0       0       
24 26 28 30 56 58 60 62                         |   -   1   1   -   -   0   |                                       1   1   0       0                                                               0       0       0       0       
48 50 52 54 56 58 60 62                         |   1   1   -   -   -   0   |                                                                                                       0   0   0   0   0       0       0       0       
56 57 58 59 60 61 62 63                         |   1   1   1   -   -   -   |                                                                                                                       0   1   0   1   0   0   0   0   
12 13 14 15 28 29 30 31 44 45 46 47 60 61 62 63 |   -   -   1   1   -   -   |       1   1   1   1                           0   0   0   0                           1   1   0   0                                   0   0   0   0   

```

Kiszedett a kifejezések:
(- jelöli a komplementert)
```
(-B -C -D E F), (C D), (-A B D), (B C -F), (A -B -C -D), (A B C)
```

Ebből az egyenlet:
```
S = (-B -C -D E F) ∨ (C D) ∨ (-A B D) ∨ (B C -F) ∨ (A -B -C -D) ∨ (A B C) ∨ (A -B -C E) ∨ (A B -F)
```

## 3. Realizálja  az  adott  függvényeket  egy  (logikai  kapukból  felépített) hálózattal.

![aramkor](aramkor.png "Aramkor")

## 4. Az   egyes   kapukat   milyen,   a   kereskedelemben   is   kapható, kapuáramkörökkel valósítaná meg (gyártó,  chip/IC  neve,  darabszám),  hogy  a  lehető  legkevesebb alkatrészt kelljen megvásárolni?

- Amilyen van a polcon... mert az a legolcsóbb.
- Amilyen van a szomszéd boltban, mert az a leggyorsabb.
- De ha mindenképp KEVESET kell venni:
    + 1db SN74LS04DR (Texas Instruments) (NOT 6 bemenet 6 kimenet)
    + 5db SN74AS21NS (Texas Instruments) (AND 8 bemenet 2 kimenet)
    + 1db M74HC4078 (STMicroelectronics) (OR  8 bemenet 1 kimenet)