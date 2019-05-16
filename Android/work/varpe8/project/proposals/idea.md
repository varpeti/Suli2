## 01 - Encrypted Chat
- Első futás után egy UUID az azonsoító
- PHP szerver
- UUID-val lehet egymást azonosítani, azonosítás után lehet becenevet adni
- Üzenet
    + Egy máshol megbeszélt jelszóval kódol (pl ChaCha20)
    + /optional/ PGP kulcsal
        * ekkor első beszélgetésnél publikus kulcsot cserélnek
        * /extra optional/ alá is írja az üzenetet a privát kulcsal, hogy tudja biztosan a másik hogy ki küldte az üzenetet.
- 3 fázis az üzeneteknek: local(A) -> server -> local(B)
- A szerver nem tárololja a leküldés után az üzeneteket
- Törlés csak a local-t törli, ha már felküldte a szervernek nem törli.
- UFT-8 Unicode /ha lehet/

## 02 - Double-entry bookkeeping / Money Manager
- Számlák:
    + Bevétel
    + Kiadás
    + Sima
        * Credit
        * Debit
        * Egyéb
- Pénznem:
    + Számlánként 1 pénznem
    + Bármilyen max 5 karakteres pénznem lehet
    + Ha különböző a pénznem, váltás ablak ugrik fel, ahol lehet árfolyamot, vagy egyik és másik mennyiséget állítani.
    + Minden pénznem 8 tizedes jegyig osztható (#cryptovaluta)
- Kimutátsok:
    + Napi, heti, havi, évi, örök, egyéni időtartamra
    + Típusok:
        * Lista: felsorolja az adott idő intervallumon az összes tarnzakciót
        * Egyenleg: kilistázza az összes az adott idő intervallumon az összes számla egyenlegét
    + Jelentések: Diagrammok, gráfok.
- Auto Backup, manual export:
    + Local
    + Online (GoogleDrive, SFTP, stb) /optional/
    + Json, xml, vagy valami human readable, de lehet bináris is.
- Plugins /optional/
    + Tasker
    + IFTTT

## 03 - Teljesen szabadon konfigurálható billentyűzet

#### Sor
- Sorok száma a billentyűzeten
- a sor magassága

#### Gomb
- Gombok száma 1 sorban
- a gomb szélessége
- a gomb elsődleges szövege/jelei
- a gomb másodlagos szövege/jelei
- sima nyomáskor mit/miket írjon
- hosszan nyomáskor popup vagy repeate vagy semmi
- a gomb háttér színe, karakter színe

#### Popup
- Popup egy lista amin mindig kijelöl egy elemet, és az új felengdésekor leírja a kijelölt elemet.
- popup lista színei

#### Egyéb
- A gombokat egy másik billentyűzettel lehet mapelni.
- /ha nem túl nehéz megoldani/ fizikai billentyűzettel is lehessen mapeleni.
- speciális gombok amik átváltanak egy másik billentyűzetre (shift, ctrl, alt, num, smiley, symbol)


#### /optional/
- különböző inputokon különböző billentyűzet (pl mail, url, numeric)
- hangok, vibrációk

