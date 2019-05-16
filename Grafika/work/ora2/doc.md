# Bézier görbe rajzoló

Sok módosítást nem kellet véghezvinni az alap törtvonal rajzolón:
- Egy a vörös kontroll pontokat kirajzoló részt
- Egy szakaszokra bontást
- 2 függvényt a Bézier-hez:
    - **B**(t,controllpontok) ami kiszámolja az adott szakaszra a controllpontok alapján a görbe útját
    - **Bt**(i,t,cpszám) ami súlyozza az X és Y koordinátát, az adott szakaszon *t* az adott *i* kontrollpontnál.

# Lagange görbe rajzoló

A Bézier görbe rajzolót módosítottam az alábbi módon:
- A **B**(t,controllpontok) függvényt átírtam a úgy hogy Lagarnge görbt rajzoljon ki.
- **Bt(..)**-t megszüntettem
- A **B**(..) átírtam **L**(..)-re

# Nurbs görbe rajzoló
- A Lagarnge ból kitöröltem a szakaszra osztást és az **L**(..) függvényt
- A **drawNurbs**(pontok) fügvényben
    - létrehozom az adattagokat:
        - Nurbs objektum
        - ORDER (*=3*)
        - kontrolpontok[maxpont][3]
        - csomópontok[maxpont+ORDER]
    - Inicializálom a megadott glut függvényekkel
    - Inicializálom a csomópontok vektoromat úgy hogy a ```knots[i] = i/(ptnum+ORDER)```
    - Feltöltöm a ```kontrolpontok[][]``` mátrixot a ```pontok[]``` vektorból
    - Majd kirajzoltatom a megadott glut fügvényekkel a görbét