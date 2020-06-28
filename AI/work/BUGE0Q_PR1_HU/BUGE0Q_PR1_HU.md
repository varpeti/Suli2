# Artificial Intelligence

| Jegyzőkönyv | Grid Car | 
| -- | -- |
| Készítette  | Váraljai Péter BUGE0Q |
| Dátum | 2020.04 |

# Tartalom jegyzék
+ 1.0 Bevezető
    * 1.1 A játék
        * 1.1.1 Lépés
        * 1.1.2 Speciális szabályok
            - 1.1.2.1 Fog of War
            - 1.1.2.2 Speciális mezők
    * 1.2 A környezet
+ 2.0 Az ágens
    * 2.1 Felépülésének folyamata
        - 2.1.1 Tervezés
        - 2.1.2 A csillag
        - 2.1.2 Módosított A*
        - 2.1.3 Multiplayer, multithread
        - 2.1.4 Fog of War
        - 2.1.5 Valódi Pánik, Valódi cél!
        - 2.1.6 Mi a következő cél?
        - 2.1.7 Gyakrabb tervezés elvetett ötlete
        - 2.1.8 Optimalizálás
            + 2.1.8.1 Rendezettebb Pánik
            + 2.1.8.2 Speciális mezők
            + 2.1.8.3 Út javítás
+ 3.0 Vélemény

# 1.0 Bevezető

A játék amiben az AI részt vesz egy úgy nevezett **Grid Car Game**.

## 1.1 A játék

Adott egy versenypálya, több kezdő és célponttal. A játék több versenyző által játszható, akik véletlen kezdő pozícióból indulnak. A játékosok adott sorrendben felváltva lépnek, és aki kevesebb lépésből ér a célba az nyer. (A megtett távolság nem számít)

### 1.1.1 Lépés
Minden játékos 9 lépésből választhat a következőképpen: Ha az előző pozíciója egy játékosnak ```(x[i-1], y[i-1])``` és a jelenlegi pozíciója ```(x[i], y[i])``` akkor a következő körben ezek a lépések válaszhatóak:

```
(x[i+1], y[i+1]) = (x[i], y[i]) + ((x[i], y[i]) - (x[i-1], y[i-1])) + (k, l) ahol k, l ∈ [-1, 0, 1] 
```

