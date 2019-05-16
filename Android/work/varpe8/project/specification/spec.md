# Teljesen szabadon konfigurálható billentyűzet

## Beállítási lehetőségek, rövid leírás:

### Billentyűzet csoport
- Név
- Ez tartalmazza a billentyűzeteket
- Ezt lehet kiexportálni illetve importálni
> (Ki) kell találni egy leíró formátumot!
> vagy Json, vagy egy saját human readable formátum (ton): 1 sor egy key/value, a behúzás határozza meg hogy mi hova tartozik. Példa: [varpeti/ton](https://github.com/varpeti/ton)

#### Billentyűzet
- billentyűzet ID
- Ez tartalmazza a sorokat
- sorok száma a billentyűzeten

#### Sor
- sor ID
- a sor magassága
- gombok száma

#### Gomb
- gomb ID
- a gomb szélessége
- a gomb elsődleges szövege/jelei
- a gomb másodlagos szövege/jelei
- sima nyomáskor mit csinálon 
- hosszan nyomáskor mit csináljon
- a gomb háttér színe, karakter színe

#### Popup
- popup ID
- ugyan úgy állítható mint egy sor
- eltűnik ha felengedi az ujját a felhasználó, és amelyik gombon ált azt trigereli
- popup színei

#### Gombfunkciók
- egy,több karakter kiírása
- kurzor mozgatása
- speciális gombok, ctrl, alt, tab, esc, F1-F12, stb
- váltás egy másik billentyűzetre
- popup /csak hosszan nyomás/
- repeate /csak hosszan nyomás/
- semmi
- intent hívás (böngésző, e-mail, billentyűzt beállítások)
- fentebbi dolgok kombinálása: pl egy gombnyomásra kiír egy '(' majd egy ')' és visszalép a két zárójel közé


#### Egy kis tech:
- A gombokat egy másik billentyűzettel lehet mapelni. - /ha nem túl nehéz megoldani/ fizikai billentyűzettel is lehessen mapeleni.
> Nem értem, hogy mire gondolsz
> Semmi extra: Azt hogy melyik karakter(eke)t írja ki egy gomb, egy másik billentyűzettel lehessen definiálni, "beleírni" ne egy az appban előre definiált készlet legyen.

- A billentyűzeteket lehessen kiexportálni, valami hunam-readable formátumba, és lehessen importálni is.
- Nem kell fedni egy adott opciónak a definíciós fileban az Acytivitiyken való beállításokat: pl a shift gomb egy másik billentyűzetet hív meg (2.) amin minden karakter nagy és bármely gomb megnyomása után visszadobja az 1-re kivéve a shift újboli megnyomására, mely átdob egy 3. billenytűzetre ahol minden billentyű nagy de nem dob vissza az 1re csak a shift.
- Egy billentyűt elég 1x létrehozni, gomb ID-val helyezük el, így ha megváltoztatjuk a gomb viselkedését, mindenhol máshol is meg fog vátozni.

#### Activity plan:
- Minnél jobban csoportosítva, minnél egyszerűbben egy átlag user számára, minnél több beálítási lehetőség biztosítása, azonban NE korlátozza a szabadságot semmiben. pl: nincs előre definiálva hogy van kicsiabc, nagyabc1, nagyabc2 billentyűzet még is ha a user a shift gombot létrehozza, kínálja fel a lehetőséget, vagy legyen rá opció hogy autómatán hozza létre a kisabc-hez a másik 2-őt.

#### /optional/ - jó volna!
- különböző inputokon különböző billentyűzet (pl mail, url, numeric)
- hangok, vibrációk
- gestures, telefon elforgatás
- a korábban kiírt szöveg visszaolvasása, és annak alapján egy gomb/gombok viselkedésének beállítása: pl Nagybetűvel kezd pont után/üres sorban
- ID alapján mutasson egy gomb a másikra, és annak az új gombon módosítása: pl a kisabc-s gombokra mutassanak a nagyABC-s gombok toUpper()-fvel.