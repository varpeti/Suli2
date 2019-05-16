--[[17.9.11
]]
tárgyteljesítés = {ZH=2, min=50%, kollokvium=true, részvétel=80%, katalógus=true}

ZH = {okt.9, nov.27, dec.11}

Mi az információ visszakeresés?
    Releváns információk keresésének módszerei.
    ! nem információ kinyerés - struktúrálatlan szövegből struktúrált adatok készítése
        pl e-mail címek

Bevezetés
    Web: WWW = word wide web
    Internet: Fizikai hálózat

Régebben:
    Könyvtár: információ visszakeresés, papír alapú könyvekből
Mostanában:
    Böngészés: weben, sokkal gyorsabb

Weboldalak száma:
    1993: 130
    1997: 1milka

Web élete:
    1.0 hőskor 1990-2001 (saját információk)
    2.0 közösség (wikipédia, multiplayer)
    3.0 ??? 
        semantikus web
        érzékelő
        szociális
        mobil
        VR 

Metaadat
    adat egy adatról 
        mi láthó a képen?
        könyv címe, szerzője stb

Szemnatika
    Konkrét kérdés

Pár statisztika a jelenlegi keresőkről

Információ visszakeresés alapjai:
    Sorrend
    Hierarchia: fejezetek

Kialakulás:
    Hidegháború
        Orosz, Amcsi verseny
        "Sir Timothy" (web atya) CERN-ben
        1993.ápr.30 világháló elérhető a publikum számára
        1990-re rengeteg módszer létezett információ visszakeresésre
        

--[[09.18
]]

1. dia második fele

Adattípúsok
    struktúrált
    félig-struktúrált
    struktúrálatlan

Adott kérdésre válasz:
    Adatbázis - struktúrált
    IR - struktúrálatlan

Bányászat:
    Adatbányászat
        Kiindulás: struktúrált
        Cél: Összefüggések feltárása
    Szövegbányászat
        Kiindulás: struktúrálatlan
        Cél: Összefüggések feltárása
    IR
        Kiindulás: struktúrálatlan
        Cél: Adott információ igényre, minnél gyorsabb nagy revelanciájó adatok kilistázása.

Nyelvtech

Nevek


2. dia

Def:
    IR = (U,IN,Q,O)->R 
        IR = információ visszakeresés
        U = felhasználó
        IN = információ igény
        Q = kereső kérdés
        O = Objektumok halmaza
        R = Válasz objektumok halmaza

    IN = (Q,I)
        I = Meg nem fogalmazott része a kérdésnek


Visszakereső modellek
    1 IR
    2 Klaszikus
    3 Boole
    4 Vektortér


Q és D (Dokumentum) távolságának matematikai mérésén alapul

Klasszikus:
    Boole - logika
    Vektortér - linal
    Valószínűségi - valszám

Boole
    Tartalmazza
    Nem tartalmazza

    Operátorok
        Negáció
        Logikai
            és, vagy

D (dokumentum) m darab j futó 1-től
T (dokumentumok) n darab i futó 1-től


Boole "38. dia"

Feladatok

O[1]=[[Még nyílnak a völgyben a kerti
virágok,
Még zöldell a nyárfa az ablak
előtt,
De látod amottan a téli
világot?
Már hó takará el a bérci tetőt.]]

O[2]=[[Fenyő ága Hósubában,
Mire vársz a Hófúvásban?
Hideg az a Kristálybunda,
Gyere haza Kis
házunkba.]]

O[3]=[[Fekete Pont Fehér
Ágon:
Varjú károg:
Fázom Fázom.]]

t = {"virág","tél","hó","fenyő","bunda","varjú"}

D[1] = {t[1],t[2]}
D[2] = {t[4],t[3],t[5]}
D[3] = {t[6]}

Q = t[3] and t[4]
->
S = {{D[1],D[2]},{D[2]}}
->
R = D[2]

---

Q = not t[1] or not t[2]
S = {{D[2],D[3]},{D[2],D[3]}}
R = {D[2],D[3]}

Vektrotérmodell "45. Dia"

TxD mátrix
    m oszlop (dokszám)
    n sor ()

--[[17.09.25
]]

W[i][j]= az a 0 és 1 közötti súly a T[i] x D[j] mátrixban --(D[j] felül)

Skálafüggetlen hálózat: Hatványfüggvény eloszlás. F(x)=C*x^(-A)


TF-IDF:
W[i][j] = f[i][j] * log(m/F[i])
    f[i][j]     i. dokumentum j. kifejezés előfordulása
    m           dokumentumok száma
    F[i]        Azon dokumentumok száma melyekben előfordul a T[i] kifejezés


-------------

D = {(2,4),(1,4),(0,1)}

Bináris: 
    W[1]={1,1}
    W[2]={1,1}
    W[3]={0,1}
    --máshogy írva:
    W = {{1,1},{1,1},{0,1}}
