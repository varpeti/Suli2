# Adatbiztonság és kriptográfia

| Jegyzőkönyv | 3. gyakorlat | 
| -- | -- |
| Készítette  | Váraljai Péter BUGE0Q |
| Dátum | 2020.04 |

# Tartalom jegyzék
+ 1. Bevezető
+ 2. Tranzakció 
    * 2.1 Ellenőrzése
        - 2.1.1 Hivatkozások ellenőrzése
        - 2.1.2 Aláírás ellenőrzése
        - 2.1.3 Értelmetlen, veszélyes adat vizsgálata
            + 2.1.3.1 Negatív utalás
            + 2.1.3.2 Double spending
+ 3. Blokklánc
    * 3.1 Validálás
        - 3.1.1 Teljes blokklánc validálása
    * 3.2 Konszenzus
        - 3.2.1 Fork
+ 4. Kód


# 1. Bevezető

A gyakorlat során egy blokklánc alapú technológiával szimuláltuk a ITKoin nevű kriptovaluta működését. A kód írása közben kitértünk a feladat kulcslépéseire, úgymint a tranzakcióhoz szükséges feltételekre, és a blokklánc építésének alapjaira.

Ebben a jegyzőkönyvben összefoglalom mind elméleti, mind gyakorlati szemszögből a kriptovaluta működéséhez szükséges ellenőrzéseket.

# 2. Tranzakció

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

## 2.1 Ellenőrzése

3 + 1 fő részre osztható a tranzakció ellenőrzése:

+ 1. Meg kell vizsgálni a blokkláncban, hogy a hivatkozott tranzakciók valóban léteznek-e, és nem lettek-e már felhasználva egy korábbi tranzakció során bemeneteként.
+ 2. Ellenőrizni kell a inputok végére csatolt aláírást a csatolt publikus kulcsal, hogy valóban a jogosult személy-e a kezdeményező.
+ 3. Meg kell vizsgálni hogy nem tartalmaz-e a rendszer szempontjából értelmetlen vagy veszélyes adatot.
+ + Ellenőrizni kell az egyéb csatolható adatokat. (Például ETH esetén a kódot)

Az ellenőrzésre a tranzakció publikus kulcsainak segítségével a rendszer bármely felhasználója képes bármikor. Így biztosított hogy a tranzakciót valóban a kezdeményező kezdeményezte, és rendelkezésére áll számára az utalni kívánt összeg.

### 2.1.1 Hivatkozások ellenőrzése

Ahhoz hogy megvizsgáljuk hogy a tranzakció a valóban valós hivatkozásokat használ, végig kell menni a blokkláncon és ellenőrizni hogy léteznek-e a meghivatkozott tranzakciók, az outputon (vagy kedvezményezettként, vagy visszajáróként) szerepel az összeg, és hogy ezt még nem használta el sehol, azaz nem hivatkozta még meg sehol máshol.

### 2.1.2 Aláírás ellenőrzése

Az aláírás ellenőrzéséhez kiszámoljuk az input lenyomatát (hash értékét) illetve a csatolt publikus kulcs segítségével dekódoljuk az szintén csatolt aláírást. Ha a kettő megegyezik, valóban jogosult a tranzakciót kezdeményező a kezdeményezésre.

### 2.1.3 Értelmetlen, veszélyes adat vizsgálata

Meg kell vizsgálni hogy nem tartalmaz-e a rendszer szempontjából értelmetlen vagy veszélyes adatot a tranzakció. Nem szabad a rendszerbe engedni olyan tranzakciókat ami mások végül kihasználhatnak.

#### 2.1.3.1 Negatív utalás

Például ha valaki negatív összeget akar utalni valakinek, és ezt megengedjük, akkor a kedvezményezett ugyan nem károsul, mivel nem hivatkozna soha a negatív összegre, de a kezdeményező a visszajárót eltehetné zsebre, aminek semmilyen alapja illetve számbeli korlátja nincsen, és erre később tudna hivatkozni mint valós összeg

#### 2.1.3.2 Double spending

A double spendig (kétszeres költekezés) a számítás technológiával üzemelő fizetési rendszereknél felmerülő visszaélési lehetőség. A kriptovaluták esetében erre az úgy lenne lehetőség, hogy egy felhasználó ugyan arra a tranzakcióra, mint bemenetre két különböző tranzakcióban is hivatkozik. Ezért a hivatkozásokat mindig ellenőrizni kell. 


# 3. Blokklánc

A blokklánc egy úgynevezett nyilvános főkönyvként működik, amely rögzíti az összes tranzakciót. Bárki csatlakozhat a blokkláncbővítéséhez, kezdeményezhet tranzakciókat, és hitelesítheti is azokat, blokkok létrehozásával.

## 3.1 Validálás

Két esetben kell a blokkláncot validálni:

