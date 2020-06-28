# Adatbiztonság és kriptográfia

| Jegyzőkönyv | 2. gyakorlat | 
| -- | -- |
| Készítette  | Váraljai Péter BUGE0Q |
| Dátum | 2020.04 |

# Tartalom jegyzék
+ 1. Bevezető
+ 2. Elmélet
    - 2.1 Blokklánc
    - 2.2 Tranzakció
        * 2.2.1 Elemei
        * 2.2.2 Ellenőrzése
    - 2.3 Bányászat
+ 3. Gyakorlat
    - 3.1 self.chain
    - 3.2 self.pending_transactions
    - 3.3 self.unspent_outputs
    - 3.4 self.my_unspent_outputs
    - 3.5 self.my_id
    - 3.6 self.ITKoin_users
    - 3.7 mine()
    - 3.8 generate_first_block()
    - 3.9 new_transaction(csaposhi, recipient)

# 1. Bevezető

A gyakorlat során egy blokklánc alapú technológiával szimuláltuk a ITKoin nevű kriptovaluta működését. A kód írása közben kitértünk a feladat kulcslépéseire, úgymint a tranzakcióhoz szükséges feltételekre, és a blokklánc építésének alapjaira.

Ebben a jegyzőkönyvben összefoglalom mind elméleti, mind gyakorlati szemszögből a kriptovaluta működését. Lebontom a műveletek okát és azok elméleti hátterét. 

# 2. Elmélet
## 2.1 Blokklánc

A blokklánc egy úgynevezett nyilvános főkönyvként működik, amely rögzíti az összes tranzakciót. Bárki csatlakozhat a blokkláncbővítéséhez, kezdeményezhet tranzakciókat, és hitelesítheti is azokat, blokkok létrehozásával.

## 2.2 Tranzakció

### 2.2.1 Tranzakció

A következő elemekből állnak a kriptovaluta tranzakciói:

+ Hivatkozott utalások (input)
+ Átutalt összeg (output)
+ Visszajáró összeg (output)
+ Tranzakciós díj (output)
+ Kezdeményező publikus kulcsa
+ Kezdeményezett publikus kulcsa
+ Digitális aláírás
+ Egyéb kiegészítő adatok*

*: Például Ethereum esetén futtatható kód.

#### Hivatkozott utalások (input)

Mivel minden utalás publikusan elérhető a blokkláncban, ezért egy tálcához tartozó egyenleg összegét a blokkláncban található tranzakciók alapján ki lehet számolni. Amikor valaki utalni szeretne, a korábbi tranzakciók visszajáró összegeit tudja felhasználni, azok hivatkozásainak felsorolásával. Így könnyen ellenőrizheti bárki a rendszerben egy tálcához tartozó egyenleg összegét, illetve azt, hogy az indított tranzakció helyes-e. Ez teljes védelmet nyújt olyan csalók ellen akik ugyan azon összeg többszöri elköltésével próbálkoznának. Fontos kritérium, hogy benne kell legyen a kriptovaluta rendszer felhasználóinak többsége által kezelt blokkláncban, és érvényes aláírással kell rendelkezzen.

#### Visszajáró összeg (output)

Mivel a tranzakciók során egy korábbi tranzakció output összegére csak egyetlen alkalommal lehet hivatkozni, és csak a teljes összegre, ami szinte biztos hogy nem egyezik meg a átutalni kívánt összeggel, ezért túlfizetés esetén a visszajáró összeg megjelenik mint output a tranzakción. Ennek lényege, hogy a tranzakció során a meghivatkozott tranzakciók összértékéből az át nem utalt összeget a kezdeményező fél visszakapja. Erre a visszajáró összegre hivatkozhat a későbbiekben a tálca tulajdonosa egy új tranzakció létrehozásakor.

#### Kezdeményező publikus kulcsa

A kripotvaluta rendszerében a publikus kulcs azonosítja a tálcákat. Így egy újonnan létrehozott tranzakcióba több okból kifolyólag is belekerül:
Egyfelől a tranzakció aláírásának hitelességét ennek segítségével bárki tudja ellenőrizni, másfelől pedig szükséges az input értékek, azaz meghivatkozott tranzakciók validálásához is, mivel csak olyan tranzakcióra lehet hivatkozni amelynek az outputjában (vagy kedvezményezettként, vagy visszajáróként) ugyan ez a publikus kulcs volt a kedvezményezett.

#### Kedvezményezett publikus kulcsa