![step](https://i.imgur.com/34jQP6R.png "Lépés") 

**Fig 1.** *Ha a kék az előző lépés, és a zöld a jelenlegi, akkor a játékos a piros pontok bármelyikébe léphet.* 

Ha egy játékos kilép a pályáról, vagy olyan helyre lép ahol egy másik játékos áll jelenleg, akkor kimarad 5 körből és vissza kerül az előző érvényes pozíciójába 0 sebességgel. A balesetben résztvevő ártatlan fél büntetés nélkül mehet tovább, mintha semmi se történt volna.

### 1.1.2 Speciális szabályok

A játék több fordulós, minden fordulóban speciális szabályok lépnek életben, ami akár alapjaiban is megváltoztatja a kívánt stratégiát, és az alkalmazott megközelítést.

#### 1.1.2.1 Fog of War

A második fordulóban a játék megszűnik *"teljes ismeretes"* lenni. Az ágens csak ```r``` sugarú környezetét "látja" a pályának, és az azon elhelyezkedő játékosoknak. Ha nincs benne a környezetben, akkor a cél helyzete is ismeretlen.

#### 1.1.2.2 Speciális mezők

A harmadik fordulóban a játék kibővül két új mezővel:

- Olaj
- Homok

Bármely speciális mezőre tetszőlegesen léphet az ágens, viszont ezekről a mezőkről való elmozdulás *sztochasztikus*, abban az esetben ha az ágens sebessége nem nulla. 

**Olaj** esetén a sebesség változatlan marad, csak az irány sztochasztikus.

**Homok** esetén a sebesség csökken és az irány sztochasztikussá válik.

![specTiles](https://i.imgur.com/F8Fuab6.png "Speciális mezők viselkedése")

**Fig 2.** *Ha a szürke ez előző pozíció, a kék a jelenlegi, akkor a zöld mezők a lehetséges pozíciók ahova az ágens kerülhet.*

## 1.2 A környezet

A játék és az ágens egy böngésző alapú JavaScript környezetben futnak.
Ennek folyományaként a *"valódi" töbszálas* programozás nem lehetséges.
Ezen felül az ágens memória és idő limittel is rendelkezik.

# 2.0 Az ágens

## 2.1 Felépülésének folyamata

Az ágens írásakor sajnos nem használtam verzió követő rendszert, így emlékezetből és a kód alapján próbálok pontos képet mutatni a fejlesztés menetéről.

### 2.1.1 Tervezés

Az ágens tervezésének első szakasza a környezet megismerése, annak *reverse engineer*-elése. Ekkor két hasznos dolgot is felfedeztem: Hogyan tudom automatizálni a "kód feltöltést", azaz hogyan tudom "ijectelni" az ágens(eim)et (**Fig 3.**). Ez nagyban meggyorsítja a fejlesztést, és csökkenti a repetatív unalmasság faktorát. A másik meg, lévén egy vizuális játéktérről van szó, a debuggolást lényegesen egyszerűbbé teszi ha tudok rajzolni a pályára. (**Fig 4.**)

```javascript
(function inject()
{
    for (var i = 0; i < 1; i++)
    {
        var a = new agentN;
        lc.addPlayer("agent"+i,a);
    }

    var b = new agentB;
    lc.addPlayer("agentB",b);

    document.getElementById("start-codeplay").click(); //start
})();
```
**Fig 3.** *Injection metódus amivel könnyen lehet több játékost is összemérni.*

```javascript
var drawLine=function(l)
{
    try
    {
        var pline = d3.select("#playerlines")
            .append("line")
            .attr("x1", l.y1*au)
            .attr("y1", l.x1*au)
            .attr("x2", l.y2*au)
            .attr("y2", l.x2*au)
            .style("fill", 'transparent')
            .style("stroke", l.color)
            .style("stroke-width", '3')
        return pline;
    }
    catch (e)
    {
    }
}
```
**Fig 4.** *Egy vonal rajzolást segítő metódus. "try-catch"-be ha esetleg nem működne az éles rendszeren*

A maradék tervezés csak annak az eldöntésébe merült ki hogy módosított ```A*``` algoritmust szeretnék az egész alapjául használni. Ami a játék egyre *sztochasztikusabbá* válása és *rész ismeretessége* miatt egy kedvezőtlen választás.

### 2.1.1 A csillag

Az első ágens egy tiszta ```A*``` lett. Ahol az ágens nem a 2D-s térben, hanem egy úgynevezett *lépés gráfban* navigált. Azaz a gráf csúcsai a pályán elfoglalt pozíción felül számos más információt is tartalmaztak, ezáltal egy hasznos kereső fát előállítva. Hogy érthetőbb legyen: ha az ágens ugyan abba a pozícióba tervez lépni, de máshonnan, az-az más sebességgel és iránnyal, akkor az a *lépés gráfban* egy teljesen másik *Node* lesz.

Ezzel a 2 hatalmas probléma is volt: Túl sokáig és túl nagy memória igénnyel futott.

### 2.1.2 Módosított A*

A következőkben a meglévő ```A*``` algoritmust ```SMA*``` algoritmussá alakítottam egy kisebb kutakodás, és hosszabb próbálkozás után, azonban az időigénye annyira megnövekedett hogy elvetettem az ötletet. A "memória-idő trade-off" nem kifizetődő, nekem mást kell feláldozni hogy mindkettőt csökkentsem. Ezért a feladtam az optimális út megkeresését első lépésben, azaz ha talál egy utat a célhoz azzal azonnal visszatér. A másik pedig, hogy nem kezelem külön a különböző irányból megközelített pozíciókat külön *Nodeként*, viszont továbbra is a *lépés gráfban* dolgozok, ami így lényegesen kevesebb memóriát igényel. Ez utóbbi módosítás egy *Hackel* lett megvalósítva, ami későbbiekbe *technical depth*-hez vezetett: Nem lehet jobbra cserélni a Heap algoritmust. Továbbá elvesztette az ágens azt a lehetőséget amikor a cél nem létezik, de ez esetünkben eleve kizárható, így nem kell félni hogy végtelen ciklusba kerül.

### 2.1.3 Multiplayer, multithread

Az első fordulóra nem elég csak módosított ```A*```. Ebben a játékban több játékos is részt vehet, és a lépések megtervezésekor nem tudja bele kalkulálni azok mindenkori helyzetét. Ezért egy úgy nevezett *"Pánik"* módba kapcsol az algoritmus amikor addig lépked véletlen szerűen amíg meg nem szüli az új tervet. 

Ezzel több probléma is van: Nincs valódi multithread, a véletlen lépésnél van jobb is. De ezzel a 3. fordulóig csak "TODO" szinten foglalkoztam.

### 2.1.4 Fog of War

A második fordulóra felkészülést már az első forduló határideje előtt kicsivel megtettem, mivel megtaláltam a tavalyi környezet kódjait, és azokból ki tudtam hámozni hogy a ```lc.validLine(p1,p2)``` az megváltozik és ```lc.validVisibleLine(c,p1,p2)``` lesz, ahol a ```c``` az a pálya rész amit az ágens ismer. Ezért a változásokhoz "wrapper" függvényeket hoztam létre (**Fig 5.**), illetve előkészítettem ```map``` updaeteléséhez szükséges lépéseknek a helyet. 

```javascript
//*/// Wrapper around different line validators
function isValidLine(p1,p2,c)
{
    if (lc.validLine) return lc.validLine(p1,p2);
    else if (lc.validVisibleLine) return lc.validVisibleLine(c,p1,p2);
    else throw "Line validation function not found!";
}

//*/// Wraper around playerAt
function isPlayerAt(p1,selfIndex=-1)
{   
    var id;
    if (lc.playerAt)             id = lc.playerAt(p1);
    else if (lc.visiblePlayerAt) id = lc.visiblePlayerAt(map,p1);
    else throw "PlayerAt function not found!";
    return (id!=-1 && id!=selfIndex);
}
```

**Fig 5.** *Csomagoló függvények a fordulókban változó függvényekre*

Az ```isPlayerAt(p1,selfIndex=-1)``` "wrapper" függvény egyébként használható úgy is hogy saját magunkat ne számítsuk játékosnak, ezt a featuret azonban a végső verzióba nem használom már, csak bennmaradt mint lehetőség.

### 2.1.5 Valódi Pánik, Valódi cél!

Mivel a játék tér nem ismert innét kezdve, azt járni kell hogy több információhoz jussunk ezért új stratégiát kell alkalmazni. Vagy kellet volna, csökönyösen ragaszkodtam, az amúgy szerintem nem túl jól teljesítő ```A* mutáns```-omhoz. "Ha nincs cél, csináljunk!" felkiáltással minden olyan területet ami az ismeretlen határán van, és rá tudunk lépni, ```sideGoal```-nak tituláltam (**Fig 6.**), és a heurisztika ezek közül az egyikhez mutat. Továbbá mindegyik célnak felel meg az ```A* mutáns``` számára. Ez utóbbira ezért van szükség hogy ne kerüljön végtelen ciklusba olyankor mikor már létszik a valódi cél, de még nincs olyan út ami elérne oda.

![agens](https://i.imgur.com/LESNxp2.png "Ágens")

**Fig 6.** *Lila: megtett út; Kék: tervezett út; Ciánkék: javítás; Narancs/fehér: pánik esetén lehetséges/választott lépés. Sárga: a tervezés kezdetekor az ismereti határon lévő mezők; Piros: valódi cél*

### 2.1.6 Mi a következő cél?

A ```getNextGoal(pos)``` szerintem az egyik legcsúnyább dolog az egészben, rengetegszer meghívódik, nem ott ahol észerű változtatások mellet kéne. Csak azért lett megtartva, és nem lett "szebb" formába öntve; mert működőik. De a szépség relatív, ez pedig egy script nyelv.

Fejlődése korai szakaszaiban első alkalommal lefutott és elmentette a ```trueGoal``` értékként azt a pozíciót ami jól fel lehetett használni heurisztikaként, és onnét kezdve csak ezzel tért vissza.

Később a ```sideGoal```-ok keresése is a feladatává vált, és amennyiben nincs "valódi cél" még, a heurisztika és a számítási teljesítmény csökkentése érdekében ```trueGoal```-ként állítja be. Ezt az ```A* mutáns``` reseteli, hogy új futáskor új információk alapján új célt találjon.

### 2.1.7 Gyakrabb tervezés elvetett ötlete

Az ágens úgy fut:
- Tervez
- Lép amíg van a tervből
- Pánikol ha nincs új terv, közbe jön valami, és próbál tervezni.

Ezt úgy akartam módosítani hogy már Lépések közben is tervez, és hozzáadja a meglévő tervhez az új információk alapján számolt tervet. A ```getNextGoal()``` függvény meghívása fontos az ```A* mutáns``` előtt, mivel így nem lesz cél a korábbi cél.

Ez azonban 2 dolog miatt nem működő képes, felesleges: A meglévő terv simám végződhet úgy hogy a következő lépésben belefut a falba, amit nem látott tervezéskor, másrészt rendkívül számítás igényessé teszi.

A kikommentelt kódrész ```this.movefunction``` alatt megtalálható.

### 2.1.8 Optimalizálás

A harmadik forduló kezdetével rátértem a kód optimalizálására, sok helyen refaktrolotma, átírtam szebbre, feleslege részeket kiszedtem, a "TODO"-k nagy részét befejeztem.

#### 2.1.8.1 Rendezettebb Pánik

A ```panic(c,playerData,selfIndex)``` függvény elérte a végső formáját, amiben igyekszik olyan lépést választani ami csökkenti a sebességet ezzel nagyban megnövelve az esélyét annak, hogy a tervezés jobb és gyorsabb eredményt adjon, csökkentve a kockázatát annak hogy baleset történik. Emellett rajzolással is "szemeteli" a pályát. (**Fig 6.**) Ezen felül ha eltér valamiben a tervezettől a következő lépés, pánik módba kerülünk.

### 2.1.8.2 Speciális mezők

A speciális mezőket nagyobb súly illeti meg a *cost* számításakor. Ha még is rá lépünk egyre, és a terv szerint haladhatunk tovább akkor semmi nem történik. Amennyiben eltér a véletlenszerű választás a tervtől, a *Pánik* mód lép érvénybe, és újratervez.

### 2.1.8.3 Út javítás

Már az első és második fordulóba is volt próbálkozás a megtervezett út kijavítására utólag, mivel ez lehet költséghatékonyabb mint egy kimerítőbb keresés, azonban a bonyolultsága meghaladja a "try and error" fejlesztést így ez nem került be a kódba a 3. fordulóig. Fehér lapo(oka)t és tintát ragadtam és nekiültem rajzolni és tervezni.

Az eredmény a (**Fig 7.**) ábrán látható. Az algoritmus ismeretében elég triviálisnak tűnik ez a megoldás, azonban "üres lappal" nehéz rájönni. Az algoritmus lényegében keres két pontot ```i,j``` amire igaz hogy ```i``` pontból el lehet-e jutni ```j``` pontba, és ```j``` pontból továbbra is el lehet jutni a ```j+1``` pontba. Ha ez mind igaz akkor ki kell vágni a felesleges út részeket, és az új útnak megfelelően updatelni kell az ```j``` és ```j+1``` pontokat, ami rendre az ```i+1``` és ```i+2``` pontoknak felel meg.
Az algoritmusnak, hogy a kezdő ponttól is tudjon javítani, ne csak +2-től, átadunk paraméterül két csak pozíciót tartalmazó *Node* szerű objektumot (nagy előnye a script nyelveknek a vegyes típusú adatszerkezet), amiket hozzáfűzök az elejéhez, majd mikor nem kellenek eldobom őket.

A (**Fig 6.**) ábrán látható baloldalt ahol kihagyott csomó tervezett lépést, és középen ahol majd ki fog hagyni.

```javascript
//*/// Make the existing path better
function betterPath(in2,in1)
{
    if (path.length<3) return false;

    path.unshift(in1);
    path.unshift(in2);

    for (var i = 1; i < path.length-2; i++) 
    {
        for (var j = i+2; j < path.length-1; j++)
        {
            //if (1 < distance(path[i].pos,path[j].pos)) continue; //only 1 block away (8)

            //Check if i->j is reachable
            var newI1 = isReachable(path[i-1].pos,path[i].pos,path[j].pos)
            if (!newI1) continue;

            //Check if j->j+1 is reachable
            var newI2 = isReachable(path[i].pos,path[j].pos,path[j+1].pos)
            if (!newI2) continue;

            //drawLine({x1:path[i].pos.x,y1:path[i].pos.y,x2:path[j].pos.x,y2:path[j].pos.y,color:"#ffffff"})
            //debugger;

            //remove unnececerry 
            path.splice(i+1, j-i-1);

            //drawCross({x1:path[i].pos.x,y1:path[i].pos.y,color:"#ff0000"});
            path[i+1]=newI1;
            path[i+2]=newI2;
            //drawCross({x1:path[i].pos.x,y1:path[i].pos.y,color:"#ffffff"});

            drawLine({x1:path[i].pos.x,y1:path[i].pos.y,x2:path[i+1].pos.x,y2:path[i+1].pos.y,color:"#33ffff"})
                //debugger;

            path.shift();path.shift(); // remove i-1 i-2

            return true; //continue
        }
    }

    path.shift();path.shift(); // remove i-1 i-2
}
```

**Fig 7.** *A ```betterPath(in2,in1)``` függvény megvalósítása*

# 3.0 Vélemény

Alapvetően elégedett vagyok az elkészült ágenssel. Nem a legjobb, ha újrakezdhetném teljesen máshogy állnék neki, azonban a munkám során számos új hasznos tudásra tettem szert, mind az mesterséges intelligenciák, mind a JavaScript programozás területén. Szívesebben megyek a saját fejem után, mintsem hogy "bizonyítottan jó" papírformát kövessek, ami bizonyítottan jobb eredményt is ad. Élvezettel töltött el nézni ahogy a saját ötletem alapján elkészített "intelligencia" a saját kis világában törekszik a cél felé.

![y19](https://i.imgur.com/ZvGqJZ4.png "19-es pálya")

**Fig 8.** *A 19-es pályán játszó ágens*