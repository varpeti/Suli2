# Projekt specifikáció
**Váraljai Péter** BUGE0Q

## Grid car race

### Probléma specifikációja

#### A játék
Adott egy versenypálya, több kezdő és célponttal. A játék több versenyző által játszható, akik véletlen kezdő pozícióból indulnak. A játékosok adott sorrendben felváltva lépnek, és aki kevesebb lépésből ér a célba az nyer. (A megtett távolság nem számít)

#### A lépés
Minden játékos 9 lépésből választhat a következőképpen: Ha az előző pozíciója egy játékosnak ```(x[i-1], y[i-1])``` és a jelenlegi pozíciója ```(x[i], y[i])``` akkor a következő körben ezek a lépések válaszhatóak:

```
(x[i+1], y[i+1]) = (x[i], y[i]) + ((x[i], y[i]) - (x[i-1], y[i-1])) + (k, l) ahol k, l ∈ [-1, 0, 1] 
```

![step](https://i.imgur.com/34jQP6R.png "Lépés") 

*Ha a kék az előző lépés, és a zöld a jelenlegi, akkor a játékos a piros pontok bármelyikébe léphet.* 

Ha egy játékos kilép a pályáról, vagy olyan helyre lép ahol egy másik játékos áll jelenleg, akkor kimarad 5 körből és vissza kerül az előző érvényes pozíciójába 0 sebességgel. A balesetben résztvevő ártatlan fél büntetés nélkül mehet tovább, mintha semmi se történt volna.

Kezdéskor és érvénytelen lépés után az előző és a jelenlegi pozíció azonos.

### Motiváció
A probléma "egyszerű", és sokféle megközelítéssel megoldható.
Ugyanakkor versenyzésre is ad lehetőséget más játékosokkal, ami ráadásul kissé ugyan, de sztochasztikussá teszi a játékot. (Egyjátékos esetben determinisztikus mivel elég lenne csak az elején meghatározni az optimális lépéseket és azt végig követni, de itt figyelni kell a többi játékosra is)

A JavaScript keretrendszer "könnyen" manipulálható hogy különböző megközelítéseket akár egymással szemben is párhuzamosan lehessen tesztelni.

### Különböző mesterséges intelligencia lehetőségek vizsgálata

#### Keresők
Mivel ez egy (majdnem) teljes ismeretes játék, egy jó kereséssel megállapítható az optimális út a célig. Ezután már csak a többi játékos zavarásának hatására kell korrigálni.

#### NEAT (NeuroEvolution of Augmenting Topologies)
Csak mert kevésbé ismert attól még nagy ágyú, és nagyot szól. Csak mert gondolkodni kevesebbet kell (ha nem 0-ról építem fel), cserébe többet kell kódolni, várni és reménykedni. Na meg egy kis hackelés a kódolásba hogy rávegyük a keretrendszert az együttműködésre. *It would be a neat solution! (pun intended)*

#### Nekiesni manuálisan és saját gondolkodás alapján iteratív módon felépíteni egy AI-t. (NMSGAIMF1AI)
Sok elvesztegetett idő és gondolkodni is kell.

#### Hybrid
A fentebb felsorolt eljárások lineáris kombinációja a cél. Ha valamelyik konstans szorzója 0, hát legyen.

###### Terv:
- Kereső (A* illetve változatai?)
- NMSGAIMF1AI segítségével realtime igazodni más játékosokhoz. (random, illetve saját korábbi verziókhoz)
- Nyerni az első körben
- NEAT 
- (NEAT vs Hybrid) vs (NEAT Hybrid)
- Nyerni a második körben
- Javítani mind a NEAT mind a Hybrid mind a NEAT Hybrid megközelítést
- Nyerni a harmadik körben
- Felrúgni a tervet teljesen, és elmenni egy teljesen másik irányba ami biztosítja a nyerést, vagy nem.

###### Egyéb extrák
- Úgy nyerni hogy a másik játékos(ok) lépéseit direkt szabotálja az ágens.
- Nyerni a JavaScript szépségeit kihasználva ;)

### Milyen tanulási módszerek használhatóak?
A feladat megoldható hagyományos mesterséges intelligenciával (nem neurális hálózat), ami tanulás nélkül is képes operálni, mivel a környezet állandó, és csak a többi játékos sztochasztikája a zavaró tényező. Ez utóbbi miatt lehet egy tanuló részt építeni ami megbecsüli a másik játékos elkövetkező lépéseit és aszerint halad tovább.

A NEAT egy genetikus algoritmus (GA), ahol a generációk mesterséges neurális hálózat segítségével működnek (NeuroEvolution). A súlyozott paramétereket és hálózati struktúráját változtatja evolúciós módszerekkel (kiválasztás, keresztezés, mutáció), úgy hogy az egyedek fitnesze és generáció diverzitása között tartja az egyensúlyt. Egyes "csoportok" képesek lehetnek fejlődés során tanuló ágenshez hasonló viselkedést elérni.

### Elérendő célok

#### Minimum
Optimális út meg**keresése** a célhoz és annak követése. Többi játékos figyelmen kívül hagyása.

#### Maximum
Egy játékos szabotáló Hybrid ágens mellet fejlődött NEAT, ami minden esetben a legoptimálisabb döntést hozza.

#### Várható
Egy Hybrid ágens, ami képes a többi versenyzőt elkerülni a cél felé haladva.