A kedvezményezett publikus kulcsa ráíródik a tranzakcióra, és amikor fel akarja használni azt az összeget később róla, akkor ezen publikus kulcs privát párjával készült aláírásával tudja igazolni hogy ő és csak is ő jogosult a tranzakcióba foglalt összeget használni.

#### Digitális aláírás

A tranzakció érvényességét a tranzakció küldőjének privát kulcsával készült digitális aláírása bizonyítja. A digitális aláírás menete:

+ 1. Vesszük a tranzakció elemeinek (hivatkozások,összeg,visszajáró,publikus kulcsok, egyéb adatok) lenyomatát (hash értékét).
+ 2. Ezt a lenyomatot aláírja a tranzakciót kezdeményező, a privát kulcsának segítségével
+ 3. Az aláírást a tranzakció elemei után csatoljuk.

### 2.2.2 Ellenőrzése

3 + 1 fő részre osztható a tranzakció ellenőrzése:

+ 1. Meg kell vizsgálni a blokkláncban, hogy a hivatkozott tranzakciók valóban léteznek-e, és nem lettek-e már felhasználva egy korábbi tranzakció során bemeneteként.
+ 2. Ellenőrizni kell a tranzakció végére csatolt aláírást, hogy valóban a jogosult személy-e a kezdeményező.
+ 3. Meg kell vizsgálni hogy nem tartalmaz-e a rendszer szempontjából értelmetlen vagy veszélyes adatot.
+ + Ellenőrizni kell az egyéb csatolható adatokat. (Például ETH esetén a kódot)

Az ellenőrzésre a tranzakció publikus kulcsainak segítségével a rendszer bármely felhasználója képes bármikor. Így biztosított hogy a tranzakciót valóban a kezdeményező kezdeményezte, és rendelkezésére áll számára az utalni kívánt összeg.

### Hivatkozások ellenőrzése

Ahhoz hogy megvizsgáljuk hogy a tranzakció a valóban valós hivatkozásokat használ, végig kell menni a blokkláncon és ellenőrizni hogy léteznek-e a meghivatkozott tranzakciók, az outputon (vagy kedvezményezettként, vagy visszajáróként) szerepel az összeg, és hogy ezt még nem használta el sehol, azaz nem hivatkozta még meg sehol máshol.

### Aláírás ellenőrzése

Az aláírás ellenőrzéséhez kiszámoljuk a tranzakció elemeinek (a végére csatolt aláírást nem ide számítva) a lenyomatát (hash értékét) illetve a tranzakciót kezdeményező publikus kulcsával dekódoljuk a tranzakció végére csatolt aláírást. Ha a kettő megegyezik, valóban jogosult a tranzakciót kezdeményező a kezdeményezésre.

### Értelmetlen, veszélyes adat vizsgálata

Meg kell vizsgálni hogy nem tartalmaz-e a rendszer szempontjából értelmetlen vagy veszélyes adatot a tranzakció. Nem szabad a rendszerbe engedni olyan tranzakciókat ami mások végül kihasználhatnak.

#### Negatív utalás

Például ha valaki negatív összeget akar utalni valakinek, és ezt megengedjük, akkor a kedvezményezett ugyan nem károsul, mivel nem hivatkozna soha a negatív összegre, de a kezdeményező a visszajárót eltehetné zsebre, aminek semmilyen alapja illetve számbeli korlátja nincsen, és erre később tudna hivatkozni mint valós összeg

## 2.3 Bányászat

A bányászat során a rendszerben várakozó tranzakciókat egy blokkba gyűjtve, majd azt a rendszer által elfogadott blokklánchoz csatolva érvényessé tesszük. Az hogy ki rakhatja be a következő blokkot azt a Proof-of-Work elv alapján dől el.

### Bányász jutalom, tranzakciós díj

A bányász jutalom két részből áll, egy a tranzakcióba elhelyezett, forrással nem rendelkező, a bányász számára szóló előre meghatározott összeg, és a tranzakciókat kezdeményezők által meghatározott tranzakciós díjak adják ki. Ez motiválja a bányászokat arra hogy blokkláncot építsenek és így a rendszer működjön és fennmaradjon, másrészt a rengeteg tranzakciók közül azokat fogják elsőnek beépíteni korlátozott méretű blokkokba, amik nagyobb jutalmat ígérnek. 