Gyakoriság:
    W = {{2,4},{1,4},{0,1}}
MaxNorm:
    W = {{1/2,1},{1/4,1},{0,1}}
NormNorm:
    W = {{1/3,2/3},{1/5,4/5},{0,1}}
TFN:
    W = {{2/q(20),4/q(20)},{1/q(17),4/q(17)},{0,1}}
TF-IDF:
    W = {{2*log(3/2),0},{1*log(3/2),0},{0,0}}

TF-IDF:
    W = {{gyak*log(docszám/EnnyiDockbanVanBenneAKif),}}

--------------


TxD = { 
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


Q = {0,1/q(5),0,0,1/q(5),1/q(5),1/q(5),1/q(5),0}

Számolás, Eredmény: td01.lua

--------------------

Hasnolősági mértékek:
    
    Skalár, dot mérték:
        Minden D[j] dokumentumra:
            R[j] = SUM(i=1, n, TxD[i][j]*Q[i]) 
                -- SUM(futó,max,skalár)
                -- R[j] a D[j] dokumentum a kérdésre adott válasz

    Cosinusz mérték:
        u.a

    Dice mérék:
        Minden D[j] dokumentumra:
            R[j] = 2*SUM(i=1, n, TxD[i][j]*Q[i]) / SUM(i=1, n, TxD[i][j]+Q[i])

    Jaccard együttható:
        Minden D[j] dokumentumra:
            R[j] = SUM(i=1, n, TxD[i][j]*Q[i]) / SUM(i=1, n, (TxD[i][j]+Q[i]) / 2^( TxD[i][j]*Q[i] ) )


                         SUM(i=1, n, TxD[i][j]*Q[i]) 
            R[j]=   -------------------------------------
                    SUM(i=1, n,   (TxD[i][j]+Q[i])      )
                       (        --------------------    )
                       (        (2^( TxD[i][j]*Q[i])    )


---------------------

Bizonytalanság:
    U = -SUM(j=1,m, p[j]*log(p[j]) )
        p[j] = R[j]/SUM(k=1,m,R[k])


--[[11.06
]]

Teljesség,felidézés:
recall = |Ra| / |R|
    |R|     = adott kérdésre (szakértők álltal meghatározott) releváns dokumentumok számossága
    |Ra|    = adott kérdésre a visszekereső álltal meghatározott dokumentumok számossága

Pontosság:
precision = |Ra| / |A|
    |A|     = a találati lista álltal visszaadott össszes dokumentum számossága 


--------------------
Feladat:

relevans_doc_halmaz = Rq = {D[3],D[5],D[9],D[25],D[39],D[44],D[56],D[71],D[89],D[123]}

talalati_lista = {123,84,56,6,8,9,511,129,187,25,38,48,250,113,3}

Qra_revelánsak_a_talalatok_kozul = {123,56,9,25,3}

D[123]: f = 10% p = 1
D[56]:  f = 20% p = 2/3
D[9]:   f = 30% p = 3/6
D[25]:  f = 40% p = 4/10
D[3]:   f = 50% p = 5/15


----------------

Ha nem 10 elemű a relevans_doc_halmaz akkor interpoláció.

Pl.: 3: {33.3%, 66.6%, 100%}
33.3%   -> {  0%, 10%, 20%, 30%}
66.6%   -> { 40%, 50%, 60%     }
100%    -> { 70%, 80%, 90%,100%}

Pl.: 16 
A százalék alattiak maximumát nézzük. 
    {{12.5%,2/3},{18,55%,3/6}} -> {20%,3/6}

--------------
feladat:

Rq = {9,56,123}

talalati_lista = {123,84,56,6,8,9,511,129,187,25,38,48,250,113,3}

Qra_revelánsak_a_talalatok_kozul = {123,56,9}

D[123]: f = 33.3% p = 1     --{  0%, 10%, 20%, 30%}
D[56]:  f = 66.6% p = 2/3   --{ 40%, 50%, 60%     }
D[9]:   f = 100%  p = 3/6   --{ 70%, 80%, 90%,100%}

--------------
feladat:

Rq = {3,5,9,25,39,44,56,71,89,123,200,201,202,203,204,205}

talalati_lista = {123,84,56,6,8,9,511,129,187,25,38,48,250,113,3}

Qra_revelánsak_a_talalatok_kozul = {123,56,25,3}

D[123]: f = 6.25%  p = 1        -- {10%}
D[56]:  f = 12.5%  p = 2/3      -- {}
D[9]:   f = 18.55% p = 3/6      -- {20%}
D[25]:  f = 25%    p = 4/10     -- {30%}
D[3]:   f = 31.25% p = 5/15     -- {40%}

----------

~P(r) = sum(1,N[q],)  


--[[11.13
]]

( (A[1]+A[2])*20 + (A[3]+A[4]+A[5])*17 + (A[6]+A[7]+A[8]+A[9]+A[10])*10 ) / ( 141 - (10*(10-A.size()))