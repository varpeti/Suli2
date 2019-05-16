--[[
]]

3NF:
    A) is in 2NF and and non-prime attribute dose not depend tranzitievly on any candidate key 
    or
    B) Either of the left hand side is the super key or the right hand side is a prime attribute.

    B)->A) 
    2NF is voilated if there is a such depedency

--[[ 05.10 Saját Gyak
]]

R(a,b,c,d,e,g,h,i)
F = {a->be, ab->de, ac->g}

{a->b, a->e, ab->d, ab->e, ac->g}
F- =  {a->b, a->e, a->d, ac->g} minimal cover

T1(a,b,e,d)
T2(a,c,g)
T3(h,i)
T4(a,c,h,i) mert candidate keys nincs benne egyik előzőbe se: ac, h, i

1NF no composite or multivalued attribute in the schema
2NF 1NF and there is no partial depedency on non primary attribute
3NF 2NF and and non-prime attribute dose not depend tranzitievly on any candidate key 
BCNF 3NF and for all Alpha->Beta FD, Alpha is a SK



--[[ 04.19 Saját gyak
]]

    Maximum kiválasztás
        T-ből akarjuk a maximum pontot elért halgatót.

        T1 <- pi[nev,pont](T)
        T2 <- ro[new_nev=nev,new_pont=pont](T1)
        Trossz <- szigma[pont>new_pont](T1 x T2)
        Tmegoldas <- T1-ro[nev=new_nev,pont=new_pont]( pi[new_nev,new_pont](Trossz) )

    Osztás  
        R(nev,osztaly) osztva S(osztaly)

        Trossz <- pi[nev](R) x S - pi[nev,osztaly](R)
        Tmegoldas <- pi[nev](R) - pi[nev](S)

    Axiomák

        tranz a->b, b->c => a->c

        relf abc->a mert a->a

        kibőv (augmentattion) a->b => ac->bc

    Következmény

        Unio a->b, a->c => a->bc

        Decomp a->bc => a->b, a->c

        psedo tranzitivity a->b c->d => ac->bd
            bizonyítás:
                bővítés: ca->cb bc->db
                tranzitivitás: ca->db



--[[ 04.17
]]

1NF no composite or multivalued attribute in the schema
2NF there is no partial depedency on non primary attribute
BCNF for all Alpha->Beta FD, Alpha is a SK

Tabular method

R(a,b,c,d,e,g)
F = {a->bg,c->d,cd->e,g->e,c->e}

L = a,c
M = d,g
R = b,e
O = -

L+O are CK 
M might part of the CK 

ac = {a,c,b,g,e,d} ist ok, if not all the attributes here, we need to add some attribute form M, and check. 

1NF true
2NF prime: a,c nonprime: b,d,e,g false cos a->bg violates
...

---

1) Example for decomp to BCNF
 
R(p,d,m) 
F = {pd->m, m->d}

CK: pd, pm
prime: p,d,m
nonprime: -

1NF true
2NF true
BCNF false cos m->d violates

R1(m,d)
F1 = {m->d} m is CK so BCNF is true

R2(m,p) 
F2 = {} pm is CK so BCNF is true

2) Better example for decomp to BCNF

R(a,b,c,d,e,g)
F = {a->bc,b->a,bd->eg,ab->c}

L = d
M = a,b,
R = c,e,g
O = -

d+ = {d} is not CK so:

ad+ = {a,d,b,c,e,g} is CK
bd+ = {b,d,a,c,e,g} is CK


--[[ 04.10
]]

F3 = {abc->d,d->a}
a   = {a}
b   = {b}
c   = {c}
d   = {d,a}
ab  = {a,b}
ac  = {a,c}
ad  = {a,d}
bc  = {b,c}
bd  = {b,d}
cd  = {c,d}
abc = {a,b,c,d} a->a b->b b->c abc->d
bcd = {a,b,c,d} d->a b->b c->c d->d

F4 = {ab->c,ab->d,c->a,d->b}
a = {a}
b = {b}
c = {c,a}
d = {d,b}
ab = {a,b,c,d} a->a b->b ab->c ab->d
ac = {a,c}
ad = {a,d,b,c} a->a d->d ab->c
...



--[[ 03.08
]]

Budapest, 2
New_York, 20
Lincoln, 0.2

sigma(cities.pop > towns.pop, cities¤town)

Budapest, Budapest  - 0
Budapest, New_York  - 0
Budapest, Lincoln   - 1
New_York, Budapest  - 1
New_York, New_York  - 0
New_York, Lincoln   - 1
Lincoln,  Budapest  - 0
Lincoln,  New_York  - 0
Lincoln,  Lincoln   - 0


pi(customer_name ,( account (X) depositor ) % pi(branch_name, sigma(barnchcity=Brooklyn, branch) ) )



--[[ 03.06
]]

AndOr
    X and true  = X
    X and false = false
    X and X     = X
    X or  true  = true
    X or  false = X
    X or  X     = X

Alapműveletek
    1 SELECT        "sigma"     -- Sor kiválasztás
    2 PROJECTION    "pi"        -- Oszlop kiválasztás
    3 Cross Product "¤"         -- Descartes szorzat, x
    4 Rename        "ro"        --
    5 Union         "u"         --
    6 Intersect     "^"         -- metszet, fordított u

Műveletek

    (X) - "natural join"    - sigma(r.b=s.b, r¤b)
    /   - "division"        - pi(a-b,A) - pi(a-b, (pi(a-b,A)¤B)-A )
        Példa:            
         A      B   A/B
        a b     b    a
        1 1     2    1
        1 2     4    2
        1 3
        1 4
        2 2
        2 4
        3 2
        3 3
        4 4
        4 5

    MIN/MAX - "min max" -
        1) Copy -> ro
        2) Cross Product -> ¤
        3) Selection -> New/Old
        4) Difference



--[[ 02.20 Gyak
]]

Levels of database design
    View     - external   - "user's interface"
    Logical  - conceptual - "DataB programers"
    Physical - internal   - "DataB administrators"

entity           - "is an object that represent the world's object throug it's attributes"
attributies      - "entitie's property"
relationsips     - "logical connection betwen entitie sets"
super key        - "set of attributies, uniquely identify the entity"
candidate key    - "minimal sets of attributes uniquely identify the entity"
primary key      - "chosen candidate key"

entity relationsip model
    entity set              - "single layered rectangle"
    weak entity set         - "duble layered rectangle"  --Csak a kapcsolaton keresztül van értelme
    attribute               - "single layered oval"
    derivered attribute     - "dotted line oval"         --számolt
    multi valued attribute  - "duble line oval"          --ugyan abból több
    composite attribute     - "attribute's attributes"   --több részegységből van
    primary key             - "under line"
    discriminator           - "dotted under line"
    relation                - "diamond"
        total participation - "duble line"
    weak relation           - "duble layered diamond"
    ISA                     - "triangle"                 --öröklődés


------
--gyak lapon

------

book (entity)
    title (string)
    author (string)
    book id (integer)

costumer (entity)
    name (string)
    address (string)
    idcard (integer)

costumer_book (relation|m2m)
    startdate (date)
    enddate (date)







--[[02.15 Előadás
]]
Points:
    100
        60
            30 ZH1
            30 ZH2
        20 Project
        20 SQL computer room exam


Data
Information
Metadata
Index

File managaer
Transaction managaer

DBMS = Data Base Management System

Querry, Querry language

Multi user enviroement
    Concurrent usage
    Transaction Management
    Concurrency Contrrol

Dada (base) models
    wordl ->[abstraction]-> Data model
    