+ A teljes vagy részleges blokklánc külső forrásból érkezik a program indításakor
+ A bányászok által publikált új blokkok nem feltétlen időrendben, és nem feltétlen egymásnak nem ellentmondóan érkeznek meg a felhasználóhoz, ezért döntést kell hozni melyik lehet a valódi, amihez majd később az egész hálózat alkalmazkodik (Konszenzus)

### 3.1.1 Teljes blokklánc validálása

A felhasználónál futó kriptovaluta rendszer külső forrásból kapja meg a teljes blokkláncot. Amikor azt megkapja végig ellenőrzi az blokkonként hogy a blokkok helyesen vannak-e egymás után fűzve. Ez utóbbit úgy ellenőrzi hogy megvizsgálja hogy az előző blokk hashének értéke megegyezik-e a jelenlegi blokkban tárolt előző blokk hash értékével. Ezen felül a *Proof of work*-ot is ellenőrzi, azaz azt hogy elegendő számú 0-ás van-e a hash elején. Továbbá ellenőrzi a blokk headerben lévő tranzakciós lenyomat, megegyezik-e a tranzakciók lenyomatával. A tranzakciókat a blokklánc ellenörzésekor nem ellenőrzi, túl sok erőforrás lenne.

## 3.2 Konszenzus

Annak ellenére, hogy egy blokk valid, és beilleszkedik a blokkláncba még nem feltétlen mindenki által elfogadott. Ennek oka abban rejlik hogy a kriptovaluta rendszerben, nem centrális, hanem peer-2-peer hálózati alapon operálnak a résztvevők. Ennek eredményeként, mindenki párhuzamosan egymással versenyezve "bányásszák" és publikálják a következő blokkot. Mivel a világ különböző pontjain is elhelyezkedhetnek a bányászok ezért nem ritka hogy "egyszerre" készülnek el egy blokkal. Ezért gyakran előfordul hogy az egymáshoz "közelebb" (információ sebességéből fakadó távolság) lévő csoport folytat egy lánc irányt. Míg egy másik csoport egy másik lánc irányába indul el. Ezért szükség van egy *Konszenzusra* hogy melyik irány a valódi. Ezt általában az dönti el, hogy melyik ágra épül több blokk hamarabb, mivel azt fogja a többség elfogadni.

### 3.2.1 Fork

Amikor egy csoport, mondjuk program hiba miatt elkezd máshogy építkezni a blokkláncba, és ők, vagy a többiek nem fogadják el a másik csoport blokkjait és ezáltal a blokkláncát, a blokklánc szétágazik.

Ezt általában gyorsan orvosolják és megszüntetik az okát.

Azonban szándékos közmegegyezést igénylő változás esetén létrejöhet a **Hard Fork**, ekkor egy új kriptovaluta születik, aminek megegyezik a minden korábbi tranzakciója az előzővel, viszont a későbbiek teljesen különböznek. (BTC -> BCH)

# Kód

```python
    def validateTransaction(self, transaction):
        sumOfInputs = 0
        for input in transaction['inputs']:
            data = {'txid':input['txid'],'csaposhi':input['csaposhi']}
            # Aláírások ellenőrzés
            if (not self.verifySignature(data, input['signature'], RSA.import_key(input['publicKey']))):
                print(data,input['signature'],RSA.import_key(input['publicKey']))
                return False
            # Input hivatkozások ellenőrzése
            if data not in self.myUnspentOutputs:
                print(data,self.myUnspentOutputs)
                return False
            sumOfInputs += input["csaposhi"]
        
        
        sumOfOutputs = 0
        for output in transaction['outputs']:
            sumOfOutputs += output['csaposhi']
            # Minden output nagyobb mint 0
            if (output['csaposhi']<=0):
                return False

        # Outputok összege megegyezik-e az inputok összegével
        if sumOfInputs != sumOfOutputs:
            return False

        return True
```

```python
    def validate_chain(self): 
        def validateChain(self):
        lastBlock = self.chain[0]
        ci = 1 # Az első blokk kivétel, nem ellenőrizzük
        
        # Végigmegyünk az összes blokkokon páronként
        while ci < len(self.chain):
            block = self.chain[ci]

            # Megvizsgáljuk hogy tényleg egybe van-e fűzve a blokklánc
            if self.createHashHexValue(lastBlock['blockHeader']) != block['blockHeader']['previousBlockHeaderHash']:
                return False

            # Megvizsgáljuk hogy az aktuális blokk hash értéke elég 0-ával kezdődik-e.
            if not self.PoW(self.createHashHexValue(block)):
                return False
            
            lastBlock = block
            ci += 1
        # Az utolsó blockot is megvizsgáljuk még, hogy érvényes e a PoW érték.
        if not self.PoW(self.createHashHexValue(self.chain[-1])):
            return False

        return True
```