A bányász jutalom feladata a rendszer fenntartásán felül még az is hogy valutát juttasson a rendszerbe, ugyanis erre nincs más lehetőség központi felügyelet híján.

### Bányászat nehézsége

A bányászat nehézségét a lenyomat (hash) érték elejére elvárt 0-ás bitek száma határozza meg. Minél több az elvárt 0-ás bitek száma, annál nehezebb a feladat, azaz annál nehezebb a lenyomatot előállítani.

# 3. Gyakorlat
## 3.1 self.chain

Egy fájlban tároljuk a blokkláncot. A ```load_chan()``` függvénnyel olvassuk be.
Egy lista amiben egymás után vannak a blokkok.
A ```mine()``` függvény fűz hozzá kész blokkokat.

## 3.2 self.pending_transactions

Egy fájlban tároljuk a várakozó tranzakciókat. A ```load_pending_transactions()``` függvénnyel olvassuk be, ahol validáljuk hogy érvényesek-e.
Egy lista amiben egymás után vannak az érvényes várakozó tranzakciók.
A ```mine()``` függvény "eszi" meg a benne lévő adatokat, egy blokkba építve azokat. A blokk headerjébe kerül a lenyomta (hash értéke) a blokkba meg az egész lista.

## 3.3 self.unspent_outputs

A ```find_unspent_outputs()``` függvény segítségével a blokkláncon végighaladva megkeressük az összes összeget, majd kivesszük azokat amik fel lettek használva belőle.

Tartalmazza a tranzakciók azonosítóját, és a pontos összegeket.

## 3.4 self.my_unspent_outputs

A ```find_unspent_outputs()``` függvény segítségével a blokkláncon végighaladva megkeressük az összes összeget ami a tálcánkhoz tartozik, majd kivesszük azokat amik fel lettek használva belőle.

Tartalmazza azon tranzakciók azonosítóját amiben kedvezményezettként szereplünk, és a pontos összegeket.

A ```new_transaction(csaposhi, recipient)``` függvény segítségével lehet felhasználni az elköltetlen összegeinket, ami addig vesz ki tranzakciókat míg a hozzá tartozó összegek egyenlőek vagy meg nem haladják a küldeni kívánt összeget.

## 3.5 self.my_id

A saját publikus kulcsunk lenyomata (hash értéke).
A ```load_my_private_key()``` függvény állítja elő publikus kulcsunkból, illetve a ```generate_rsa_key()``` menti ugyan ezt az értéket le egy ```filename+"_id.txt``` fájlba.

## 3.6 self.ITKoin_users

Ez egy lista ami tartalmazza a rendszerben résztvevő tálcák id fájljainak nevét.

A ```generate_first_block()``` függvény használja fel, ahol előveszi sorba az id fájl neveket, majd beolvassa tartalmát.

## 3.7 mine()

Kibányássz egy új blokkot és hozzáfűzi a láncot:

+ Létrehozza az előző blokk headerjének lenyomatát (hash értékét), ha nincs akkor speciális "fffff...fff".
+ Előállítja a blokk headert a ```nonce``` a ```pending_transactions``` lenyomatából és az előző blokk headerjének lenyomatából.
+ Addig növeli a ```nonce``` értékét míg elő nem állítja a blokk header lenyomatát úgy hogy "0000"-val kezdődjön.
+ Beilleszti a blokkba a headert és az összes várakozó ellenőrzött tranzakciót
+ Hozzáfűzi a blokkhoz
+ Elment mindent

## 3.8 generate_first_block()

Létrehozza az első blokkot a láncban:

+ Előveszi sorba az id fájl neveket, majd beolvassa tartalmát.
+ Mindenkinek aki a listában szerepel létrehoz egy a nevére szóló fix értékű tranzakciót.
+ Meghívja a ```mine()``` függvényt.

## 3.9 new_transaction(csaposhi, recipient)

Létrehoz egy új tranzakciót:

+ A ```self.my_unspent_outputs```-ből addig vesz ki tranzakciókat míg a hozzá tartozó összegek egyenlőek vagy meg nem haladják a küldeni kívánt összeget. Majd inputként elmenti, a publikus kulcsal együtt.
+ Outputként hozzáfűzi a kedvezményezett publikus kulcsát és az összeget amit megadtunk.
+ Az outputhoz adja a visszajárót, és a saját publikus kulcsunk.
+ Létrehozza a tranzakció ID-jét, ami a tranzakció lenyomata.
+ A várakozó tranzakciókhoz fűzi a tranzakciót.